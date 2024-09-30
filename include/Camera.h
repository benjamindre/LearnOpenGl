/**
 * @file Camera.h
 * @brief None
 * @author Benjamin Enger (benjaminenger125522@gmail.com)
 * @date 2024-08-12 10:47:15
 * @version 1.0
 */

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>

static const float kYaw         = -90.0f;
static const float kPitch       =  0.0f;
static const float kSpeed       =  2.5f;
static const float kSensitivity =  0.1f;
static const float kZoom        =  45.0f;

enum class Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = kYaw, float pitch = kPitch);
    ~Camera();

    glm::mat4 GetViewMatrix() const;

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);

    glm::vec3 GetPosition() const
    {
        return m_Position;
    }

    glm::vec3 GetFront() const
    {
        return m_Front;
    }

    glm::vec3 GetUp() const
    {
        return m_Up;
    }

    glm::vec3 GetRight() const
    {
        return m_Right;
    }

    glm::vec3 GetWorldUp() const
    {
        return m_WorldUp;
    }

    float GetZoom() const
    {
        return m_Zoom;
    }

    float GetYaw() const
    {
        return m_Yaw;
    }

    float GetPitch() const
    {
        return m_Pitch;
    }
private:
    void UpdateCameraVectors();
private:
    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::vec3 m_WorldUp;

    float m_Yaw;
    float m_Pitch;

    float m_MovementSpeed;
    float m_MouseSensitivity;
    float m_Zoom;
};