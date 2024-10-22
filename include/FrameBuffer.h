/**
 * @file FrameBuffer.h
 * @brief None
 * @author Benjamin Enger (benjaminenger125522@gmail.com)
 * @date 2024-08-30
 * @version 1.0
 */
#pragma once

#include "Config.h"

#include <cstdint>

class FrameBuffer
{
public:
    FrameBuffer(int width, int height);

    ~FrameBuffer();

    void BindFrameBuffer(bool depthTest);

    void UnbindFrameBuffer();

    void RescaleFramebuffer(int width, int height);

    uint32_t GetTextureID() const { return m_TextureID; }
private:
    uint32_t m_FBO;
    uint32_t m_TextureID;
    uint32_t m_RBO;
};
