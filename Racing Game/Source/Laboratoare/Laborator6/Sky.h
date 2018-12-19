#pragma once

using namespace std;

// Include variabilele si metodele pentru cer.
class Sky
{
public:
	glm::vec3 color;

	Sky();
	~Sky();

	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-150, -3, 10)),
		VertexFormat(glm::vec3(150, -3, 10)),
		VertexFormat(glm::vec3(150, 100, 10)),
		VertexFormat(glm::vec3(-150, 100, 10)),
		VertexFormat(glm::vec3(-150, -3, -150)),
		VertexFormat(glm::vec3(150, -3, -150)),
		VertexFormat(glm::vec3(150, 100, -150)),
		VertexFormat(glm::vec3(-150, 100, -150))
	};

	vector<unsigned short> indices =
	{
		0, 1, 2,	// fata
		0, 2, 3,
		3, 2, 5,	// sus
		3, 5, 4,
		1, 6, 5,	// dreapta
		1, 5, 2,
		0, 6, 2,	// jos
		0, 7, 6,
		7, 6, 5,	// spate
		7, 5, 4,
		0, 7, 4,	// stanga
		0, 4, 3
	};
};