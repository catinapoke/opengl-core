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
    if (meshes.size() > index)
        return meshes[index];
    return nullptr;
}