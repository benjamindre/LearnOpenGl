/**
 * @file Mesh.h
 * @brief None
 * @author Benjamin Enger (benjaminenger125522@gmail.com)
 * @date 2024-09-01 15:31:57
 * @version 1.0
 */

#pragma once

#include "Config.h"
#include "ShaderProgram.h"

#include <glm/glm.hpp>

#include <vector>

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    uint32_t TextureID;
    std::string Type;
    std::string Path;
};

class Mesh
{
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<int>& indices, const std::vector<Texture>& textures);
    ~Mesh();

    void Draw(ShaderProgram* shader) const;

private:
    void Init();

private:
    uint32_t m_VAO;
    uint32_t m_VBO;
    uint32_t m_EBO;

    std::vector<Vertex> m_Vertices;
    std::vector<int> m_Indices;
    std::vector<Texture> m_Textures;
};
