#pragma once
#include <map>
#include <vector>
#include "Mesh.h"

// КЛАСС ДЛЯ РАБОТЫ С МЕНЕДЖЕРОМ РЕСУРСОВ (РЕАЛИЗОВАН НА ОСНОВЕ ШАБЛОНА SINGLETON)
class ResourceManager  
{
    public:
        // Статик-метод для получения экземпляра менеджера ресурса. 
        // Всегда будет возвращена ссылка на объект, хранящийся в единственном экземпляре.
        static ResourceManager& instance() 
        {
            static ResourceManager ResourceManager;
            return ResourceManager;
        }

        // Загрузка одного меша. 
        // Возвращаемое значение - индекс меша в менеджере ресурсов.
        int loadMesh(std::string filename); 

        // Получение меша по его индексу. 
        // Если такого меша нет (недействительный индекс) возвращается nullptr
        Mesh* getMesh(int index); 

    private:
        // конструктор по умолчанию (объявлен приватным) 
        // в результате нельзя создать ни одного объекта данного класса вне самого класса
        ResourceManager() {}; 
        // конструктора копирования нет 
        ResourceManager(const ResourceManager& v) = delete;
        // оператора присваивания нет 
        ResourceManager& operator=(const ResourceManager& v) = delete;

    private:
        // вектор для хранения всех мешей 
        std::vector<Mesh*> meshes;
        // map для хранения соответствия между именем запрашиваемого файла
        // и индексом в контейнере meshes  
        std::map<std::string, int> meshes_id;
};