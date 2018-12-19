#pragma once

#include <Core/Engine.h>

using namespace std;

// Contine datele pentru astronaut.
class Astronaut
{
public:
	Astronaut();
	~Astronaut();

	glm::vec3 v1 = glm::vec3(25, 50, 0);
	glm::vec3 v2 = glm::vec3(0, 0, 0);
	glm::vec3 v3 = glm::vec3(50, 0, 0);

	vector<VertexFormat> vertices =
	{
		VertexFormat(v1, glm::vec3(0, 0, 1)),
		VertexFormat(v2, glm::vec3(0, 1, 0)),
		VertexFormat(v3, glm::vec3(0, 1, 0))
	};

	vector<unsigned short> indices =
	{
		0, 1, 2
	};
};