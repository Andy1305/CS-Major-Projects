#pragma once

// Include variabilele si metodele pentru pamant.
class Earth
{
public:
	glm::vec3 color;

	Earth();
	~Earth();

	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-151, -0.05, 10)),
		VertexFormat(glm::vec3(151, -0.05, 10)),
		VertexFormat(glm::vec3(151, -0.05, -151)),
		VertexFormat(glm::vec3(-151, -0.05, -151))
	};

	vector<unsigned short> indices
	{
		0, 1, 2,
		0, 2, 3
	};
};