/**
 * @file Sphere.h
 * @brief 球体
 * @author Benjamin Enger (benjaminenger125522@gmail.com)
 * @date 2024-08-30
 * @version 1.0
 */
#pragma once

#include <cstdint>
#include <vector>

#define PI 3.14159265358979323846

class Sphere
{
public:
    Sphere(int stackCount = 18, int sectorCount = 36, float radius = 1.0f);
    ~Sphere();

    void Draw();

    const std::vector<float>& GetVertices() const { return m_Vertices; }
    const std::vector<float>& GetNormals() const { return m_Normals; }
    const std::vector<float>& GetTextureCoords() const { return m_TextureCoords; }
    const std::vector<int>& GetIndices() const { return m_Indices; }

private:
    void AxisRotation();
private:
    int m_StackCount;
    int m_SectorCount;
    float m_Radius;

    uint32_t m_VAO;
    uint32_t m_VBO[3];
    uint32_t m_EBO;

    std::vector<float> m_Vertices;
    std::vector<float> m_Normals;
    std::vector<float> m_TextureCoords;
    std::vector<int> m_Indices;
};
