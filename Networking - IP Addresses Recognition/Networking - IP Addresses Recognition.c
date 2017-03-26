#include<stdio.h>
#include<stdlib.h>


#define EPERM 1
#define EINVAL 2
#define ENOMEM 3


typedef struct 
{
    int R, G, B;
} pixel;


pixel** Initialization(pixel** im, int width, int height)	//Creeaza o matrice si o initializeaza, daca nu apare nicio eroare. Aceasta este returnata.
{
    int i, j;

    im = malloc(height * sizeof (pixel));

    if (im == NULL) 						//Se verifica alocarea liniilor.
    {
        fflush(stdout);

        fprintf(stderr, "%d\n", ENOMEM);

        exit(EXIT_FAILURE);
    }

    for (i = 0; i < height; i++) 
    {
        im[i] = calloc(width, sizeof (pixel));

        if (im[i] == NULL)					//Se verifica alocarea coloanelor.
	{
	    free(im);

            fflush(stdout);

            fprintf(stderr, "%d\n", ENOMEM);

            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < height; i++)				//Citirea elementelor. 
    {
        for (j = 0; j < width; j++) 
	{
            scanf("%d", &im[i][j].R);

            if (im[i][j].R < 0 || im[i][j].R > 255) 
	    {
                for (i = 0; i < height; i++) 
		{
                    free(im[i]);
                }

                free(im);

                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }

            scanf("%d", &im[i][j].G);

            if (im[i][j].G < 0 || im[i][j].G > 255) 
	    {
                for (i = 0; i < height; i++) 
		{
                    free(im[i]);
                }

                free(im);

                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }

            scanf("%d", &im[i][j].B);

            if (im[i][j].B < 0 || im[i][j].B > 255) 
	    {
                for (i = 0; i < height; i++) 
		{
                    free(im[i]);
                }

                free(im);

                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }
        }
    }

    return im;
}


pixel** Crop(pixel** im, int start_col, int start_line, int end_col, int end_line)	//Returneaza noua matrice modificata. 
{
    int i, j, k, l, width, height;

    width = end_col - start_col + 1;
    height = end_line - start_line + 1;

    pixel** aux = malloc(height * sizeof (pixel));					//Matricea cu noile dimensiuni.

    if (aux == NULL) 
    {
        fflush(stdout);

        fprintf(stderr, "%d\n", ENOMEM);

        exit(EXIT_FAILURE);
    }

    for (i = 0; i < height; i++) 
    {
        aux[i] = calloc(width, sizeof (pixel));

        if (aux[i] == NULL) 
	{
	    free(aux);

            fflush(stdout);

            fprintf(stderr, "%d\n", ENOMEM);

            exit(EXIT_FAILURE);
        }
    }

    for (i = start_line, k = 0; i <= end_line; i++, k++) 
    {
        for (j = start_col, l = 0; j <= end_col; j++, l++) 
	{
            aux[k][l] = im[i][j];							//Se copiaza elementele.
        }
    }

    return aux;
}


pixel** Copy(pixel** im, int width, int height, int width2, int height2)		//Returneaz o matrice copie, pentru operatia 6.
{
    int i, j;

    pixel** aux = malloc(height2 * sizeof (pixel));					//Matricea copie.

    if (aux == NULL) 
    {
        fflush(stdout);

        fprintf(stderr, "%d\n", ENOMEM);

        exit(EXIT_FAILURE);
    }

    for (i = 0; i < height2; i++) 
    {
        aux[i] = calloc(width2, sizeof (pixel));

        if (aux[i] == NULL)
	{
	    free(aux);

            fflush(stdout);

            fprintf(stderr, "%d\n", ENOMEM);

            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < height; i++) 
    {
        for (j = 0; j < width; j++) 
	{
            aux[i][j] = im[i][j];							//Copiaza elementele.
        }
    }

    return aux;
}


int main() 
{
    int op, i, j, k, width, height, start_col, start_line, end_col, end_line, width2, height2, num_iter, num_rot;
    
    pixel** im = NULL, **im2 = NULL; 							//Imaginea initiala si una auxiliara.

    do 
    {
        if (scanf("%d", &op) == EOF) 							//Daca nu faceam asta, imi repeta operatia 1 la infinit.
	{
            return 0;
        }

        if (op == 1) 
	{
            scanf("%d", &width); 							//coloane
            scanf("%d", &height); 							//linii

            if (height < 1 || height > 1024)
	    {
                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }

            if (width < 1 || width > 1024) 
	    {
                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }

            im = Initialization(im, width, height);					//Se creeaza si initializeaza matricea.

            continue;
        }

        if (op == 2) 
	{
            if (im == NULL)								//Se verifica daca matricea a fost creeata si initializata inainte. 
	    {
                fflush(stdout);

                fprintf(stderr, "%d\n", EPERM);

                exit(EXIT_FAILURE);
            }

            scanf("%d", &start_col);
            scanf("%d", &start_line);
            scanf("%d", &end_col);
            scanf("%d", &end_line);

            if (start_line < 0 || start_line > end_line || end_line < start_line || end_line >= height) 
	    {
                for (i = 0; i < height; i++) 
		{
                    free(im[i]);
                }

                free(im);

                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }

            if (start_col < 0 || start_col > end_col || end_col < start_col || end_col >= width) 
	    {
                for (i = 0; i < height; i++) 
		{
                    free(im[i]);
                }

                free(im);

                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }

            im = Crop(im, start_col, start_line, end_col, end_line);				//Se creeaza si initializeaza matricea cu noile dimensiuni.

            height = end_line - start_line + 1;							//Se setea noua inaltimea.
            width = end_col - start_col + 1;							//Se seteaza noua latime.

            continue;
        }

        if (op == 3) 
	{
            if (im == NULL) 
	    {
                fflush(stdout);

                fprintf(stderr, "%d\n", EPERM);

                exit(EXIT_FAILURE);
            }

            scanf("%d", &width2);
            scanf("%d", &height2);

            if (height2 < 1 || height2 > 1024) 
	    {
                for (i = 0; i < height; i++) 
		{
                    free(im[i]);
                }

                free(im);

                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }

            if (width2 < 1 || width2 > 1024) 
	    {
                for (i = 0; i < height; i++) 
		{
                    free(im[i]);
                }

                free(im);

                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }

            if (height2 <= height && width2 <= width) 
	    {
                im = Crop(im, 0, 0, width2 - 1, height2 - 1);
            }

            if (height2 > height) 
	    {
                im = Copy(im, width, height, width, height2);

                for (i = height; i < height2; i++)						//Se completeaza restul pixelilor. 
		{
                    for (j = 0; j < width; j++) 
		    {
                        im[i][j].R = 255;
                        im[i][j].G = 255;
                        im[i][j].B = 255;
                    }
                }

                height = height2;
            }

            if (width2 > width) 
	    {
                im = Copy(im, width, height, width2, height);

                for (i = 0; i < height; i++)							//Se completeaza restul pixelilor. 
		{
                    for (j = width; j < width2; j++) 
		    {
                        im[i][j].R = 255;
                        im[i][j].G = 255;
                        im[i][j].B = 255;
                    }
                }

                width = width2;
            }

            width = width2;
            height = height2;

            continue;
        }

        if (op == 4) 
	{
            if (im == NULL) 
	    {
                fflush(stdout);

                fprintf(stderr, "%d\n", EPERM);

                exit(EXIT_FAILURE);
            }

            pixel p;

            scanf("%d", &start_col);
            scanf("%d", &start_line);
            scanf("%d", &end_col);
            scanf("%d", &end_line);

            if (start_line < 0 || start_line > end_line || end_line < start_line || end_line >= height) 
	    {
                for (i = 0; i < height; i++) 
		{
                    free(im[i]);
                }

                free(im);

                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }

            if (start_col < 0 || start_col > end_col || end_col < start_col || end_col >= width) 
	    {
                for (i = 0; i < height; i++) 
		{
                    free(im[i]);
                }

                free(im);

                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }

            scanf("%d", &p.R);

            if (p.R < 0 || p.R > 255) 
	    {
                for (i = 0; i < height; i++) 
		{
                    free(im[i]);
                }

                free(im);

                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }

            scanf("%d", &p.G);

            if (p.G < 0 || p.G > 255) 
	    {
                for (i = 0; i < height; i++) 
		{
                    free(im[i]);
                }

                free(im);

                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }

            scanf("%d", &p.B);

            if (p.B < 0 || p.B > 255) 
	    {
                for (i = 0; i < height; i++) 
		{
                    free(im[i]);
                }

                free(im);

                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }

            for (i = start_line; i <= end_line; i++)						//Se seteaza noile culori ale pixelilor.
	    {
                for (j = start_col; j <= end_col; j++) 
		{
                    im[i][j].R = p.R;
                    im[i][j].G = p.G;
                    im[i][j].B = p.B;
                }
            }
        }

        if (op == 5) 
	{
            if (im == NULL) 
	    {
                fflush(stdout);

                fprintf(stderr, "%d\n", EPERM);

                exit(EXIT_FAILURE);

                return 0;
            }

            im2 = Copy(im, width, height, width, height);					//Copie a matricii, ce va retine media pixelilor.

            scanf("%d", &num_iter);

            if (num_iter < 0 || num_iter > 2000) 
	    {
                for (i = 0; i < height; i++) 
		{
                    free(im[i]);
                    free(im2[i]);
                }

                free(im);
                free(im2);

                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }

            for (k = 0; k < num_iter; k++) 
	    {
                for (i = 0; i < height; i++) 
		{
                    for (j = 0; j < width; j++) 
		    {
                        if (i == 0)								//Prima linie. 
			{
                            if (j == 0)								//Prima coloana.
			    {
                                im2[i][j].R = (im[i][j + 1].R + im[i + 1][j].R) / 2;
                                im2[i][j].G = (im[i][j + 1].G + im[i + 1][j].G) / 2;
                                im2[i][j].B = (im[i][j + 1].B + im[i + 1][j].B) / 2;

                                continue;
                            }

                            if (j == width - 1)							//Ultima coloana.
			    {
                                im2[i][j].R = (im[i][j - 1].R + im[i + 1][j].R) / 2;
                                im2[i][j].G = (im[i][j - 1].G + im[i + 1][j].G) / 2;
                                im2[i][j].B = (im[i][j - 1].B + im[i + 1][j].B) / 2;

                                continue;
                            }

                            im2[i][j].R = (im[i][j - 1].R + im[i][j + 1].R + im[i + 1][j].R) / 3;
                            im2[i][j].G = (im[i][j - 1].G + im[i][j + 1].G + im[i + 1][j].G) / 3;
                            im2[i][j].B = (im[i][j - 1].B + im[i][j + 1].B + im[i + 1][j].B) / 3;

                            continue;
                        }

                        if (j == 0 && i != 0 && i != height - 1) 				//Prima coloana si orice linie in afara de cele externe.
			{
                            im2[i][j].R = (im[i][j + 1].R + im[i - 1][j].R + im[i + 1][j].R) / 3;
                            im2[i][j].G = (im[i][j + 1].G + im[i - 1][j].G + im[i + 1][j].G) / 3;
                            im2[i][j].B = (im[i][j + 1].B + im[i - 1][j].B + im[i + 1][j].B) / 3;

                            continue;
                        }

                        if (j == width - 1 && i != 0 && i != height - 1) 			//Ultima coloana si orice linie in afara de cele externe.
			{
                            im2[i][j].R = (im[i][j - 1].R + im[i - 1][j].R + im[i + 1][j].R) / 3;
                            im2[i][j].G = (im[i][j - 1].G + im[i - 1][j].G + im[i + 1][j].G) / 3;
                            im2[i][j].B = (im[i][j - 1].B + im[i - 1][j].B + im[i + 1][j].B) / 3;

                            continue;
                        }

                        if (i == height - 1)							//Ultima linie.
			{
                            if (j == 0)								//Prima coloana. 
			    {
                                im2[i][j].R = (im[i][j + 1].R + im[i - 1][j].R) / 2;
                                im2[i][j].G = (im[i][j + 1].G + im[i - 1][j].G) / 2;
                                im2[i][j].B = (im[i][j + 1].B + im[i - 1][j].B) / 2;

                                continue;
                            }

                            if (j == width - 1)							//Ultima coloana.
			    {
                                im2[i][j].R = (im[i][j - 1].R + im[i - 1][j].R) / 2;
                                im2[i][j].G = (im[i][j - 1].G + im[i - 1][j].G) / 2;
                                im2[i][j].B = (im[i][j - 1].B + im[i - 1][j].B) / 2;

                                continue;
                            }

                            im2[i][j].R = (im[i][j - 1].R + im[i][j + 1].R + im[i - 1][j].R) / 3;
                            im2[i][j].G = (im[i][j - 1].G + im[i][j + 1].G + im[i - 1][j].G) / 3;
                            im2[i][j].B = (im[i][j - 1].B + im[i][j + 1].B + im[i - 1][j].B) / 3;

                            continue;
                        }

                        im2[i][j].R = (im[i][j - 1].R + im[i][j + 1].R + im[i - 1][j].R + im[i + 1][j].R) / 4;
                        im2[i][j].G = (im[i][j - 1].G + im[i][j + 1].G + im[i - 1][j].G + im[i + 1][j].G) / 4;
                        im2[i][j].B = (im[i][j - 1].B + im[i][j + 1].B + im[i - 1][j].B + im[i + 1][j].B) / 4;
                    }
                }
            }

            for (i = 0; i < height; i++) 
	    {
                free(im[i]);
            }

            free(im);

            im = im2;										//Matricea initiala devine cea noua.
        }

        if (op == 6) 
	{
            if (im == NULL) 
	    {
                fflush(stdout);

                fprintf(stderr, "%d\n", EPERM);

                exit(EXIT_FAILURE);
            }

            scanf("%d", &num_rot);

            if (num_rot < 1 || num_rot > 3) 
	    {
                for (i = 0; i < height; i++) 
		{
                    free(im[i]);
                }

                free(im);

                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }
        }

        if (op == 7) 
	{
            pixel p;

            if (im == NULL) 
	    {
                fflush(stdout);

                fprintf(stderr, "%d\n", EPERM);

                exit(EXIT_FAILURE);
            }

            scanf("%d", &start_col);

            if (start_col < 0 || start_col > width) 
	    {
                for (i = 0; i < height; i++) 
		{
                    free(im[i]);
                }

                free(im);

                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }

            scanf("%d", &start_line);

            if (start_line < 0 || start_line > height) 
	    {
                for (i = 0; i < height; i++) 
		{
                    free(im[i]);
                }

                free(im);

                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }

            scanf("%d", &p.R);

            if (p.R < 0 || p.R > 255) 
	    {
                for (i = 0; i < height; i++) 
		{
                    free(im[i]);
                }

                free(im);

                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }

            scanf("%d", &p.G);

            if (p.G < 0 || p.G > 255) 
	    {
                for (i = 0; i < height; i++) 
		{
                    free(im[i]);
                }

                free(im);

                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }

            scanf("%d", &p.B);

            if (p.B < 0 || p.B > 255) 
	    {
                for (i = 0; i < height; i++) 
		{
                    free(im[i]);
                }

                free(im);

                fflush(stdout);

                fprintf(stderr, "%d\n", EINVAL);

                exit(EXIT_FAILURE);
            }
        }

        if (op == 8) 
	{
            if (im == NULL) 
	    {
                fflush(stdout);

                fprintf(stderr, "%d\n", EPERM);

                exit(EXIT_FAILURE);
            }

            printf("%d ", width);
            printf("%d\n", height);

            for (i = 0; i < height; i++) 
	    {
                for (j = 0; j < width; j++) 
		{
                    if (j == width - 1 && i < height - 1) 
		    {
                        printf("%d ", im[i][j].R);
                        printf("%d ", im[i][j].G);
                        printf("%d\n", im[i][j].B);

                        continue;
                    }

                    if (j == width - 1 && i == height - 1) 
		    {
                        printf("%d ", im[i][j].R);
                        printf("%d ", im[i][j].G);
                        printf("%d", im[i][j].B);

                        continue;
                    }

                    printf("%d ", im[i][j].R);
                    printf("%d ", im[i][j].G);
                    printf("%d ", im[i][j].B);
                }
            }
        }

        if (op == 0) 
	{
            if (im == NULL) 
	    {
                return 0;
            }

            for (i = 0; i < height; i++) 
	    {
                free(im[i]);
            }

            free(im);

            return 0;
        }

        if (op > 8 || op < 0) 
	{
            for (i = 0; i < height; i++) 
	    {
                free(im[i]);
            }

            free(im);

            fflush(stdout);

            fprintf(stderr, "%d\n", EPERM);

            exit(EXIT_FAILURE);
        }
    } while (1);

    return 0;
}
