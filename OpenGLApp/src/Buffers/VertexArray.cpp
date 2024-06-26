#include "VertexArray.h"
VertexArray::VertexArray(const std::vector<float>& vertices, const std::vector<unsigned int>& elements)
    : vertexCount(vertices.size()), elementCount(elements.size())
{
    glGenVertexArrays(1, &m_VaoID);
    glBindVertexArray(m_VaoID);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);  // Bind the EBO here
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementCount * sizeof(unsigned int), elements.data(), GL_STATIC_DRAW);

    // Vertex (float3 position, float3 color, float2 texture coords
 // Vertex (float3 position, float3 color, float2 texture coords)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &m_VaoID);
}

void VertexArray::bind() const
{
    glBindVertexArray(m_VaoID);
}

void VertexArray::DrawArray(const std::unique_ptr<Shader>& shader, const std::unique_ptr<Texture>& texture)
{
    shader->setInt("uTexture", texture->GetID());
    // Since the EBO is associated with the VAO, no need to bind EBO again
    glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0);
}
