#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float fov, float aspectRatio, float nearClip, float farClip);

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

    void ProcessKeyboardMovement(const glm::vec3& direction, float deltaTime);
    void ProcessKeyboardRotation(float xOffset, float yOffset);
    void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yOffset);

    void SetPosition(const glm::vec3& position) { m_Position = position; }
    void SetYaw(float yaw) { m_Yaw = yaw; updateCameraVectors(); }
    void SetPitch(float pitch) { m_Pitch = pitch; updateCameraVectors(); }
    void SetFOV(float fov) { m_FOV = fov; updateProjectionMatrix(); }
    void SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; updateProjectionMatrix(); }
    void SetNearClip(float nearClip) { m_NearClip = nearClip; updateProjectionMatrix(); }
    void SetFarClip(float farClip) { m_FarClip = farClip; updateProjectionMatrix(); }

    glm::vec3 GetPosition() const { return m_Position; }
    glm::vec3 GetFront() const { return m_Front; }
    glm::vec3 GetUp() const { return m_Up; }
    glm::vec3 GetRight() const { return m_Right; }
    float GetYaw() const { return m_Yaw; }
    float GetPitch() const { return m_Pitch; }
    float GetFOV() const { return m_FOV; }
    float GetAspectRatio() const { return m_AspectRatio; }
    float GetNearClip() const { return m_NearClip; }
    float GetFarClip() const { return m_FarClip; }

private:
    void updateCameraVectors();
    void updateProjectionMatrix();

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

    float m_FOV;           // Field of View
    float m_AspectRatio;   // Aspect Ratio
    float m_NearClip;      // Near clipping plane
    float m_FarClip;       // Far clipping plane

    glm::mat4 m_ProjectionMatrix;
};