#include "Texture.h"
#include <glad/glad.h>
#include <iostream>


Texture::Texture(const std::string& path)
{
    glGenTextures(1, &m_RendererID);
    if (m_RendererID == 0) {
        std::cerr << "Error generating texture ID." << std::endl;
    }
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    // Set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Check for errors after setting texture parameters
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "Error setting texture parameters: " << error << std::endl;
    }

    // Load and generate the texture
    stbi_set_flip_vertically_on_load(true); // Flip the image vertically on load
    unsigned char* data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 0);
    if (data)
    {
        GLenum format = (m_Channels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Check for errors after creating the texture and generating mipmaps
        error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "Error loading texture and generating mipmaps: " << error << std::endl;
        }
    }
    else
    {
        std::cerr << "Failed to load texture: " << stbi_failure_reason() << std::endl;
    }

    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_RendererID);
}

void Texture::use()
{
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}
