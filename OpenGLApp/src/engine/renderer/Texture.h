#pragma once

#include <stb/stb_image.h>
#include <string>

class Texture {
public:
	Texture(const std::string& path);
	~Texture();

	void use();

	inline unsigned int GetID() const { return m_RendererID; }
private:
	unsigned int m_RendererID;
	int m_Width, m_Height, m_Channels;
};