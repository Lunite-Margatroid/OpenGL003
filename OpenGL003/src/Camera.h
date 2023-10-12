#pragma once


#ifndef PI
#define PI 3.14159f
#endif


enum Camera_Movement
{
	FRONT,
	BACK,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// ≥ı º÷µ
const float YAW = -PI/2.0f;
const float PITCH = 0.0f;
const float SPEED = 5.0f;
const float SCROLL_SENSITIVITY = 0.02f;
const float ROTATE_SENEITIVITY = 0.005f;
const float FOV = PI / 4.0f;

class Camera
{
private:
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	float m_yaw;
	float m_pitch;

	float m_fov;

	float m_moveSpeed;
	float m_scrollSensitivity;
	float m_rotateSensitivity;

	void UpdateViewTrans();
	void UpdateProjectionTrans();
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = YAW,
		float pitch = PITCH,
		float fov = FOV
		);

	void SetMoveSpeed(float moveSpeed);
	void SetScrollSensitivity(float sensitivity);
	void SetRotateSensitivity(float sensitivity);
	void SetFov(float fov);

	glm::mat4 GetViewTrans();
	glm::mat4 GetProjectionTrans();

	void ProcessKeyInput(Camera_Movement diration, float deltaTime);
	void ProcessMouse(float offsetx, float offsety);
	void ProcessScroll(float offsety);

};

