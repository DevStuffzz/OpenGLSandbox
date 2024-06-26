#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float fov, float aspectRatio, float nearClip, float farClip)
    : m_Position(position), m_WorldUp(up), m_Yaw(yaw), m_Pitch(pitch), m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip),
    m_MovementSpeed(2.5f), m_MouseSensitivity(0.01f), m_Zoom(45.0f)
{
    updateCameraVectors();
    updateProjectionMatrix();
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

glm::mat4 Camera::GetProjectionMatrix() const {
    return m_ProjectionMatrix;
}

void Camera::ProcessKeyboardMovement(const glm::vec3& direction, float deltaTime) {
    float velocity = m_MovementSpeed * deltaTime;
    m_Position += direction * velocity;
}

// Assuming the Camera class has a method like this:
void Camera::ProcessKeyboardRotation(float xOffset, float yOffset) {
    // Implement the rotation logic here
    // You might want to use angles instead of offsets and apply to the camera's rotation
    m_Yaw += xOffset;
    m_Pitch += yOffset;

    // Ensure the pitch is within bounds
    if (m_Pitch > 89.0f)
        m_Pitch = 89.0f;
    if (m_Pitch < -89.0f)
        m_Pitch = -89.0f;

    // Update the camera vectors
    updateCameraVectors();
}
void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
    xOffset *= m_MouseSensitivity;
    yOffset *= m_MouseSensitivity;

    m_Yaw += xOffset;
    m_Pitch += yOffset;

    if (constrainPitch) {
        if (m_Pitch > 89.0f)
            m_Pitch = 89.0f;
        if (m_Pitch < -89.0f)
            m_Pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset) {
    m_FOV -= yOffset;
    if (m_FOV < 1.0f)
        m_FOV = 1.0f;
    if (m_FOV > 45.0f)
        m_FOV = 45.0f;
    updateProjectionMatrix();
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(front);
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

void Camera::updateProjectionMatrix() {
    m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
}