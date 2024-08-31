#include "Texture2D.h"

#include <cassert>
#include <stb_image.h>
#include <glad/glad.h>

Texture2D::Texture2D(std::string_view filename, uint16_t rgbType)
{
    stbi_set_flip_vertically_on_load(true);

    uint8_t* pixels = stbi_load(filename.data(), &m_Width, &m_Height, &m_Channels, 0);
    if (!pixels)
        assert(false && "Read texture2d image failed.");

    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    // 设置纹理环绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // 设置纹理过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, rgbType, m_Width, m_Height, 0, rgbType, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(pixels);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &m_TextureID);
}