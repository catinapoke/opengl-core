#pragma once
#include <map>
#include <vector>

#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

// ����� ��� ������ � ���������� �������� (���������� �� ������ ������� SINGLETON)
class ResourceManager
{
public:
    static ResourceManager& instance()
    {
        static ResourceManager ResourceManager;
        return ResourceManager;
    }

    int loadMesh(std::string filename);
    Mesh* getMesh(int index);

    int loadTexture(std::string filename);
    Texture* getTexture(int index);

    int loadMaterial(Material* material);
    Material* getMaterial(int index);

private:
    // ����������� �� ��������� (�������� ���������)
    // � ���������� ������ ������� �� ������ ������� ������� ������ ��� ������ ������
    ResourceManager() {};
    // ������������ ����������� ���
    ResourceManager(const ResourceManager& v) = delete;
    // ��������� ������������ ���
    ResourceManager& operator=(const ResourceManager& v) = delete;

private:
    std::vector<Mesh*> meshes;
    std::map<std::string, int> meshes_id;

    std::vector<Texture*> textures;
    std::map<std::string, int> textures_id;

    std::vector<Material*> materials;
    std::map<Material, int> materials_id;
};