#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{

public:

	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		this->_perspective = glm::perspective(fov, aspect, zNear, zFar);

		this->_position = pos;

		this->_forward = glm::vec3(0, 0, 1);

		this->_up = glm::vec3(0, 1, 0);
	}

	inline glm::mat4 getViewProjection() const
	{
		return this->_perspective * glm::lookAt(this->_position , this->_position + this->_forward, this->_up);
	}

	virtual ~Camera() {}

private:

	glm::mat4 _perspective;
	
	glm::vec3 _position;
	
	glm::vec3 _forward;

	glm::vec3 _up;

};
