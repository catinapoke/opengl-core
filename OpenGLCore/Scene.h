#pragma once
#include <string>
#include <vector>
#include "rapidjson/document.h"

#include "Camera.h"
#include "GraphicObject.h"
#include "Light.h"

// ����� ��� ������ �� ������ 
class Scene
{
public:
    // ����������� �� ��������� 
    Scene();

    // ������������� ����� (��������: xml-���� � ��������� �������)
    void init(std::string filename); 
    // �������� ����� �� xml-����� 
    bool loadFromXML(std::string filename);

    // ��������� ����� (���� ����������) 
    void simulate(float sec);
    // ����� ���� ����� (����������� ��������� � RenderManager) 
    void draw();

    // ��������� ������ (��� � ����������� � ��������� �������� ��������� ������)
    Camera* getCamera(); 

    // ��������� ���������� � ����� (��� �������) 
    std::string getSceneDescription();

private:
    // �������� ������� �� ��� �������������� � xml-����� ("models.xml")
    GraphicObject createGraphicObject(std::string model_id); 

private:
    // ������  
    Camera camera;
    // �������� ����� 
    Light light;
    // ��� ����������� ������� 
    std::vector<GraphicObject> graphicObjects;
    // xml-�������� � ������� ���������� �������� ���� �������   
    rapidjson::Document modelsDescription;
    // ��� ����� ����������� ����� (��� ������������ ����������� ���������)
    std::string sceneFilename; 
};