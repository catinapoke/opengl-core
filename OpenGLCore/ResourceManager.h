#pragma once
#include <map>
#include <vector>
#include "Mesh.h"

// ����� ��� ������ � ���������� �������� (���������� �� ������ ������� SINGLETON)
class ResourceManager  
{
    public:
        // ������-����� ��� ��������� ���������� ��������� �������. 
        // ������ ����� ���������� ������ �� ������, ���������� � ������������ ����������.
        static ResourceManager& instance() 
        {
            static ResourceManager ResourceManager;
            return ResourceManager;
        }

        // �������� ������ ����. 
        // ������������ �������� - ������ ���� � ��������� ��������.
        int loadMesh(std::string filename); 

        // ��������� ���� �� ��� �������. 
        // ���� ������ ���� ��� (���������������� ������) ������������ nullptr
        Mesh* getMesh(int index); 

    private:
        // ����������� �� ��������� (�������� ���������) 
        // � ���������� ������ ������� �� ������ ������� ������� ������ ��� ������ ������
        ResourceManager() {}; 
        // ������������ ����������� ��� 
        ResourceManager(const ResourceManager& v) = delete;
        // ��������� ������������ ��� 
        ResourceManager& operator=(const ResourceManager& v) = delete;

    private:
        // ������ ��� �������� ���� ����� 
        std::vector<Mesh*> meshes;
        // map ��� �������� ������������ ����� ������ �������������� �����
        // � �������� � ���������� meshes  
        std::map<std::string, int> meshes_id;
};