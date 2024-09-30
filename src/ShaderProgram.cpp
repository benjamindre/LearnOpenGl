#include "ShaderProgram.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(std::string_view vertexShader, std::string_view fragmentShader)
{
    uint32_t vertex = CreateShader(vertexShader, GL_VERTEX_SHADER);
    uint32_t fragment = CreateShader(fragmentShader, GL_FRAGMENT_SHADER);

    m_ProgramID = glCreateProgram();

    glAttachShader(m_ProgramID, vertex);
    glAttachShader(m_ProgramID, fragment);
    glLinkProgram(m_ProgramID);

    int32_t success;
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(m_ProgramID, 512, NULL, infoLog);
        std::cerr << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_ProgramID);
}

void ShaderProgram::Use() const
{
    glUseProgram(m_ProgramID);
}

void ShaderProgram::SetBool(std::string_view name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_ProgramID, name.data()), static_cast<int>(value));
}

void ShaderProgram::SetInt(std::string_view name, int value) const
{
    glUniform1i(glGetUniformLocation(m_ProgramID, name.data()), value);
}

void ShaderProgram::SetFloat(std::string_view name, float value) const
{
    glUniform1f(glGetUniformLocation(m_ProgramID, name.data()), value);
}

void ShaderProgram::SetVec3(std::string_view name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(m_ProgramID, name.data()), 1, glm::value_ptr(value));
}

void ShaderProgram::SetMat4(std::string_view name, const glm::mat4& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, name.data()), 1, GL_FALSE, glm::value_ptr(value));
}

uint32_t ShaderProgram::CreateShader(std::string_view filename, uint32_t type)
{
    std::ifstream shaderStream(filename.data(), std::ios::in);

    if (!shaderStream.is_open())
        assert(false && "opegl shader read error.");

    std::string line;
    std::stringstream shaderStreamStr;
    while (std::getline(shaderStream, line))
        shaderStreamStr << line << '\n';

    std::string shaderStr = shaderStreamStr.str();
    const char* shaderSource = shaderStr.c_str();

    uint32_t shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    int32_t success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << infoLog << std::endl;
    }

    return shader;
}