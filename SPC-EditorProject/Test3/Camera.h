#pragma once
	
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

struct Camera
{
	public:
		Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
		{
			this->pos = pos;
			this->fov = fov;
			this->aspect = aspect;
			this->zNear = zNear;
			this->zFar = zFar;
			this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
			this->up = glm::vec3(0.0f, 1.0f, 0.0f);
			this->projection = glm::perspective(fov, aspect, zNear, zFar);
		}

		inline glm::mat4 GetViewProjection() const
		{
			return projection * glm::lookAt(pos, pos + forward, up);
		}

		inline glm::mat4 GetView() const
		{
			return glm::lookAt(pos, pos + forward, up);
		}
		inline glm::mat4 GetProjection() const
		{
			return projection;
		}
		inline void SetPos(glm::vec3 pos)
		{
			this->pos = pos;		
		}
		inline glm::vec3 GetPos()
		{
			return this->pos;
		}
		inline void SetFov(float fov)
		{
			this->fov = glm::clamp(fov, 30.0f, 180.0f);;
			this->projection = glm::perspective(fov, aspect, zNear, zFar);
		}
		inline float GetFov()
		{
			
			return fov;
		}


		protected:
		private:
			float fov;
			float aspect;
			float zNear;
			float zFar;
			glm::mat4 projection;
			glm::vec3 pos;
			glm::vec3 forward;
			glm::vec3 up;
};
