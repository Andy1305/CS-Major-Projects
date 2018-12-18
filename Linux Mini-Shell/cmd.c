/**
 * Operating Systems 2013-2017 - Assignment 2
 *
 * TODO Name, Group
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <fcntl.h>
#include <unistd.h>

#include "cmd.h"
#include "utils.h"

#define READ		0
#define WRITE		1

/**
 * Internal change-directory command.
 */
static bool shell_cd(word_t *dir)
{
	int ret;
	/* TODO execute cd */
	ret = chdir(get_word(dir));

	return ret;
}

/**
 * Internal exit/quit command.
 */
static int shell_exit(void)
{
	return SHELL_EXIT;
}

/**
 * Parse a simple command (internal, environment variable assignment,
 * external command).
 */
static int parse_simple(simple_command_t *s, int level, command_t *father)
{
	int ret = 0, size, status, fd = -1;
	char *file = NULL, *var= NULL, *value = NULL, *in = NULL, *out = NULL, *err = NULL;
	pid_t pid;
	
	/* TODO sanity checks */

	/* TODO if builtin command, execute the command */
	if(strcmp(get_word(s->verb), "exit") == 0 ||
	   strcmp(get_word(s->verb), "quit") == 0)
	   	ret = shell_exit();
	else if(strcmp(get_word(s->verb), "cd") == 0) {
		file = get_word(s->in);
		if(file != NULL) {
			fd = open(file, O_RDONLY);
			DIE(fd < 0, "file does not exist");
		}
				
		fd = -1;
		file = get_word(s->out);
		if(file != NULL) {
			if(s->io_flags == IO_OUT_APPEND)
				fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
			else
				fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		}
				
		file = get_word(s->err);
		if(file != NULL) {
			if(s->io_flags == IO_ERR_APPEND)
					fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
				else
					fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		}
		ret = shell_cd(s->params);
	}
	else if (strchr(get_word(s->verb), '=') != NULL) {
		var = strtok(get_word(s->verb), "=");
		value = strtok(NULL, "=");
		if(value[0] == '$')
			setenv(var, getenv(&value[1]), 1);
		else
			setenv(var, value, 1);
	}
	else if (s->verb->expand == true) {
		printf("%s\n", get_word(s->verb));
	}
	else {
		pid = fork();
	
		switch(pid) {
			case -1:
				DIE(1, "error forking");
			case 0:
				in = get_word(s->in);
				if(in != NULL) {
					fd = open(in, O_RDONLY);
					DIE(fd < 0, "file does not exist");
					dup2(fd, STDIN_FILENO);
				}
				in = NULL;
				
				fd = -1;
				out = get_word(s->out);
				if(out != NULL) {
					if(s->io_flags == IO_OUT_APPEND)
						fd = open(out, O_CREAT | O_WRONLY | O_APPEND, 0777);
					else
						fd = open(out, O_CREAT | O_TRUNC | O_WRONLY, 0777);
					dup2(fd, STDOUT_FILENO);
				}
				
				err = get_word(s->err);
				if(err != NULL) {
					//printf("err: %s\n", file);
					if(s->io_flags == IO_ERR_APPEND)
						fd = open(err, O_CREAT | O_WRONLY | O_APPEND, 0777);
					else
						if(out != NULL && (strcmp(out, err) != 0)) {
							fd = open(err, O_CREAT | O_TRUNC | O_WRONLY, 0777); }
							//printf("%s %s %d %d\n", out, err, strlen(out), strlen(err)); }
						else {
							close(fd);
							close(STDOUT_FILENO);
							fd = open(err, O_CREAT | O_APPEND | O_WRONLY, 0777);
						}
					dup2(fd, STDERR_FILENO);
				}
				out = NULL;
				err = NULL;
				
				char* aux = (char*) s->aux;
				if(aux != NULL) {
					//printf("INTRA AUX\n");
					//printf("%s %s\n", get_word(s->verb), aux);
					if(strstr(aux, "in") && strstr(aux, "out")) {
						int i = 0;
						in = calloc(strlen(aux), sizeof(char));
						//out = calloc(strlen(aux), sizeof(char));
						while(aux[i] != ' ') {
							in[i] = aux[i];
							i++;
						}
						file = &in[2];
						//printf("in: %s\n", file); 
						fd = open(file, O_RDONLY, 0777);
						dup2(fd, STDIN_FILENO);
						i++;
						out = &aux[i];
						file = &out[3];
						//printf("out: %s\n", file); 
						fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
						dup2(fd, STDOUT_FILENO);
						free(in);
						out = NULL;
					}
					else if(strstr(aux, "in")) {
						file = &aux[2];
						//printf("%s %d\n", file, strlen(file));
						fd = open(file, O_RDONLY, 0777);
						dup2(fd, STDIN_FILENO);
						
						if(strstr(aux, "out")) {
							
						}
					}
					else if(strstr(aux, "out")) {
						file = &aux[3];
						//printf("%s %d\n", file, strlen(file));
						fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
						dup2(fd, STDOUT_FILENO);
					}
				}

				execvp(get_word(s->verb), get_argv(s, &size));
				fprintf(stderr, "Execution failed for \'%s\'\n", get_word(s->verb));
				exit(EXIT_FAILURE);
						
			default:
				waitpid(pid, &status, 0);
				//DIE(ret < 0, "waitpid");
				ret = status;
		}
	}

	/* TODO if variable assignment, execute the assignment and return
	 * the exit status
	 */

	/* TODO if external command:
	 *   1. fork new process
	 *     2c. perform redirections in child
	 *     3c. load executable in child
	 *   2. wait for child
	 *   3. return exit status
	 */
	//printf("%s returned %d.\n", get_word(s->verb), ret);
	return ret; /* TODO replace with actual exit status */
}

/**
 * Process two commands in parallel, by creating two children.
 */
static bool do_in_parallel(command_t *cmd1, command_t *cmd2, int level,
		command_t *father)
{
	/* TODO execute cmd1 and cmd2 simultaneously */

	return true; /* TODO replace with actual exit status */
}

/**
 * Run commands by creating an anonymous pipe (cmd1 | cmd2)
 */
static bool do_on_pipe(command_t *cmd1, command_t *cmd2, int level,
		command_t *father)
{
	/* TODO redirect the output of cmd1 to the input of cmd2 */
	
	return true; /* TODO replace with actual exit status */
}

/**
 * Parse and execute a command.
 */
int parse_command(command_t *c, int level, command_t *father)
{
	pid_t p1, p2;
	int ret = 0;
	char pipe[30] = "pipe", in[32] = "in", out[33] = "out", nr[10];
	/* TODO sanity checks */
	
	if (c->op == OP_NONE) {
		//printf("%s %d\n", get_word(c->scmd->verb), level); 
		/* TODO execute a simple command */
		if(c->aux != NULL) {
			c->scmd->aux = calloc(30, sizeof(char));
			strcpy(c->scmd->aux, c->aux);
			//printf("%s\n", (char*)c->scmd->aux);
		}
		
		ret = parse_simple(c->scmd, level, father);
		
		if(c->aux != NULL) {
			free(c->scmd->aux);
		}
		return ret; /* TODO replace with actual exit code of command */
	}
	
	switch (c->op) {
	case OP_SEQUENTIAL:
		/* TODO execute the commands one after the other */
		parse_command(c->cmd1, level + 1, c);
		parse_command(c->cmd2, level + 1, c);
		break;

	case OP_PARALLEL:
		/* TODO execute the commands simultaneously */
		p1 = fork();
		if(p1 == 0) {
			parse_command(c->cmd1, level + 1, c);
			exit(0);
		}
		if(p1 > 0) {
			p2 = fork();
			if(p2 == 0) {
				parse_command(c->cmd2, level + 1, c);
				exit(0);
			}
			if(p2 > 0) {
				waitpid(p1, 0, 0);
				waitpid(p2, 0, 0);
			}
		}
		break;

	case OP_CONDITIONAL_NZERO:
		/* TODO execute the second command only if the first one
		 * returns non zero
		 */
		if(parse_command(c->cmd1, level + 1, c) != 0)
			ret = parse_command(c->cmd2, level + 1, c); 
		break;

	case OP_CONDITIONAL_ZERO:
		/* TODO execute the second command only if the first one
		 * returns zero
		 */
		if(parse_command(c->cmd1, level + 1, c) == 0)
		        ret = parse_command(c->cmd2, level + 1, c);
		break;

	case OP_PIPE:
		/* TODO redirect the output of the first command to the
		 * input of the second
		 */
		c->cmd1->aux = calloc(30, sizeof(char));
		c->cmd2->aux = calloc(30, sizeof(char));
		sprintf(nr, "%d", level);
		strcat(pipe, nr);
		strcat(in, pipe);
		strcat(out, pipe);
		strcpy(c->cmd1->aux, out);
		strcpy(c->cmd2->aux, in);
		if(c->aux != NULL) {
			strcat(c->cmd2->aux, " ");
			strcat(c->cmd2->aux, c->aux);
		}
		//mkfifo(pipe, 0777);
		int l = level + 1;
		//printf("%s         %s\n", c->cmd1->aux, c->cmd2->aux);
		parse_command(c->cmd1, l, c);
		//printf("IESE cmd1\n");
		ret = parse_command(c->cmd2, l, c);
		//printf("IESE cmd2\n");
		free(c->cmd1->aux);
		free(c->cmd2->aux);
		//unlink(pipe);
		
		pid_t pid;
		//system("rm -rf pipe*");
		pid = fork();
	
		switch(pid) {
		case -1:
			DIE(1, "error forking");
		case 0:
			execlp("rm", "rm", pipe, NULL);
		default:
			waitpid(pid, 0, 0);
		}
		break;

	default:
		return SHELL_EXIT;
	}

	return ret; /* TODO replace with actual exit code of command */
}
