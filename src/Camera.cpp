#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3 &position, const glm::vec3 &up, float yaw, float pitch)
    : m_Position(position), m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_WorldUp(up), m_Yaw(yaw), m_Pitch(pitch), m_MovementSpeed(kSpeed), m_MouseSensitivity(kSensitivity), m_Zoom(kZoom)
{
    UpdateCameraVectors();
}

Camera::~Camera()
{

}

void Camera::UpdateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = cos(glm::radians(m_Pitch)) * sin(glm::radians(m_Yaw));

    m_Front = glm::normalize(front);

    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = m_MovementSpeed * deltaTime;
    if (direction == Camera_Movement::FORWARD)
        m_Position += m_Front * velocity;
    if (direction == Camera_Movement::BACKWARD)
        m_Position -= m_Front * velocity;
    if (direction == Camera_Movement::LEFT)
        m_Position -= m_Right * velocity;
    if (direction == Camera_Movement::RIGHT)
        m_Position += m_Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= m_MouseSensitivity;
    yoffset *= m_MouseSensitivity;

    m_Yaw   += xoffset;
    m_Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (m_Pitch > 89.0f)
            m_Pitch = 89.0f;
        if (m_Pitch < -89.0f)
            m_Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    m_Zoom -= (float)yoffset;

    if (m_Zoom < 1.0f)
        m_Zoom = 1.0f;
    if (m_Zoom > 45.0f)
        m_Zoom = 45.0f;
}
