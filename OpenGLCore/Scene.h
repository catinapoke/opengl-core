#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"

#include "Camera.h"
#include "GraphicObject.h"
#include "Light.h"

// ����� ��� ������ �� ������
class Scene
{
public:
    // ����������� �� ���������
    Scene() = default;

    // ������������� ����� (��������: xml-���� � ��������� �������)
    void init(std::string filename);

    // �������� ����� �� xml-�����
    bool loadFromJSON(std::string filename);

    // ��������� ����� (���� ����������)
    void simulate(float sec);
    // ����� ���� ����� (����������� ��������� � RenderManager)
    void draw();

    GraphicObject createGraphicObject(std::string str);

    // ��������� ������ (��� � ����������� � ��������� �������� ��������� ������)
    Camera* getCamera();

    // ��������� ���������� � ����� (��� �������)
    std::string getSceneDescription();

private:
    // �������� ������� �� ��� �������������� � xml-����� ("models.xml")
    GraphicObject createGraphicObject(rapidjson::Value::ConstMemberIterator it);
    std::unordered_map<std::string, rapidjson::Value::ConstMemberIterator> objectInfo;
    rapidjson::Document* GetJsonDocument(std::string filename);
    vec3 StrToVec3(std::string str);
    vec4 StrToVec4(std::string str);

private:
    // ������
    Camera camera;
    // �������� �����
    Light light;
    // ��� ����������� �������
    std::vector<GraphicObject> graphicObjects;
    // json-�������� � ������� ���������� �������� ���� �������
    rapidjson::Document modelsDescription;
    // ��� ����� ����������� ����� (��� ������������ ����������� ���������)
    std::string sceneFilename;
};