#include "Model.h"
#include "Texture2D.h"

#include <iostream>
#include <stb_image.h>

Model::Model(std::string_view filename)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename.data(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    m_Directory = filename.substr(0, filename.find_last_of("/\\"));

    ProcessNode(scene->mRootNode, scene);
}

Model::~Model()
{

}

void Model::Draw(ShaderProgram* shaderProgram) const
{
    for (auto& mesh : m_Meshes)
        mesh->Draw(shaderProgram);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    for (int i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_Meshes.emplace_back(ProcessMesh(mesh, scene));
    }

    for (int i = 0; i < node->mNumChildren; ++i)
        ProcessNode(node->mChildren[i], scene);
}

std::unique_ptr<Mesh> Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<int> indices;
    std::vector<Texture> textures;

    for (int i = 0; i < mesh->mNumVertices; ++i)
    {
        Vertex vertex;
        vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);


        if(mesh->mTextureCoords[0]) // 网格是否有纹理坐标？
            vertex.TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    for (int i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);
    }

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Texture> diffuseTexture = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseTexture.begin(), diffuseTexture.end());

        std::vector<Texture> specularTexture = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularTexture.begin(), specularTexture.end());
    }


    return std::make_unique<Mesh>(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string_view typeName)
{
    std::vector<Texture> textures;

    for (int i = 0; i < material->GetTextureCount(type); ++i)
    {
        aiString str;
        material->GetTexture(type, i, &str);

        bool skip = false;
        for (int j = 0; j < m_TexturesLoaded.size(); ++j)
        {
            if (m_TexturesLoaded[j].Path == std::string(str.C_Str()))
            {
                textures.push_back(m_TexturesLoaded[j]);
                skip = true;
                break;
            }
        }

        if (!skip)
        {
            Texture texture;
            texture.Texture = std::make_shared<Texture2D>(m_Directory + "/" + std::string(str.C_Str()));
            texture.Type = typeName;
            texture.Path = std::string(str.C_Str());
            textures.push_back(texture);

            m_TexturesLoaded.push_back(texture);
        }
    }


    return textures;
}