#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Camera.h"
#include <iostream>
using namespace std;
//using namespace glm;
class Transform
{
	private:
		glm::mat4 model;

	public:
		Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
		{
			this->pos = pos;
			this->rot = rot;
			this->scale = scale;
			glm::mat4 posMat = glm::translate(pos);
			glm::mat4 scaleMat = glm::scale(scale);
			glm::mat4 rotX = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));
			glm::mat4 rotY = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
			glm::mat4 rotZ = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));
			glm::mat4 rotMat = rotX * rotY * rotZ;

			//cout << "Rotando:  " << rot.x << ", " << rot.y << ", " << rot.z << endl;
			//return posMat * rotMat * scaleMat;
			//model = posMat * rotMat * scaleMat;
		}

		

		glm::mat4 GetMVP(const Camera& camera)
		{
			glm::mat4 VP = camera.GetViewProjection();
			glm::mat4 M = GetModel();

			return VP * M;
		}
		void CalcModel()
		{
			glm::mat4 R, S, T;

			model = glm::mat4(1.0);

			// calc m_matrix
			T = Translate(pos);
			R = Rotate(rot);
			S = Scale(scale);

			model = T * S * R;
		}

		glm::mat4 Scale(glm::vec3 scaled)
		{
			glm::mat4 S(1.0f);
			S = glm::scale(S, scaled);
			return S;
		}

		glm::mat4 Translate(glm::vec3 translation)
		{
			
			return glm::translate(glm::mat4(1.0f), translation);
		}

		glm::mat4 Rotate(glm::vec3 rotation)
		{
			glm::mat4 R(1.0f);
			// rotation = vec3(0, 0, 0);

			// Orden YXZ

			// rotar en y
			R = glm::rotate(R, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));

			// rotar en x  // picth
			R = glm::rotate(R, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

			// rotar en z
			R = glm::rotate(R, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

			cout << "Rotando en " << rotation.x << ", " << rotation.y << ", " << rotation.z << endl;

			return R;
		}

		  glm::vec3* GetPos() { return &pos; }
		  glm::vec3* GetRot() { return &rot; }
		  glm::vec3* GetScale() { return &scale; }

		void SetPos(glm::vec3& pos) { this->pos = pos; }
		
		void SetRot(glm::vec3& rot) 
		{ 
				this->rot = rot; 
		}
		void SetRotX(float angle)
		{
			glm::mat4 rotAux = glm::rotate(angle, glm::vec3(1, 0, 0));
			model = model *rotAux;
		}
		void SetRotY(float angle)
		{
			glm::mat4 rotAux = glm::rotate(angle, glm::vec3(0, 1, 0));
			model = model *rotAux;
		}
		void SetRotZ(float angle)
		{
			glm::mat4 rotAux = glm::rotate(angle, glm::vec3(0, 0, 1));
			model = model *rotAux;
		}


		  void SetScale(glm::vec3& scale) { this->scale = scale; }

		glm::mat4 GetModel()
		{

			glm::mat4 posMat = glm::translate(pos);
			glm::mat4 scaleMat = glm::scale(scale);
			glm::mat4 rotX = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));
			glm::mat4 rotY = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
			glm::mat4 rotZ = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));
			glm::mat4 rotMat = rotX * rotY * rotZ;

			//CalcModel();

			//cout << "Rotando:  " << rot.x << ", " << rot.y << ", " << rot.z << endl;
			return posMat * rotMat * scaleMat;
			//return  model;
		}

	protected:
	private:
		glm::vec3 pos;
		glm::vec3 rot;
		glm::vec3 scale;
};
