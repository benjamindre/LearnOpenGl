#include "Sphere.h"

#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Sphere::Sphere(int stackCount, int sectorCount, float radius)
    : m_StackCount(stackCount), m_SectorCount(sectorCount), m_Radius(radius)
{
    float sectorStep = 2 * PI / m_SectorCount;
    float stackStep = PI / m_StackCount;

    float sectorAngle, stackAngle;
    for (int x = 0; x <= m_StackCount; ++x)
    {
        stackAngle = PI / 2 - x * stackStep;
        float zPos = m_Radius * sin(stackAngle);

        for (int y = 0; y <= m_SectorCount; ++y)
        {
            sectorAngle = y * sectorStep;

            float yPos = m_Radius * cos(stackAngle) * cos(sectorAngle);
            float xPos = m_Radius * cos(stackAngle) * sin(sectorAngle);

            m_Vertices.push_back(xPos);
            m_Vertices.push_back(yPos);
            m_Vertices.push_back(zPos);

            m_Normals.push_back(xPos * (1.0f / m_Radius));
            m_Normals.push_back(yPos * (1.0f / m_Radius));
            m_Normals.push_back(zPos * (1.0f / m_Radius));

            m_TextureCoords.push_back(static_cast<float>(y) / m_SectorCount);
            m_TextureCoords.push_back(static_cast<float>(x) / m_StackCount);
        }
    }

    uint32_t k1, k2;
    for(int i = 0; i < m_StackCount; ++i)
    {
        k1 = i * (m_SectorCount + 1);     // beginning of current stack
        k2 = k1 + m_SectorCount + 1;      // beginning of next stack

        for(int j = 0; j < m_SectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding 1st and last stacks
            if(i != 0)
            {
                m_Indices.push_back(k1);
                m_Indices.push_back(k2);
                m_Indices.push_back(k1 + 1);
            }

            if(i != (m_StackCount - 1))
            {
                m_Indices.push_back(k1 + 1);
                m_Indices.push_back(k2);
                m_Indices.push_back(k2 + 1);
            }
        }
    }
    // 由于绘制出来的顶点数组是 +Z 轴朝向屏幕，正上方是 +Z轴
    // 所以需要旋转 +Y 轴变换到 +Z 轴朝上，+Z代表北极
    // Y -> Z
    AxisRotation();

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(3, m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float), m_Vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, m_Normals.size() * sizeof(float), m_Normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, m_TextureCoords.size() * sizeof(float), m_TextureCoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(int), m_Indices.data(), GL_STATIC_DRAW);
}

void Sphere::Draw()
{
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Sphere::~Sphere()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(3, m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void Sphere::AxisRotation()
{
    float tx[] = {1.0f, 0.0f, 0.0f};     // x-axis (left)
    float ty[] = {0.0f, 0.0f, 1.0f};     // y-axis (up)
    float tz[] = {0.0f, -1.0f, 0.0f};    // z-axis (forward)

    for (int i = 0; i < m_Vertices.size(); i += 3)
    {
        float x = m_Vertices[i];
        float y = m_Vertices[i + 1];
        float z = m_Vertices[i + 2];
        m_Vertices[i] = x * tx[0] + y * ty[0] + z * tz[0];
        m_Vertices[i + 1] = x * tx[1] + y * ty[1] + z * tz[1];
        m_Vertices[i + 2] = x * tx[2] + y * ty[2] + z * tz[2];

        float nx = m_Normals[i];
        float ny = m_Normals[i + 1];
        float nz = m_Normals[i + 2];
        m_Normals[i] = nx * tx[0] + ny * ty[0] + nz * tz[0];
        m_Normals[i + 1] = nx * tx[1] + ny * ty[1] + nz * tz[1];
        m_Normals[i + 2] = nx * tx[2] + ny * ty[2] + nz * tz[2];
    }
}