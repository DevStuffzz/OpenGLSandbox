#pragma once

#include "Buffers/VertexArray.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "engine/io/Camera.h"

class Mesh {
public:
    Mesh(std::unique_ptr<VertexArray>&& va)
        : m_VertexArray(std::move(va)), m_ModelMatrix(1.0f) {}

    ~Mesh() = default;

    void Draw(const std::unique_ptr<Shader>& shader, const std::unique_ptr<Texture>& texture, const std::unique_ptr<Camera>& camera) {
        shader->use();
        texture->use();

        shader->setMat4("model", m_ModelMatrix);
        shader->setMat4("view", camera->GetViewMatrix());
        shader->setMat4("proj", camera->GetProjectionMatrix());

        m_VertexArray->bind();
        m_VertexArray->DrawArray(shader, texture);
    }

    void Translate(const glm::vec3& translation) {
        m_ModelMatrix = glm::translate(m_ModelMatrix, translation);
    }

    void Rotate(float angle, const glm::vec3& axis) {
        m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(angle), axis);
    }

    void Scale(const glm::vec3& scalingFactors) {
        m_ModelMatrix = glm::scale(m_ModelMatrix, scalingFactors);
    }

    const glm::mat4& GetModelMatrix() const {
        return m_ModelMatrix;
    }
public:
    glm::vec3 color = glm::vec3(1.0f);

private:
    std::unique_ptr<VertexArray> m_VertexArray;
    glm::mat4 m_ModelMatrix;
};
