/**
 * @file ChapterLayer.h
 * @brief None
 * @author Benjamin Enger (benjaminenger125522@gmail.com)
 * @date 2024-08-31 11:45:07
 * @version 1.0
 */

#pragma once

#include "ILayer.h"
#include "FrameBuffer.h"
#include "Sphere.h"
#include "Camera.h"
#include "Texture2D.h"
#include "ShaderProgram.h"
#include "Application.h"

struct LightMaterial
{
    glm::vec3 Position;
    glm::vec3 Direction;
    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Specular;
};

class ChapterLayer : public ILayer
{
public:
    ChapterLayer(Application* application, int width, int height);

    ~ChapterLayer() override;

    void Render(double time) override;
private:
    Application* m_Application;
    FrameBuffer m_FrameBuffer;
    Texture2D m_BoxEmission;
    Texture2D m_BoxDiffuse;
    Texture2D m_BoxSpecular;
    ShaderProgram m_BoxProgram;
    ShaderProgram m_LightProgram;

    uint32_t m_CubeVAO;
    uint32_t m_CubeVBO;
    Camera m_Camera;
    LightMaterial m_LightMaterial;
};

