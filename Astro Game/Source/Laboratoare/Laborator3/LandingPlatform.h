#pragma once

// Contine datele pentru platforma de aterizare.
class LandingPlatform
{
public:
	LandingPlatform();
	~LandingPlatform();


	glm::vec3 v1 = glm::vec3(500, 250, 0);
	glm::vec3 v2 = glm::vec3(700, 250, 0);
	glm::vec3 v3 = glm::vec3(700, 270, 0);
	glm::vec3 v4 = glm::vec3(500, 270, 0);

	vector<VertexFormat> vertices =
	{
		VertexFormat(v1, glm::vec3(1, 0, 0)), //0
		VertexFormat(v2, glm::vec3(1, 0, 0)), //1
		VertexFormat(v3, glm::vec3(1, 0, 0)), //2
		VertexFormat(v4, glm::vec3(1, 0, 0)) //3
	};

	vector<unsigned short> indices =
	{
		0, 1, 2,
		0, 2, 3
	};
};