#include <iostream>
#include <vector>
#include <string>

#include <Core/Engine.h>

#include "RacingGame.h"


using namespace std;


RacingGame::RacingGame()
{
}

RacingGame::~RacingGame()
{
}

Highway::Highway()
{
}

Highway::~Highway()
{
}

Sky::Sky()
{
}

Sky::~Sky()
{
}

Earth::Earth()
{
}

Earth::~Earth()
{
}

Car::Car()
{
}

Car::~Car()
{
}


// Actualizeaza timpul zilei.
void RacingGame::getTime()
{
	if (time >= 2.7)	// daca e prea intuneric
		night_or_day = 1;	// incepe sa se lumineze

	if (time <= 0)	// incepe sa se intunece
		night_or_day = 0;

	if (night_or_day == 0)
		time += 0.0015;

	if (night_or_day == 1)
	{
		time -= 0.0015;
	}
}

// Metoda de initializare.
void RacingGame::Init()
{
	camera = new Camera::Camera();

	Mesh* s = CreateMesh("sky", sky.vertices, sky.indices);
	Mesh* c = CreateMesh("car", car.vertices, car.indices);
	Mesh* obstacle = CreateMesh("obstacle", hw.vertices5, hw.indices5);
	Mesh* road = CreateMesh("road", hw.vertices, hw.indices);

	// se creeaza punctele pentru curba la stanga
	hw.BuildLeftCurve();
	Mesh* left_curve = CreateMesh("left_curve", hw.vertices3, hw.indices3);

	// se creeaza punctele pentru curba la dreapta
	hw.BuildRightCurve();
	Mesh* right_curve = CreateMesh("right_curve", hw.vertices4, hw.indices4);

	Mesh* border = CreateMesh("border", hw.vertices2, hw.indices2);
	Mesh* e = CreateMesh("earth", earth.vertices, earth.indices);

	Shader *shader = new Shader("shader");
	shader->AddShader("Source/Laboratoare/Laborator6/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Laboratoare/Laborator6/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
	shaders[shader->GetName()] = shader;

	// pozitia initiala a camerei
	camera->Set(glm::vec3(2.5, 2, 4), glm::vec3(2.5, 2, -1), glm::vec3(0, 1, 0));
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 300.0f);

	polygonMode = GL_FILL;

	// numarul segmentelor strazii
	hw.nr_parts = 9;

	// pozitia obstacolului
	hw.obstacle_position = hw.border_length * 7;

	// lungimea unui segment al strazii
	hw.length = 10;

	sky.color = glm::vec3(0 / 255.0, 191 / 255.0, 255 / 255.0);
	car.color = glm::vec3(0, 0, 0);
	hw.obstacle_color = glm::vec3(0, 0, 0.5);
	hw.road_color = glm::vec3(128 / 255.0, 128 / 255.0, 128 / 255.0);
	hw.border_color = glm::vec3(240 / 255.0, 255 / 255.0, 0 / 255.0);
	earth.color = glm::vec3(124 / 255.0, 252 / 255.0, 0 / 255.0);
}


Mesh* RacingGame::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	// Create the VAO and bind it
	unsigned int VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}


void RacingGame::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}


void RacingGame::Update(float deltaTimeSeconds)
{
	
	int i;
	int dir = 0;
	glm::mat4 aux;

	// wireframe sau solid
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
	glLineWidth(2);

	getTime();

	hw.length = 10;
	hw.length2 = hw.length * (hw.road_length / hw.border_length);
	hw.length3 = hw.length * (hw.road_length / hw.border_length);

	car.modelMatrix = glm::mat4(1);
	hw.obstacle_modelMatrix = glm::mat4(1);
	hw.road_modelMatrix = glm::mat4(1);
	hw.curve_modelMatrix = glm::mat4(1);
	hw.left_border_modelMatrix = glm::mat4(1);
	hw.right_border_modelMatrix = glm::mat4(1);

	// masina e pozitionata pe banda dreapta
	car.modelMatrix = glm::translate(car.modelMatrix, glm::vec3(2, 0, 0));
	car.modelMatrix = glm::translate(car.modelMatrix, car.translation);

	// partea de sus a masinii
	aux = car.modelMatrix;
	aux = glm::translate(aux, glm::vec3(0.25, 0.5, 0));
	aux = glm::scale(aux, glm::vec3(0.5, 0.5, 0.4));


	RenderSimpleMesh(meshes["sky"], shaders["shader"], glm::mat4(1), sky.color);
	RenderSimpleMesh(meshes["car"], shaders["shader"], car.modelMatrix, car.color);
	RenderSimpleMesh(meshes["car"], shaders["shader"], aux, glm::vec3(1, 0, 0));
	RenderSimpleMesh(meshes["earth"], shaders["shader"], glm::mat4(1), earth.color);

	hw.right_border_modelMatrix = glm::translate(hw.right_border_modelMatrix, glm::vec3(hw.road_width + hw.border_width, 0, 0));
	hw.curve_modelMatrix = glm::translate(hw.curve_modelMatrix, glm::vec3(hw.road_width, 0, 0));

	// tranzitiile specifice fiecarei piese a strazii
	hw.obstacle_modelMatrix = glm::translate(hw.obstacle_modelMatrix, glm::vec3(hw.road_width / 2, 0, -hw.road_length * 7));
	hw.road_translation = glm::vec3(0, 0, -hw.road_length);
	hw.left_border_translation = glm::vec3(0, 0, -hw.border_length);
	hw.right_border_translation = glm::vec3(0, 0, -hw.border_length);

	for (int j = 0; j < hw.nr_parts; j++)
	{
		aux = glm::mat4(1);
		angle = (float)((M_PI / 2) - (M_PI / hw.curve_angle));

		// segment de sosea
		for (i = 0; i < hw.length; i++)
		{
			RenderSimpleMesh(meshes["road"], shaders["shader"], hw.road_modelMatrix, hw.road_color);
			
			hw.road_modelMatrix = glm::translate(hw.road_modelMatrix, hw.road_translation);
			hw.curve_modelMatrix = glm::translate(hw.curve_modelMatrix, hw.road_translation);

			if (i == hw.length - 3)
			{
				//hw.obstacle_modelMatrix = hw.road_modelMatrix;

				RenderSimpleMesh(meshes["obstacle"], shaders["shader"], hw.obstacle_modelMatrix, hw.obstacle_color);
			}

			
		}

		// segment de bordura stanga
		for (i = 0; i < hw.length2; i++)
		{
			RenderSimpleMesh(meshes["border"], shaders["shader"], hw.left_border_modelMatrix, hw.border_color);

			hw.left_border_modelMatrix = glm::translate(hw.left_border_modelMatrix, hw.left_border_translation);
		}

		// segment de bordura dreapta
		for (i = 0; i < hw.length3; i++)
		{
			RenderSimpleMesh(meshes["border"], shaders["shader"], hw.right_border_modelMatrix, hw.border_color);

			hw.right_border_modelMatrix = glm::translate(hw.right_border_modelMatrix, hw.right_border_translation);
		}

		// Se actualizeaza pozitiile (matricile de modelare) si tranzitiile 
		// pentru curba dreapta si al doilea segment.
		if (j == 0)
		{
			RenderSimpleMesh(meshes["right_curve"], shaders["shader"], hw.curve_modelMatrix, hw.road_color);

			aux = hw.left_border_modelMatrix;
			aux = glm::rotate(aux, -angle, glm::vec3(0, 1, 0));
			RenderSimpleMesh(meshes["border"], shaders["shader"], aux, hw.border_color);

			hw.road_modelMatrix = hw.curve_modelMatrix;
			hw.road_modelMatrix = glm::rotate(hw.road_modelMatrix, angle, glm::vec3(0, 1, 0));
			hw.road_translation = glm::vec3(hw.road_width, 0, 0);

			hw.obstacle_modelMatrix = hw.road_modelMatrix;
			hw.obstacle_modelMatrix = glm::translate(hw.obstacle_modelMatrix, 
													 glm::vec3(hw.obstacle_position, 0, -hw.road_length / 2));

			hw.left_border_modelMatrix = hw.curve_modelMatrix;
			hw.left_border_modelMatrix = glm::rotate(hw.left_border_modelMatrix, angle, glm::vec3(0, 1, 0));
			hw.left_border_modelMatrix = glm::translate(hw.left_border_modelMatrix, glm::vec3(0, 0, -(hw.road_length)));
			hw.left_border_modelMatrix = glm::rotate(hw.left_border_modelMatrix, -(float)M_PI / 2, glm::vec3(0, 1, 0));

			hw.right_border_modelMatrix = hw.curve_modelMatrix;
			hw.right_border_modelMatrix = glm::rotate(hw.right_border_modelMatrix, angle, glm::vec3(0, 1, 0));
			hw.right_border_modelMatrix = glm::translate(hw.right_border_modelMatrix, glm::vec3(0, 0, hw.border_width));
			hw.right_border_modelMatrix = glm::rotate(hw.right_border_modelMatrix, -(float)M_PI / 2, glm::vec3(0, 1, 0));

		}

		// Se actualizeaza pozitiile (matricile de modelare) si tranzitiile 
		// pentru curba stanga si al treilea segment.
		if (j == 1)
		{
			hw.road_translation = glm::vec3(0, 0, -hw.road_length);

			hw.obstacle_modelMatrix = hw.road_modelMatrix;
			hw.obstacle_modelMatrix = glm::translate(hw.obstacle_modelMatrix, 
													 glm::vec3(hw.road_width / 2, 0, -hw.obstacle_position));

			hw.left_border_modelMatrix = hw.road_modelMatrix;
			hw.left_border_modelMatrix = glm::translate(hw.left_border_modelMatrix, glm::vec3(0, 0, -hw.road_length));
			hw.length2 -= hw.road_length / hw.border_length;

			RenderSimpleMesh(meshes["border"], shaders["shader"], hw.right_border_modelMatrix, hw.border_color);
			hw.right_border_modelMatrix = hw.road_modelMatrix;
			hw.right_border_modelMatrix = glm::translate(hw.right_border_modelMatrix, 
														 glm::vec3(hw.road_length + hw.border_width, 0, 0));
		}

		// Se actualizeaza pozitiile (matricile de modelare) si tranzitiile 
		// pentru curba stanga si al patrulea segment.
		if (j == 2)
		{
			hw.curve_modelMatrix = hw.road_modelMatrix;
			RenderSimpleMesh(meshes["left_curve"], shaders["shader"], hw.curve_modelMatrix, hw.road_color);

			hw.road_modelMatrix = glm::rotate(hw.road_modelMatrix, -angle, glm::vec3(0, 1, 0));
			hw.road_modelMatrix = glm::translate(hw.road_modelMatrix, glm::vec3(-hw.road_width, 0, 0));
			hw.road_translation = glm::vec3(-hw.road_width, 0, 0);

			hw.obstacle_modelMatrix = hw.road_modelMatrix;
			hw.obstacle_modelMatrix = glm::translate(hw.obstacle_modelMatrix, 
													 glm::vec3(-hw.obstacle_position, 0, -hw.road_width / 2));

			hw.left_border_modelMatrix = hw.road_modelMatrix;
			hw.left_border_modelMatrix = glm::translate(hw.left_border_modelMatrix, glm::vec3(hw.road_length, 0, 0));

			hw.left_border_modelMatrix = glm::rotate(hw.left_border_modelMatrix, float(M_PI / 2), glm::vec3(0, 1, 0));
			hw.length2 += hw.road_length / hw.border_length;

			aux = hw.right_border_modelMatrix;
			aux = glm::rotate(aux, angle, glm::vec3(0, 1, 0));
			aux = glm::translate(aux, glm::vec3(0, 0, -0.25));
			RenderSimpleMesh(meshes["border"], shaders["shader"], aux, hw.border_color);

			hw.right_border_modelMatrix = hw.road_modelMatrix;
			hw.right_border_modelMatrix = glm::translate(hw.right_border_modelMatrix, 
														 glm::vec3(hw.road_length, 0, -(hw.road_length + hw.border_width)));
			hw.right_border_modelMatrix = glm::rotate(hw.right_border_modelMatrix, float(M_PI / 2), glm::vec3(0, 1, 0));
		}

		// Se actualizeaza pozitiile (matricile de modelare) si tranzitiile 
		// pentru curba stanga si al cincilea segment.
		if (j == 4)
		{
			hw.curve_modelMatrix = hw.road_modelMatrix;
			hw.curve_modelMatrix = glm::rotate(hw.curve_modelMatrix, float(M_PI / 2), glm::vec3(0, 1, 0));
			hw.curve_modelMatrix = glm::translate(hw.curve_modelMatrix, glm::vec3(0, 0, hw.road_width));
			RenderSimpleMesh(meshes["left_curve"], shaders["shader"], hw.curve_modelMatrix, hw.road_color);

			aux = hw.right_border_modelMatrix;
			aux = glm::rotate(aux, angle, glm::vec3(0, 1, 0));
			aux = glm::translate(aux, glm::vec3(0, 0, -0.25));
			RenderSimpleMesh(meshes["border"], shaders["shader"], aux, hw.border_color);

			hw.road_modelMatrix = hw.curve_modelMatrix;
			hw.road_modelMatrix = glm::rotate(hw.road_modelMatrix, -angle, glm::vec3(0, 1, 0));
			hw.road_modelMatrix = glm::translate(hw.road_modelMatrix, glm::vec3(-hw.road_length, 0, 0));

			hw.obstacle_modelMatrix = hw.road_modelMatrix;
			hw.obstacle_modelMatrix = glm::translate(hw.obstacle_modelMatrix, 
													 glm::vec3(-hw.obstacle_position, 0, -hw.road_width / 2));

			hw.left_border_modelMatrix = hw.curve_modelMatrix;
			hw.left_border_modelMatrix = glm::rotate(hw.left_border_modelMatrix, -angle, glm::vec3(0, 1, 0));
			hw.left_border_modelMatrix = glm::rotate(hw.left_border_modelMatrix, (float)M_PI / 2, glm::vec3(0, 1, 0));

			hw.right_border_modelMatrix = hw.curve_modelMatrix;
			hw.right_border_modelMatrix = glm::rotate(hw.right_border_modelMatrix, -angle, glm::vec3(0, 1, 0));
			hw.right_border_modelMatrix = glm::translate(hw.right_border_modelMatrix, glm::vec3(0, 0, -(hw.road_length + hw.border_width)));
			hw.right_border_modelMatrix = glm::rotate(hw.right_border_modelMatrix, (float)M_PI / 2, glm::vec3(0, 1, 0));
		}

		// Se actualizeaza pozitiile (matricile de modelare) si tranzitiile 
		// pentru curba stanga si al saselea segment.
		if (j == 5)
		{
			hw.road_translation = glm::vec3(0, 0, hw.road_length);

			hw.obstacle_modelMatrix = hw.road_modelMatrix;
			hw.obstacle_modelMatrix = glm::translate(hw.obstacle_modelMatrix, 
													 glm::vec3(hw.road_length / 2, 0, hw.obstacle_position));

			RenderSimpleMesh(meshes["border"], shaders["shader"], hw.right_border_modelMatrix, hw.border_color);

			hw.left_border_modelMatrix = hw.road_modelMatrix;
			hw.left_border_modelMatrix = glm::translate(hw.left_border_modelMatrix, glm::vec3(hw.road_length + hw.border_width, 0, hw.road_length));
			hw.left_border_translation = hw.road_translation;
			hw.length2 -= hw.road_length / hw.border_length;

			hw.right_border_modelMatrix = hw.road_modelMatrix;
			hw.right_border_translation = hw.road_translation;

		}

		// Se actualizeaza pozitiile (matricile de modelare) si tranzitiile 
		// pentru curba stanga si al saptelea segment.
		if (j == 6)
		{
			hw.curve_modelMatrix = hw.road_modelMatrix;
			hw.curve_modelMatrix = glm::translate(hw.curve_modelMatrix, glm::vec3(0, 0, -hw.road_width));
			hw.curve_modelMatrix = glm::rotate(hw.curve_modelMatrix, -float(M_PI / hw.curve_angle), glm::vec3(0, 1, 0));
			RenderSimpleMesh(meshes["left_curve"], shaders["shader"], hw.curve_modelMatrix, hw.road_color);

			hw.road_modelMatrix = hw.curve_modelMatrix;
			hw.road_modelMatrix = glm::translate(hw.road_modelMatrix, glm::vec3(0, 0, hw.road_width));

			hw.obstacle_modelMatrix = hw.road_modelMatrix;
			hw.obstacle_modelMatrix = glm::translate(hw.obstacle_modelMatrix, 
													 glm::vec3(0, 0, hw.obstacle_position));

			hw.right_border_modelMatrix = hw.curve_modelMatrix;
			hw.right_border_modelMatrix = glm::translate(hw.right_border_modelMatrix, glm::vec3(0, 0, hw.road_length));
			hw.length3 += hw.road_length / hw.border_length;

			hw.left_border_modelMatrix = hw.curve_modelMatrix;
			hw.left_border_modelMatrix = glm::translate(hw.left_border_modelMatrix, glm::vec3(hw.road_width + hw.border_width, 0, 0));
			hw.left_border_modelMatrix = glm::translate(hw.left_border_modelMatrix, glm::vec3(0, 0, hw.road_width));
			hw.length2 += hw.road_length / hw.border_length;

			aux = hw.left_border_modelMatrix;
			aux = glm::translate(aux, glm::vec3(0, 0, -0.27));
			aux = glm::translate(aux, glm::vec3(0, 0, -hw.border_length));
			aux = glm::rotate(aux, angle, glm::vec3(0, 1, 0));
			RenderSimpleMesh(meshes["border"], shaders["shader"], aux, hw.border_color);
		}

		// Se actualizeaza pozitiile (matricile de modelare) si tranzitiile 
		// pentru ultimul segment.
		if (j == 7)
		{
			hw.road_translation = glm::vec3(hw.road_length, 0, 0);
			hw.length += (hw.road_length / hw.border_length) * 4;

			hw.obstacle_modelMatrix = hw.road_modelMatrix;
			hw.obstacle_modelMatrix = glm::translate(hw.obstacle_modelMatrix, 
													 glm::vec3(hw.obstacle_position, 0, -hw.road_width / 2));

			hw.left_border_modelMatrix = glm::translate(hw.left_border_modelMatrix, glm::vec3(0, 0, -(hw.border_length + hw.border_width)));
			hw.left_border_modelMatrix = glm::rotate(hw.left_border_modelMatrix, (float)M_PI / 2, glm::vec3(0, 1, 0));
			hw.left_border_modelMatrix = glm::translate(hw.left_border_modelMatrix, glm::vec3(0, 0, hw.border_length));
			hw.length3 += hw.road_length / hw.border_length * 3;

			hw.right_border_modelMatrix = glm::rotate(hw.right_border_modelMatrix, (float)M_PI / 2, glm::vec3(0, 1, 0));
			hw.right_border_modelMatrix = glm::translate(hw.right_border_modelMatrix, glm::vec3(hw.road_length, 0, hw.border_length));
			hw.length2 += hw.road_length / hw.border_length * 2;
		}
	}

	// ultimele parti ale strazii, conectate
	hw.road_modelMatrix = glm::translate(hw.road_modelMatrix, glm::vec3(-hw.road_length + 0.5, 0, 0));
	RenderSimpleMesh(meshes["road"], shaders["shader"], hw.road_modelMatrix, hw.road_color);

	hw.road_modelMatrix = glm::translate(hw.road_modelMatrix, glm::vec3(-0.3, 0, -hw.road_length));
	RenderSimpleMesh(meshes["road"], shaders["shader"], hw.road_modelMatrix, hw.road_color);

	hw.left_border_modelMatrix = glm::mat4(1);
	hw.right_border_modelMatrix = glm::mat4(1);

	hw.left_border_modelMatrix = glm::translate(hw.left_border_modelMatrix, glm::vec3(0, 0, 1.3));
	RenderSimpleMesh(meshes["border"], shaders["shader"], hw.left_border_modelMatrix, hw.border_color);
	
	hw.right_border_modelMatrix = glm::translate(hw.right_border_modelMatrix, glm::vec3(0, 0, 4));
	hw.right_border_modelMatrix = glm::translate(hw.right_border_modelMatrix, glm::vec3(hw.road_width + hw.border_width, 0, 0));
	RenderSimpleMesh(meshes["border"], shaders["shader"], hw.right_border_modelMatrix, hw.border_color);

	hw.right_border_modelMatrix = glm::translate(hw.right_border_modelMatrix, glm::vec3(0, 0, 2));
	RenderSimpleMesh(meshes["border"], shaders["shader"], hw.right_border_modelMatrix, hw.border_color);

	// Tranzitiile masinii
	if (carDirection == up)
	{
		car.translation.z -= deltaTimeSeconds * speed;

		car.modelMatrix = glm::translate(car.modelMatrix, car.translation);

		carDirection = stop;
	}

	if (carDirection == left)
	{
		car.translation.x -= deltaTimeSeconds * speed;

		car.modelMatrix = glm::translate(car.modelMatrix, car.translation);

		carDirection = stop;
	}

	if (carDirection == down)
	{
		car.translation.z += deltaTimeSeconds * speed;

		car.modelMatrix = glm::translate(car.modelMatrix, car.translation);

		carDirection = stop;
	}

	if (carDirection == right)
	{
		car.translation.x += deltaTimeSeconds * speed;

		car.modelMatrix = glm::translate(car.modelMatrix, car.translation);

		carDirection = stop;
	}
}


 void RacingGame::FrameEnd()
{
	//DrawCoordinatSystem();
}


void RacingGame::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, glm::vec3 color)
{
	int location;

	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	location = glGetUniformLocation(shader->GetProgramID(), "Model");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glm::mat4 viewMatrix = camera->GetViewMatrix();
	location = glGetUniformLocation(shader->GetProgramID(), "View");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	location = glGetUniformLocation(shader->GetProgramID(), "Projection");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	location = glGetUniformLocation(shader->GetProgramID(), "object_color");
	glUniform3fv(location, 1, glm::value_ptr(color));

	location = glGetUniformLocation(shader->GetProgramID(), "time");
	glUniform1f(location, time);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}


void RacingGame::OnInputUpdate(float deltaTime, int mods)
{
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		if (window->KeyHold(GLFW_KEY_W))
		{
			camera->TranslateForward((deltaTime * speed));

			carDirection = up;
		}

		if (window->KeyHold(GLFW_KEY_A))
		{
			camera->TranslateRight(-(deltaTime * speed));

			carDirection = left;
		}

		if (window->KeyHold(GLFW_KEY_S))
		{
			camera->TranslateForward(-(deltaTime * speed));
			
			carDirection = down;
		}

		if (window->KeyHold(GLFW_KEY_D))
		{
			camera->TranslateRight(deltaTime * speed);

			carDirection = right;
		}

		if (window->KeyHold(GLFW_KEY_Q)) 
		{
			camera->TranslateRight(-deltaTime * speed);

			camera->TranslateUpword(-deltaTime * speed);
		}

		if (window->KeyHold(GLFW_KEY_E))
		{
			camera->TranslateUpword(deltaTime * speed);
		}
	}
}


void RacingGame::OnKeyPress(int key, int mods)
{
	// wireframe sau solid
	if (key == GLFW_KEY_SPACE)
	{
		switch (polygonMode)
		{
		case GL_LINE:
			polygonMode = GL_FILL;
			break;

		default:
			polygonMode = GL_LINE;
			break;
		}
	}
}


void RacingGame::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) 
		{
			camera->RotateFirstPerson_OX(-deltaY * sensivityOY);
			camera->RotateFirstPerson_OY(-deltaX * sensivityOX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL)
		{
			camera->RotateThirdPerson_OX(-deltaY * sensivityOY);
			camera->RotateThirdPerson_OY(-deltaX * sensivityOX);
		}
	}
}


void RacingGame::OnKeyRelease(int key, int mods)
{
}
