#include <iostream>

#include <vector>
#include <Core/Engine.h>

#include "Transform2D.h"
#include "Tema1.h"
#include "LandingPlatform.h"
#include "ReflectionPlatform.h"
#include "FinalPlatform.h"
#include "Asteroid.h"

using namespace std;


Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

Astronaut::Astronaut()
{
}

Astronaut::~Astronaut()
{
}

LandingPlatform::LandingPlatform()
{
}

LandingPlatform::~LandingPlatform()
{
}

ReflectionPlatform::ReflectionPlatform()
{
}

ReflectionPlatform::~ReflectionPlatform()
{
}

FinalPlatform::FinalPlatform()
{
}

FinalPlatform::~FinalPlatform()
{
}

Asteroid::Asteroid()
{
}

Asteroid::~Asteroid()
{
}


// Initializari, creare de meshe, obtinere puncte asteroid.
void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	//// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;

	//// initialize tx and ty (the translation steps)
	translateX = 0;
	translateY = 0;

	//// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;

	//// initialize angularStep
	angularStep = 0;

	as.radius = 40;
	as.num_vertices = 12;

	as.vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0, 1))); // punctul din mijloc asteroidului

	for (int i = 0; i < as.num_vertices; i++) // se creeaza puncte
	{
		as.vertices.push_back(VertexFormat(
			                               glm::vec3((as.radius * cos(i * 2 * M_PI / as.num_vertices)),
			                               (as.radius * sin(i * 2 * M_PI / as.num_vertices)), 0), glm::vec3(1, 0, 1))
										  );
	}

	as2 = as;

	Mesh *astronaut = CreateMesh("astro", astro.vertices, astro.indices);
	meshes["astro"] = astronaut;

	Mesh *landing_platform = CreateMesh("landing_platform", lp.vertices, lp.indices);
	meshes["landing_platform"] = landing_platform;

	Mesh *reflection_platform = CreateMesh("reflection_platform", rp.vertices, rp.indices);
	meshes["reflection_platform"] = reflection_platform;

	Mesh *asteroid = CreateMesh("asteroid", as.vertices, as.indices);
	meshes["asteroid"] = asteroid;

	Mesh *asteroid2 = CreateMesh("asteroid2", as2.vertices, as2.indices);
	meshes["asteroid2"] = asteroid2;

	Mesh *final_platform = CreateMesh("final_platform", fp.vertices, fp.indices);
	meshes["final_platform"] = final_platform;

	initial_pos = astro.v1; // pozitia initiala a astronautului
	last_pos = astro.v1;	//pozitia precedenta a astronautului

	initialtX = 0;
	initialtY = 0;

	as.cx = as.vertices[0].position.x;
	as.cy = as.vertices[0].position.y;

	as2.cx = as.vertices[0].position.x;
	as2.cy = as.vertices[0].position.y;

	as.initial_pos.x = 1000;
	as.initial_pos.y = 200;

	as2.initial_pos.x = 600;
	as2.initial_pos.y = 500;

	as.cx = as.initial_pos.x;
	as.cy = as.initial_pos.y;

	as2.cx = as2.initial_pos.x;
	as2.cy = as2.initial_pos.y;
}



Mesh* Tema1::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO = 0;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	unsigned int IBO = 0;

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);
	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data
	// It will be learned later, when GLSL shaders will be introduced
	// For the moment just think that each property value from our vertex format needs to be send to a certain channel
	// in order to know how to receive it in the GLSL vertex shader

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// TODO: Unbind the VAO
	glBindVertexArray(0);
	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	return meshes[name];
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}







// Calculeaza translatia initiala, pozitia varfului si unghiul de rotatie,
// in functie de latura.
void Tema1::LandingPlatformCollision(int scenario)
{
	//jos
	if (scenario == 1)
	{
		initialtX = astro.v1.x - initial_pos.x;
		initialtY = lp.v1.y - initial_pos.y - initial_pos.y;

		astro.v1.y = lp.v1.y - initial_pos.y;

		r = -M_PI;
	}

	//stanga
	if (scenario == 2)
	{
		initialtX = (lp.v1.x - initial_pos.y) - initial_pos.x;
		initialtY = astro.v1.y - initial_pos.y;

		astro.v1.x = (lp.v1.x - initial_pos.y) - initial_pos.x;
		
		r = -(M_PI / 2);
	}

	//sus
	if (scenario == 3)
	{
		initialtX = astro.v1.x - initial_pos.x;
		initialtY = lp.v3.y;

		astro.v1.y = lp.v3.y + initial_pos.y;

		r = 0;
	}

	//stanga
	if (scenario == 4)
	{
		initialtX = (lp.v2.x + initial_pos.y) - initial_pos.x;
		initialtY = astro.v1.y - initial_pos.y;

		astro.v1.x = (lp.v2.x + initial_pos.y) - initial_pos.x;

		r = -(M_PI / 2);
	}

	last_pos.x = astro.v1.x;
	last_pos.y = astro.v1.y;

	translateX = 0;
	translateY = 0;
}


// Calculeaza translatia initiala, pozitia varfului unghiul de rotatie
// si noul cadran, dupa coliziune, in functie de latura.
void Tema1::ReflectionPlatformCollision(int scenario)
{
	initialtX = astro.v1.x - initial_pos.x;
	initialtY = astro.v1.y - initial_pos.y;

	translateX = 0;
	translateY = 0;

	//jos
	if (scenario == 1)
	{
		initialtY -= initial_pos.y;
		astro.v1.y -= initial_pos.y;

		r = -r - M_PI;

		if (quadrant == 1)
		{
			quadrant = 4;
		}

		if (quadrant == 2)
		{
			quadrant = 3;
		}
	}

	//stanga
	if (scenario == 2)
	{
		initialtX -= initial_pos.y;
		astro.v1.x -= initial_pos.y;

		if (quadrant == 1)
		{
			quadrant = 2;
		}

		if (quadrant == 4)
		{
			quadrant = 3;
		}
	}

	//sus
	if (scenario == 3)
	{

		initialtY += initial_pos.y;
		astro.v1.y += initial_pos.y;
		
		r = -r + M_PI;

		if (quadrant == 4)
		{
			quadrant = 1;
		}

		if (quadrant == 3)
		{
			quadrant = 2;
		}
	}

	//dreapta
	if (scenario == 4)
	{
		initialtX += initial_pos.y;
		astro.v1.x += initial_pos.y;

		if (quadrant == 2)
		{
			quadrant = 1;
		}

		if (quadrant == 3)
		{
			quadrant = 4;
		}
	}

	last_pos.x = astro.v1.x;
	last_pos.y = astro.v1.y;
}


// Calculeaza translatia initiala, pozitia varfului si unghiul de rotatie,
// in functie de latura, pentru asteroid.
void Tema1::AsteroidCollision(Asteroid as)
{
	//stanga
	if (astro.v1.x >= (as.cx - as.radius - err2) && astro.v1.x <= (as.cx - as.radius + err2) && 
		astro.v1.y <= (as.cy + as.radius - err2) && astro.v1.y >= (as.cy - as.radius + err2))
	{
		ReflectionPlatformCollision(2);

		return;
	}

	//jos
	if (astro.v1.x > (as.cx - as.radius + err2) && astro.v1.x < (as.cx + as.radius - err2) && 
		astro.v1.y >= (as.cy - as.radius) && astro.v1.y <= as.cy)
	{
		ReflectionPlatformCollision(1);

		return;
	}

	//dreapta
	if (astro.v1.x >= (as.cx + as.radius - err2) && astro.v1.x <= (as.cx + as.radius) && 
		astro.v1.y <= (as.cy + as.radius - err2) && astro.v1.y >= (as.cy - as.radius + err2))
	{
		ReflectionPlatformCollision(4);

		return;
	}

	//sus
	if (astro.v1.x > (as.cx - as.radius + err2) && astro.v1.x < (as.cx + as.radius - err2) && 
		astro.v1.y <= (as.cy + as.radius) && astro.v1.y >= as.cy)
	{
		ReflectionPlatformCollision(3);

		return;
	}
}

// Calculeaza coliziune cu platforma de final si reseteaza jocul.
int Tema1::GameOver()
{
	if (astro.v1.x >= fp.v1.x - err1 && astro.v1.x <= fp.v2.x + err1 && astro.v1.y >= fp.v1.y - err1 && astro.v1.y <= fp.v3.y + err1)
	{
		quadrant = -1;

		initialtX = 0;
		initialtY = 0;

		translateX = 0;
		translateY = 0;

		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		return 1;
	}
}




// Calculeaza si aplica transformarile la fiecare pas, in functie de cadran sau de
// latura si totodata verifica si coliziunile.
void Tema1::Update(float deltaTimeSeconds)
{
	if (GameOver() == 1)	// daca platforma finala a fost atinsa.
	{
		return;
	}

	glm::ivec2 resolution = window->GetResolution();
	
	modelMatrix = glm::mat3(1);		// pentru astronaut
	modelMatrix2 = glm::mat3(1);	// pentru asteroidul cu translatie
	modelMatrix3 = glm::mat3(1);	// pentru asteroidul cu scalare si rotatie

	modelMatrix *= Transform2D::Translate(initialtX, initialtY);
	modelMatrix2 *= Transform2D::Translate(as2.initial_pos.x, as2.initial_pos.y);
	modelMatrix3 *= Transform2D::Translate(as.initial_pos.x, as.initial_pos.y);
	
	as.rotation += deltaTimeSeconds * 50;

	as.scaleX += deltaTimeSeconds * 6;
	as.scaleY += deltaTimeSeconds * 6;

	as2.translateY += deltaTimeSeconds * 2;

	modelMatrix2 *= Transform2D::Translate(0, 80 * sin(as2.translateY));	// translatare asteroid

	as2.cy = as2.initial_pos.y + 80 * sin(as2.translateY);

	modelMatrix3 *= Transform2D::Scale(sin(as.scaleX), sin(as.scaleY));	// scalare asteroid
	modelMatrix3 *= Transform2D::Rotate(-as.rotation);	// rotatie asteroid
	
	// Calculare pozitie varf, in functie de cadran.
	if (click == 1)
	{
		translateX += deltaTimeSeconds * dx * 200;
		translateY += deltaTimeSeconds * dy * 200;
		
		if (quadrant == 1)
		{
			astro.v1.x = last_pos.x + translateX;
			astro.v1.y = last_pos.y + translateY;
		}

		if (quadrant == 2)
		{
			astro.v1.x = last_pos.x - translateX;
			astro.v1.y = last_pos.y + translateY;
		}

		if (quadrant == 3)
		{
			astro.v1.x = last_pos.x - translateX;
			astro.v1.y = last_pos.y - translateY;
		}

		if (quadrant == 4)
		{
			astro.v1.x = last_pos.x + translateX;
			astro.v1.y = last_pos.y - translateY;
		}
	}

	// Calculare translatie si rotatie astronaut.
	if (quadrant == 1)
	{
		modelMatrix *= Transform2D::Translate(translateX, translateY); //Translatia spre mouse;
		modelMatrix *= Transform2D::Translate(initial_pos.x, initial_pos.y)*
					   Transform2D::Rotate(-r)*
			           Transform2D::Translate(-initial_pos.x, -initial_pos.y); //Rotatia spre mouse.
	}

	if (quadrant == 2)
	{
		modelMatrix *= Transform2D::Translate(-translateX, translateY);
		modelMatrix *= Transform2D::Translate(initial_pos.x, initial_pos.y)*
					   Transform2D::Rotate(r)*
			           Transform2D::Translate(-initial_pos.x, -initial_pos.y);
	}

	if (quadrant == 3)
	{
		modelMatrix *= Transform2D::Translate(-translateX, -translateY);
		modelMatrix *= Transform2D::Translate(initial_pos.x, initial_pos.y)*
				       Transform2D::Rotate(r)*
			           Transform2D::Translate(-initial_pos.x, -initial_pos.y);
	}

	if (quadrant == 4)
	{
		modelMatrix *= Transform2D::Translate(translateX, -translateY);
		modelMatrix *= Transform2D::Translate(initial_pos.x, initial_pos.y)*
					   Transform2D::Rotate(-r)*
					   Transform2D::Translate(-initial_pos.x, -initial_pos.y);
	}


	// Detectare coliziune LandingPlatform
	//jos
	if (astro.v1.x > (lp.v1.x + err2) && astro.v1.x < (lp.v2.x - err2) && 
		astro.v1.y >= lp.v1.y - err2 && astro.v1.y <= lp.v1.y + (lp.v3.y - lp.v1.y) / 2)
	{
		click = 0;

		LandingPlatformCollision(1);

		return;
	}

	//stanga
	if (astro.v1.x >= lp.v1.x && astro.v1.x <= (lp.v1.x + err2) &&
		astro.v1.y >= lp.v1.y && astro.v1.y <= lp.v3.y)
	{
		click = 0;

		LandingPlatformCollision(2);

		return;
	}

	//sus
	if (astro.v1.x > (lp.v1.x + err2) && astro.v1.x < (lp.v2.x - err2) &&
		astro.v1.y <= lp.v3.y + err2 && astro.v1.y >= lp.v1.y - err2)
	{
		click = 0;

		LandingPlatformCollision(3);

		return;
	}

	//dreapta
	if (astro.v1.x <= lp.v2.x + err2 && astro.v1.x >= (lp.v2.x - err2) &&
		astro.v1.y >= lp.v1.y && astro.v1.y <= lp.v3.y)
	{
		click = 0;

		LandingPlatformCollision(4);

		return;
	}
	

	// // Detectare coliziune ReflexionPlatform
	//jos
	if (astro.v1.x > (rp.v1.x + err1) && astro.v1.x < (rp.v2.x - err1) &&
		astro.v1.y >= rp.v1.y && astro.v1.y <= rp.v1.y + ((rp.v3.y - rp.v1.y) / 2))
	{
		ReflectionPlatformCollision(1);
		
		return;
	}

	//stanga
	if (astro.v1.x >= rp.v1.x - err2 && astro.v1.x <= (rp.v1.x + err2) &&
		astro.v1.y >= rp.v1.y && astro.v1.y <= rp.v3.y)
	{
		ReflectionPlatformCollision(2);
		
		return;
	}

	//sus
	if (astro.v1.x > (rp.v1.x + err1) && astro.v1.x < (rp.v2.x - err1) &&
		astro.v1.y <= rp.v3.y && astro.v1.y >= rp.v1.y)
	{
		ReflectionPlatformCollision(3);
		
		return;
	}

	//dreapta
	if (astro.v1.x <= rp.v2.x + 3 && astro.v1.x >= (rp.v2.x - err1) &&
		astro.v1.y >= rp.v1.y && astro.v1.y <= rp.v3.y)
	{
		ReflectionPlatformCollision(4);
		
		return;
	}


	// // Detectare coliziune fereastra
	//stanga
	if (astro.v1.x <= 0)
	{
		ReflectionPlatformCollision(4);
		
		return;
	}

	//dreapta
	if (astro.v1.x >= resolution.x)
	{
		ReflectionPlatformCollision(2);
		
		return;
	}

	//sus
	if (astro.v1.y >= resolution.y)
	{
		ReflectionPlatformCollision(1);
		
		return;
	}

	//jos
	if (astro.v1.y <= 0)
	{
		ReflectionPlatformCollision(3);
		
		return;
	}

	// Detectare coliziune si calculare pozitii noi asteroizi
	AsteroidCollision(as);
	AsteroidCollision(as2);

	RenderMesh2D(meshes["astro"], shaders["VertexColor"], modelMatrix);
	RenderMesh2D(meshes["landing_platform"], shaders["VertexColor"], glm::mat3(1));
	RenderMesh2D(meshes["reflection_platform"], shaders["VertexColor"], glm::mat3(1));
	RenderMesh2D(meshes["final_platform"], shaders["VertexColor"], glm::mat3(1));
	RenderMesh2D(meshes["asteroid2"], shaders["VertexColor"], modelMatrix2);
	RenderMesh2D(meshes["asteroid"], shaders["VertexColor"], modelMatrix3);
}


void Tema1::FrameEnd()
{

}


// Calculeaza viteza si unghiul de rotatie pana la pozitia mouse-ului.
void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT))
	{
		Tema1::mouseX = mouseX;
		Tema1::mouseY = mouseY;

		glm::ivec2 resolution = window->GetResolution();

		click = 1;

		translateX = 0;
		translateY = 0;
		
		c1 = abs(mouseX - astro.v1.x);
		c2 = abs(abs(resolution.y - mouseY) - astro.v1.y);

		dx = abs(mouseX - astro.v1.x);
		dy = abs(abs(resolution.y - mouseY) - astro.v1.y);

		hyp = sqrtf(dx*dx + dy*dy);
		
		dx = dx / hyp;
		dy = dy / hyp;

		if (mouseX > astro.v1.x && abs(resolution.y - mouseY) > astro.v1.y) //CI
		{
			quadrant = 1;

			r = asin(c1 / sqrtf(c1 * c1 + c2 * c2));
		}

		if (mouseX < astro.v1.x && abs(resolution.y - mouseY) > astro.v1.y) //CII
		{
			quadrant = 2;

			r = asin(c1 / sqrtf(c1 * c1 + c2 * c2));
		}

		if (mouseX < astro.v1.x && abs(resolution.y - mouseY) < astro.v1.y) //CIII
		{
			quadrant = 3;

			r = M_PI / 2 + asin(c2 / sqrtf(c1 * c1 + c2 * c2));
		}

		if (mouseX > astro.v1.x && abs(resolution.y - mouseY) < astro.v1.y) //CIV
		{
			quadrant = 4;

			r = M_PI / 2 + asin(c2 / sqrtf(c1 * c1 + c2 * c2));
		}
	}	
}