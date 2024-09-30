/**
 * @file ShaderProgram.h
 * @brief None
 * @author Benjamin Enger (benjaminenger125522@gmail.com)
 * @date 2024-08-31 12:12:06
 * @version 1.0
 */

#pragma once

#include "Config.h"

#include <glm/glm.hpp>

class ShaderProgram
{
public:
    ShaderProgram(std::string_view vertexShader, std::string_view fragmentShader);
    ~ShaderProgram();

    void Use() const;

    void SetBool(std::string_view name, bool value) const;
    void SetInt(std::string_view name, int value) const;
    void SetFloat(std::string_view name, float value) const;
    void SetVec3(std::string_view name, const glm::vec3& value) const;
    void SetMat4(std::string_view name, const glm::mat4& value) const;
private:
    static uint32_t CreateShader(std::string_view filename, uint32_t type);
private:
    uint32_t m_ProgramID;
};
