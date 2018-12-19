#pragma once

#include <Component/SimpleScene.h>

#include <Laboratoare\Laborator3\Astronaut.h>
#include <Laboratoare\Laborator3\LandingPlatform.h>
#include <Laboratoare\Laborator3\ReflectionPlatform.h>
#include <Laboratoare\Laborator3\Asteroid.h>
#include <Laboratoare\Laborator3\FinalPlatform.h>

using namespace std;


// Contine variabilele, obiectele, si metodele necesare temei.
class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		Mesh* CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices);

		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;

		void LandingPlatformCollision(int scenario);
		void ReflectionPlatformCollision(int scenario);
		void AsteroidCollision(Asteroid as);
		int GameOver();

	protected:
		int mouseX, mouseY, quadrant = -1, click = 0, window_flag = 0, err1 = 2, err2 = 3;
		float dx, dy, hyp, r, translateX, translateY, scaleX, scaleY, angularStep, c1, c2;
		float angle_to_platform, reflexion_angle, initialtX, initialtY;

		glm::vec3 initial_pos, last_pos;
		glm::mat3 modelMatrix, modelMatrix2, modelMatrix3;
		
		Astronaut astro;
		LandingPlatform lp;
		ReflectionPlatform rp;
		Asteroid as, as2;
		FinalPlatform fp;
};
