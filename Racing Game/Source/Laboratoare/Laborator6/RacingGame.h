#pragma once

#include <Component/SimpleScene.h>

#include "LabCamera.h"
#include "Sky.h"
#include "Car.h"
#include "Highway.h"
#include "Earth.h"

// Include variabilele si metodele generale, specifice programului principal.
class RacingGame : public SimpleScene
{
public:
	RacingGame();
	~RacingGame();

	void getTime();

	void Init() override;

	Mesh * CreateMesh(const char * name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices);


protected:
	int night_or_day = 0;
	float time = 0;
	float angle, speed = 10.0;
	enum directions { stop, up, left, down, right, up_and_left, up_and_right};
	directions carDirection;
	glm::mat4 projectionMatrix;
	GLenum polygonMode;
	Sky sky;
	Car car;
	Highway hw;
	Earth earth;
	Camera::Camera *camera;
	

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, glm::vec3 color);

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY);

	void OnKeyRelease(int key, int mods) override;
};
