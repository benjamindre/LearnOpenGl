/**
 * @file Texture2D.h
 * @brief 纹理加载
 * @author Benjamin Enger (benjaminenger125522@gmail.com)
 * @date 2024-08-31 13:35:47
 * @version 1.0
 */

#pragma once

#include "Config.h"

#include <glad/glad.h>

/// @brief 使用是应尽可能的使用指针来初始化这个实例，因为它在析构函数中释放掉了 TextureID (纹理ID)。
/// 并且在较高的作用域中来包含这个指针，达到延迟释放的效果。如果作用域较小的话，读取完纹理后作用域结束会
/// 调用它的析构，导致纹理被释放
class Texture2D
{
public:
    Texture2D(std::string_view filename, bool flipVertically = true);
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
