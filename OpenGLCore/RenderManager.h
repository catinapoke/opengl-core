#pragma once
#include <ctime>
#include <vector>

#include <GL/glew.h>
#include "freeglut/freeglut.h"
#include "glm/glm.hpp"

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

private:
    // ����������� �� ��������� (���������)
    RenderManager() :startTime(clock()), FPS(0), light(nullptr), camera(nullptr) {};
    // ������������ ����������� ���
    RenderManager(const RenderManager& root) = delete;
    // ��������� ������������ ���
    RenderManager& operator=(const RenderManager&) = delete;

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
    int frames;
};