#pragma once

#include "glad/glad.h"
#include <vector>
#include <engine/renderer/Shader.h>
#include <engine/renderer/Texture.h>

class VertexArray {
public:
    VertexArray(const std::vector<float>& vertices, const std::vector<unsigned int>& elements);
    ~VertexArray();

    inline unsigned int GetID() const { return m_VaoID; }
    void bind() const;

    void DrawArray(const std::unique_ptr<Shader>& shader, const std::unique_ptr<Texture>& texture);
private:
    unsigned int m_VaoID;
    unsigned int VBO, EBO;
    unsigned int vertexCount, elementCount;
};
