#include "ResourceManager.h"

int ResourceManager::loadMesh(std::string filename)
{
    std::map<std::string, int>::iterator it = meshes_id.find(filename);
    if (it != meshes_id.end())
        return it->second;

    meshes.push_back(new Mesh(filename));
    meshes_id.insert(std::pair<std::string, int>(filename, meshes.size() - 1));
    return meshes.size() - 1;
}

Mesh* ResourceManager::getMesh(int index)
{
    if (meshes.size() > index && index>=0)
        return meshes[index];
    return nullptr;
}

int ResourceManager::loadTexture(std::string filename)
{
    std::map<std::string, int>::iterator it = textures_id.find(filename);
    if (it != textures_id.end())
        return it->second;

    textures.push_back(new Texture(filename));
    textures_id.insert(std::pair<std::string, int>(filename, textures.size() - 1));
    return textures.size() - 1;
}

Texture* ResourceManager::getTexture(int index)
{
    if (textures.size() > index && index >= 0)
        return textures[index];
    return nullptr;
}

int ResourceManager::loadMaterial(Material* material)
{
    for (int i = 0; i < materials.size(); i++)
        if (material->operator==(*materials[i]))
            return i;

    materials.push_back(material);
    printf("Materials: %d\n", materials.size());
    return materials.size() - 1;
}

Material* ResourceManager::getMaterial(int index)
{
    if (materials.size() > index && index >= 0)
        return materials[index];
    return nullptr;
}