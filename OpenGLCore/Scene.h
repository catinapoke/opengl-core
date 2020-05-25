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

    

    // ��������� � ��������� ������ �����
    Camera* getCamera();
    void SetCamera(Camera* camera);

    // ��������� �����
    void SetLight(Light* light);

    // ��������� ���������� � ����� (��� �������)
    std::string getSceneDescription();

private:
    // �������� ������� �� ��� �������������� � json-����� ("models.xml")
    GraphicObject createGraphicObject(std::string str);
    // �������� ������� �� ������ �� ��� �������� � rapidjson::Document
    GraphicObject createGraphicObject(rapidjson::Value::ConstMemberIterator it);
    // ������ rapidjson::Document �� ����� filename
    rapidjson::Document* GetJsonDocument(std::string filename);
    // �������������� ����� � ������� � ������� �������
    vec3 StrToVec3(std::string str);
    vec4 StrToVec4(std::string str);
    // LOD check realisation
    bool LODSkip(GraphicObject& graphicObject, glm::vec3& cameraPosition);
    bool FrustrumCullingSkip(GraphicObject& graphicObject, Camera& camera);
    bool FrustrumCullingSkip(GraphicObject& graphicObject, glm::mat4& projectionViewMatrix);

private:
    // ������
    Camera* camera;
    // �������� �����
    Light* light;
    // ��� ����������� ������� �����
    std::vector<GraphicObject> graphicObjects;
    // json-�������� � ������� ���������� �������� ���� �������
    rapidjson::Document* modelsDescription;
    // ��� ����� ����������� ����� (��� ������������ ����������� ���������)
    std::string sceneFilename;
    static const std::unordered_map<GraphicObjectType, int> LODDistance;
};