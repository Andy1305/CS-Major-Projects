#pragma once

// Contine datele pentru asteroizi.
class Asteroid
{
public:
	int num_vertices;
	float cx, cy, radius = 0, translateX = 0, translateY = 0, rotation = 0, scaleX = 0, scaleY = 0;
	
	glm::vec3 initial_pos;

	Asteroid();
	~Asteroid();

	vector<VertexFormat> vertices;

	vector<unsigned short> indices =
	{
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5,
		0, 5, 6,
		0, 6, 7,
		0, 7, 8,
		0, 8, 9,
		0, 9, 10,
		0, 10, 11,
		0, 11, 12,
		0, 12, 1
	};
};