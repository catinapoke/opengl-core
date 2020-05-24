#pragma once
#include <ctime>
#include <vector>

#include "opengl.h"

#include "ResourceManager.h"
#include "Shader.h"
#include "Camera.h"
#include "GraphicObject.h"
#include "Light.h"
#include "Material.h"

// ����� ��� �������������� � OPENGL
// ���� ����� �������������� ����� ������������ ��������� ������� ������
class RenderManager
{
public:
    // ������-����� ��� ��������� ���������� ������
    static RenderManager& instance()
    {
        static RenderManager renderManager;
        return renderManager;
    }

    // ������������� ������� RenderManager, ����������� ����� ������������� OpenGL:
    // �������� ��������, ��������� ���������� ���������� � ������ �������������
    void init(Shader shader);

    // ������ ������ ���������� ����� (����������, ������� ������� ����������� ��������)
    void start();
    // ��������� ������������ ������
    void setCamera(Camera* camera);
    // ��������� ������������� ��������� �����
    void setLight(Light* light);
    // ���������� � ������� ���������� ���������� ������� ��� ������
    void addToRenderQueue(GraphicObject* graphicObject);
    // ���������� ������ ����� (�������� ������)
    void finish();

    // ��������� ���������� FPS
    float getFPS();
    int getDrawCalls();
    int getMaterialChanges();

private:
    // ����������� �� ��������� (���������)
    RenderManager() :startTime(clock()), FPS(0), light(nullptr), camera(nullptr), elapsedTime(0), frames(0), materialChanges(0), drawCalls(0) {};
    // ������������ ����������� ���
    RenderManager(const RenderManager& root) = delete;
    // ��������� ������������ ���
    RenderManager& operator=(const RenderManager&) = delete;

    void SetRenderMaterial(Material* material);
    void DrawSingle(Shader& shader, std::vector<glm::mat4>& modelView, Mesh* mesh);
    void DrawInstanced(Shader& shader, std::vector<glm::mat4>& modelView, Mesh* mesh);
    // ������ ���������� FPS
    void calcFPS();

private:
    // ������������ �������
    std::vector<Shader> shaders;

    // ��������� �� ������
    Camera* camera;
    // ��������� �� �������� �����
    Light* light;
    // ��������� �� ��� ����������� �������, ������� ���������� ������� � ������ �����
    std::vector<GraphicObject*> graphicObjects;


    // ���������� ���������� ������ � �������
    float FPS;
    std::clock_t startTime;
    std::clock_t elapsedTime;
    int drawCalls;
    int materialChanges;
    int frames;
};