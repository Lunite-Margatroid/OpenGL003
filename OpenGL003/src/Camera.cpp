#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "render.h"

#include "Camera.h"

glm::mat4 Camera::GetViewTrans()
{
	UpdateViewTrans();
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::GetProjectionTrans()
{
	return glm::perspective(m_fov, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
}

void Camera::ProcessKeyInput(Camera_Movement diration, float deltaTime)
{
	switch (diration)
	{
	case FRONT:
		m_position += m_front * deltaTime * m_moveSpeed;
		break;
	case BACK:
		m_position -= m_front * deltaTime * m_moveSpeed;
		break;
	case LEFT:
		m_position -= m_right * deltaTime * m_moveSpeed;
		break;
	case RIGHT:
		m_position += m_right * deltaTime * m_moveSpeed;
		break;
	case UP:
		m_position.y += deltaTime * m_moveSpeed;
		break;
	case DOWN:
		m_position.y -= deltaTime * m_moveSpeed;
		break;
	default:break;
	};
}

void Camera::ProcessMouse(float offsetx, float offsety)
{
	m_yaw += offsetx * m_rotateSensitivity;
	m_pitch += offsety * m_rotateSensitivity;

	if (m_pitch > 1.5f)
		m_pitch = 1.5f;
	if (m_pitch < -1.5f)
		m_pitch = -1.5f;
}

void Camera::ProcessScroll(float offsety)
{
	m_fov -= offsety * m_scrollSensitivity;

	if (m_fov > PI / 4.0f)
		m_fov = PI / 4.0f;
	if (m_fov < 0.02f)
		m_fov = 0.02f;
}

void Camera::UpdateViewTrans()
{
	glm::vec3 front;
	front.x = cos(m_pitch) * cos(m_yaw);
	front.y = sin(m_pitch);
	front.z = cos(m_pitch) * sin(m_yaw);
	m_front = glm::normalize(front);
	m_right = glm::normalize(glm::cross(front, m_worldUp));
}

void Camera::UpdateProjectionTrans()
{
}

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, 
	float yaw, float pitch, float fov):
	m_position(position),
	m_front(front),
	m_up(up),
	m_yaw(yaw),
	m_pitch(pitch),
	m_fov(fov)
{
	m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_moveSpeed = SPEED;
	m_scrollSensitivity = SCROLL_SENSITIVITY;
	m_rotateSensitivity = ROTATE_SENEITIVITY;

	UpdateViewTrans();
	UpdateProjectionTrans();
}

void Camera::SetMoveSpeed(float moveSpeed)
{
	m_moveSpeed = moveSpeed;
}

void Camera::SetScrollSensitivity(float sensitivity)
{
	m_scrollSensitivity = sensitivity;
}

void Camera::SetRotateSensitivity(float sensitivity)
{
	m_rotateSensitivity = sensitivity;
}

void Camera::SetFov(float fov)
{
	m_fov = fov;
}
