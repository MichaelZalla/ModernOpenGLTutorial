#pragma once

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

class Transform
{

public:

	Transform(
		const glm::vec3& pos = glm::vec3(),
		const glm::vec3& rot = glm::vec3(),
		const glm::vec3& scale = glm::vec3(1.0, 1.0, 1.0)):
		_pos(pos),
		_rot(rot),
		_scale(scale) {}

	inline glm::mat4 getModelMatrix() const
	{
		glm::mat4 posMatrix = glm::translate(this->_pos);
		
		glm::mat4 rotXMatrix = glm::rotate(this->_rot.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(this->_rot.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(this->_rot.z, glm::vec3(0, 0, 1));
		
		glm::mat4 scaleMatrix = glm::scale(this->_scale);

		// Using reverse-order to multiply in order x-y-z (non-commutative);

		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		// Again, using reverse-order to multiply in order scale-rot-pos;

		return posMatrix * rotMatrix * scaleMatrix;
	}

	inline glm::vec3& getPos() {
		return this->_pos;
	}
	
	inline void setPos(const glm::vec3& pos) {
		this->_pos = pos;
	}

	inline glm::vec3& getRot() {
		return this->_rot;
	}
	
	inline void setRot(const glm::vec3& rot) {
		this->_rot = rot;
	}

	inline glm::vec3& getScale() {
		return this->_scale;
	}
	
	inline void setScale(const glm::vec3& scale) {
		this->_scale = scale;
	}
	
	virtual ~Transform() {}

private:

	glm::vec3 _pos;
	glm::vec3 _rot;
	glm::vec3 _scale;

private:

	// Transform(const Transform& other);

	// Transform& operator=(const Transform& other);

};
