/**
 * @file ModelLayer.h
 * @brief None
 * @author Benjamin Enger (benjaminenger125522@gmail.com)
 * @date 2024-09-01 16:55:42
 * @version 1.0
 */

#pragma once

#include "ILayer.h"
#include "Model.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "FrameBuffer.h"
#include "Application.h"

class ModelLayer : public ILayer
{
public:
    ModelLayer(Application* application);
    ~ModelLayer() override { }

    void Render(double time) override;
private:
    Application* m_Application;
    FrameBuffer m_FrameBuffer;
    ShaderProgram m_ShaderProgram;
    Model m_Model;

    Camera m_Camera;
};
