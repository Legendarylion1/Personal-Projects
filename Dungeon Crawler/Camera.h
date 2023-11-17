#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shaderClass.h"
#include "Texture.h"

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	float width;
	float height;

	float nearPlane = -1.0f;
	float farPlane = 10.0f;

	Camera(int width, int height, glm::vec3 position);

	void Matrix(Shader& shader, glm::vec3 translate);
	void Matrix(Shader& shader, glm::vec3 translate, float rotationDegrees);
	void Matrix(Shader& shader, glm::vec3 translate, float rotationDegrees, bool flipImage);
	void move(int direction, float speed);
	void setPosition(glm::vec3 newPosition);
};