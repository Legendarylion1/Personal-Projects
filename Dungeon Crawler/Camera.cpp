#include "Camera.h"

/// <summary>
/// Initializes the camera
/// </summary>
/// <param name="width">- Width of the screen</param>
/// <param name="height">- Height of the screen</param>
/// <param name="position">- Starting position of the camera</param>
Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

/// <summary>
/// Sets the model view projection matrix uniform
/// </summary>
/// <param name="shader">- Reference to the game's shader</param>
/// <param name="translate">- Position of the model</param>
void Camera::Matrix(Shader& shader, glm::vec3 translate)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), translate);

	view = glm::lookAt(Position, Position + Orientation, Up);
	proj = glm::ortho(0.0f, width, 0.0f, height, nearPlane, farPlane);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "mvp"), 1, GL_FALSE, glm::value_ptr(proj * view * model));
}

/// <summary>
/// Rotates the model and sets the model view projection matrix uniform
/// </summary>
/// <param name="shader">- Reference to the game's shader</param>
/// <param name="translate">- Position of the model</param>
/// <param name="rotationDegrees">- How much to rotate the model in degrees</param>
void Camera::Matrix(Shader& shader, glm::vec3 translate, float rotationDegrees)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), translate);

	model = glm::rotate(model, glm::radians(rotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
	view = glm::lookAt(Position, Position + Orientation, Up);
	proj = glm::ortho(0.0f, width, 0.0f, height, nearPlane, farPlane);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "mvp"), 1, GL_FALSE, glm::value_ptr(proj * view * model));
}

/// <summary>
/// Rotates and flips the model. Then binds the model view projection matrix uniform
/// </summary>
/// <param name="shader">- Reference to the game's shader</param>
/// <param name="translate">- Position of the model</param>
/// <param name="rotationDegrees">- How much to rotate the model in degrees</param>
/// <param name="flipImage">- Whether or not to flip the image 180 degrees about the Y axis</param>
void Camera::Matrix(Shader& shader, glm::vec3 translate, float rotationDegrees, bool flipImage)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f); 

	if (!flipImage)
	{
		translate.z += 1.0f;
		model = glm::translate(glm::mat4(1.0f), translate);
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	else
	{
		model = glm::translate(glm::mat4(1.0f), translate);
		model = glm::rotate(model, glm::radians(rotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
	}


	view = glm::lookAt(Position, Position + Orientation, Up);
	proj = glm::ortho(0.0f, width, 0.0f, height, nearPlane, farPlane);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "mvp"), 1, GL_FALSE, glm::value_ptr(proj * view * model));
}

/// <summary>
/// Moves the camera position in the desired direction
/// </summary>
/// <param name="direction">- Direction to move the camera in</param>
/// <param name="speed">- Number of units to move the camera</param>
void Camera::move(int direction, float speed)
{
	if (direction == UP)
	{
		Position.y += speed;
	}
	if (direction == DOWN)
	{
		Position.y += -speed;
	}
	if (direction == LEFT)
	{
		Position.x += -speed;
	}
	if (direction == RIGHT)
	{
		Position.x += speed;
	}
}

/// <summary>
/// Sets the position of the camera
/// </summary>
/// <param name="newPosition">- Desired position of the camera</param>
void Camera::setPosition(glm::vec3 newPosition)
{
	Position = newPosition;
}