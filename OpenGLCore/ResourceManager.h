#pragma once
#include <map>
#include <vector>

#include "Mesh.h"
#include "Texture.h"

// КЛАСС ДЛЯ РАБОТЫ С МЕНЕДЖЕРОМ РЕСУРСОВ (РЕАЛИЗОВАН НА ОСНОВЕ ШАБЛОНА SINGLETON)
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

private:
    // конструктор по умолчанию (объявлен приватным)
    // в результате нельзя создать ни одного объекта данного класса вне самого класса
    ResourceManager() {};
    // конструктора копирования нет
    ResourceManager(const ResourceManager& v) = delete;
    // оператора присваивания нет
    ResourceManager& operator=(const ResourceManager& v) = delete;

private:
    std::vector<Mesh*> meshes;
    std::map<std::string, int> meshes_id;

    std::vector<Texture*> textures;
    std::map<std::string, int> textures_id;
};