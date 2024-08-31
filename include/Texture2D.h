/**
 * @file Texture2D.h
 * @brief 纹理加载
 * @author Benjamin Enger (benjaminenger125522@gmail.com)
 * @date 2024-08-31 13:35:47
 * @version 1.0
 */

#pragma once

#include "Config.h"

class Texture2D
{
public:
    Texture2D(std::string_view filename, uint16_t rgbType);
    ~Texture2D();

    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    int GetChannels() const { return m_Channels; }
    uint32_t GetTextureID() const { return m_TextureID; }
private:
    int m_Width;
    int m_Height;
    int m_Channels;
    uint32_t m_TextureID;
};
