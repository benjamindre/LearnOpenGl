#include "Texture2D.h"

#include <cassert>
#include <stb_image.h>
#include <glad/glad.h>

Texture2D::Texture2D(std::string_view filename, bool flipVertically)
{
    if (flipVertically)
        stbi_set_flip_vertically_on_load(true);

    uint16_t format = GL_RGB;
    uint8_t* pixels = stbi_load(filename.data(), &m_Width, &m_Height, &m_Channels, 0);
    if (!pixels)
        assert(false && "Read texture2d image failed.");

    if (m_Channels == 1) format = GL_RED;
    else if (m_Channels == 3) format = GL_RGB;
    else if (m_Channels == 4) format = GL_RGBA;

    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    // glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, pixels);

    // 设置纹理环绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // 设置纹理过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(pixels);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &m_TextureID);
}