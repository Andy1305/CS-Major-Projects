#pragma once

// Include variabilele si metodele pentru pamant.
class Car
{
public:
	float rotation = 0;
	glm::vec3 color, translation = glm::vec3(0, 0, 0);
	glm::mat4 modelMatrix = glm::mat4(1);

	Car();
	~Car();

	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0, 0, 0)),			// 0
		VertexFormat(glm::vec3(1, 0, 0)),			// 1
		VertexFormat(glm::vec3(1, 0.5, 0)),			// 2
		VertexFormat(glm::vec3(0, 0.5, 0)),			// 3
		VertexFormat(glm::vec3(0, 0.5, -2)),		// 4
		VertexFormat(glm::vec3(1, 0.5, -2)),		// 5
		VertexFormat(glm::vec3(1, 0, -2)),			// 6
		VertexFormat(glm::vec3(0, 0, -2))			// 7
	};

	vector<unsigned short> indices =
	{
		0, 1, 2,	// fata
		0, 2, 3,
		3, 2, 5,
		3, 5, 4,
		1, 6, 2,
		2, 6, 5,
		0, 6, 1,	// spate
		0, 7, 6,
		4, 5, 7,
		5, 6, 7,
		0, 3, 4,
		0, 4, 7
	};
};