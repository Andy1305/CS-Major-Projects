#pragma once

#include <include/glm.h>
#include <include/math.h>

// Include variabilele si metodele pentru implementarea camerei, ca in laboratorul 5.
namespace Camera
{
	class Camera
	{
		public:
			float distanceToTarget = 2.5;
			glm::vec3 position;
			glm::vec3 forward;
			glm::vec3 right;
			glm::vec3 up;

			Camera()
			{
			}

			~Camera()
			{
			}

			void Set(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
			{
				this->position = position;
				forward = glm::normalize(center-position);
				right	= glm::cross(forward, up);
				this->up = glm::cross(right,forward);
			}

			void MoveForward(float distance)
			{
				glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
			}

			void TranslateForward(float distance)
			{
				position += glm::normalize(forward) * distance;
			}

			void TranslateUpword(float distance)
			{
				position += glm::normalize(up) * distance;
			}

			void TranslateRight(float distance)
			{
				position += glm::normalize(right) * distance;
			}

			void RotateFirstPerson_OX(float angle)
			{
				glm::vec4 newForward = glm::rotate(glm::mat4(1.0f), angle, right) * glm::vec4(forward, 1.0);
				forward = glm::normalize(glm::vec3(newForward));

				glm::vec4 newUp = glm::rotate(glm::mat4(1.0f), angle, right) * glm::vec4(up, 1.0);
				up = glm::normalize(glm::vec3(newUp));
			}

			void RotateFirstPerson_OY(float angle)
			{
				glm::vec4 newForward = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1.0);
				forward = glm::normalize(newForward);

				glm::vec4 newRight = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(right, 1.0);
				right = glm::normalize(newRight);
				
				glm::vec4 newUp = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(up, 1.0);
				up = glm::normalize(newUp);
			}

			void RotateFirstPerson_OZ(float angle)
			{
				glm::vec4 newRight = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, -1)) * glm::vec4(right, 1.0);
				right = glm::normalize(newRight);

				glm::vec4 newUp = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, -1)) * glm::vec4(up, 1.0);
				up = glm::normalize(newUp);
			}

			void RotateThirdPerson_OX(float angle)
			{
				position += glm::normalize(forward) * distanceToTarget;
				
				glm::vec4 newForward = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1, 0, 0)) * glm::vec4(forward, 1.0);
				forward = glm::normalize(newForward);

				glm::vec4 newUp = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1, 0, 0)) * glm::vec4(up, 1.0);
				up = glm::normalize(newUp);
				
				position -= glm::normalize(forward) * distanceToTarget;
			}

			void RotateThirdPerson_OY(float angle)
			{
				//position += glm::normalize(forward) * distanceToTarget;
				MoveForward(distanceToTarget);
				/*glm::vec4 newForward = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1.0);
				forward = glm::normalize(newForward);

				glm::vec4 newRight = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(right, 1.0);
				right = glm::normalize(newRight);

				glm::vec4 newUp = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(up, 1.0);
				up = glm::normalize(newUp);*/
				RotateFirstPerson_OY(angle);
				//position -= glm::normalize(forward) * distanceToTarget;
				MoveForward(-distanceToTarget);
			}

			void RotateThirdPerson_OZ(float angle)
			{
				position += glm::normalize(forward) * distanceToTarget;

				glm::vec4 newRight = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, -1)) * glm::vec4(right, 1.0);
				right = glm::normalize(newRight);

				glm::vec4 newUp = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, -1)) * glm::vec4(up, 1.0);
				up = glm::normalize(newUp);

				position -= glm::normalize(forward) * distanceToTarget;
			}

			glm::mat4 GetViewMatrix()
			{
				return glm::lookAt(position, position + forward, up);
			}

			glm::vec3 GetTargetPosition()
			{
				return position + forward * distanceToTarget;
			}
		};
}