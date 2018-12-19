#pragma once

using namespace std;

// Include variabilele si metodele pentru implementarea strazii, inclusiv curbe, borduri si obstacole.
class Highway : public SimpleScene
{
public:
	int length, length2, length3, smoothness = 8, curve_angle = 3, nr_parts, obstacle_position;
	float road_width = 4, road_length = 4, border_width = 0.5, border_length = road_length / 1, border_height = 1;
	glm::vec3 road_translation, left_border_translation, right_border_translation;
	glm::vec3 road_color, border_color, obstacle_color;
	glm::mat4 road_modelMatrix, curve_modelMatrix, left_border_modelMatrix, right_border_modelMatrix,
		obstacle_modelMatrix;

	Highway();
	~Highway();

	// strada
	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0, 0, 0)),							// 0
		VertexFormat(glm::vec3(road_width, 0, 0)),					// 1
		VertexFormat(glm::vec3(road_width, 0, -road_length)),		// 2
		VertexFormat(glm::vec3(0, 0, -road_length))					// 3
	};

	// strada
	vector<unsigned short> indices =
	{
		0, 1, 2,
		0, 2, 3
	};

	// bordura
	vector<VertexFormat> vertices2
	{
		VertexFormat(glm::vec3(-border_width, 0, 0)),							// 0
		VertexFormat(glm::vec3(0, 0, 0)),										// 1
		VertexFormat(glm::vec3(0, border_height, 0)),							// 2
		VertexFormat(glm::vec3(-border_width, border_height, 0)),				// 3
		VertexFormat(glm::vec3(-border_width, border_height, -border_length)),	// 4
		VertexFormat(glm::vec3(0, border_height, -border_length)),				// 5
		VertexFormat(glm::vec3(0, 0, -border_length)),							// 6
		VertexFormat(glm::vec3(-border_width, 0, -border_length))				// 7
	};

	// bordura
	vector<unsigned short> indices2 =
	{
		0, 1, 2,	// fata
		0, 2, 3,
		3, 2, 5,
		3, 5, 4,
		1, 6, 2,
		2, 6, 5,
		0, 6, 1,	//spate
		0, 7, 6,
		4, 5, 7,
		5, 6, 7,
		0, 3, 4,
		0, 4, 7
	};

	// curba stanga
	vector<VertexFormat> vertices3;

	// curba stanga
	vector<unsigned short> indices3 =
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
		0, 12, 13,
		0, 13, 14
	};

	// curba dreapta
	vector<VertexFormat> vertices4;

	// curba dreapta
	vector<unsigned short> indices4 =
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
		0, 12, 13,
		0, 13, 14
	};

	// obstacol
	vector<VertexFormat> vertices5
	{
		VertexFormat(glm::vec3(0, 0, 1)),
		VertexFormat(glm::vec3(1, 0, 1)),
		VertexFormat(glm::vec3(0, 1, 1)),
		VertexFormat(glm::vec3(1, 1, 1)),
		VertexFormat(glm::vec3(0, 0, 0)),
		VertexFormat(glm::vec3(1, 0, 0)),
		VertexFormat(glm::vec3(0, 1, 0)),
		VertexFormat(glm::vec3(1, 1, 0))
	};

	// obstacol
	vector<unsigned short> indices5
	{
		0, 1, 2,
		1, 3, 2,
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4
	};

	void BuildLeftCurve()
	{
		for (int i = 0; i <= smoothness; i++)	// se creeaza puncte
		{
			vertices3.push_back(VertexFormat(
				glm::vec3(road_length * cos(i * M_PI / curve_angle / smoothness),
				0, -road_length * sin(i * M_PI / curve_angle / smoothness)))
			);
		}
	}


	void BuildRightCurve()
	{
		for (int i = 0; i <= smoothness; i++)	// se creeaza puncte
		{
			vertices4.push_back(VertexFormat(
				glm::vec3(-road_length * cos(i * M_PI / curve_angle / smoothness),
					0, -road_length * sin(i * M_PI / curve_angle / smoothness)))
			);
		}
	}
};