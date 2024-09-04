/**
 * @file Model.h
 * @brief None
 * @author Benjamin Enger (benjaminenger125522@gmail.com)
 * @date 2024-09-01 16:13:54
 * @version 1.0
 */

#pragma once

#include "Config.h"
#include "Mesh.h"
#include "ShaderProgram.h"

#include <string_view>
#include <vector>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
    Model(std::string_view filename);
    ~Model();

    void Draw(ShaderProgram* shaderProgram) const;

private:
    /// 处理节点
    void ProcessNode(aiNode* node, const aiScene* scene);

    /// 处理网格
    std::unique_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<Texture> LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string_view typeName);
private:
    std::string m_Directory;
    std::vector<std::unique_ptr<Mesh>> m_Meshes;

    std::vector<Texture> m_TexturesLoaded;
};
