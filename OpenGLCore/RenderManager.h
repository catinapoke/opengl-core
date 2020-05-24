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

// КЛАСС ДЛЯ ВЗАИМОДЕЙСТВИЯ С OPENGL
// ВЕСЬ ВЫВОД ОСУЩЕСТВЛЯЕТСЯ ЧЕРЕЗ ЕДИНСТВЕННЫЙ ЭКЗЕМПЛЯР ДАННОГО КЛАССА
class RenderManager
{
public:
    // Статик-метод для получения экземпляра класса
    static RenderManager& instance()
    {
        static RenderManager renderManager;
        return renderManager;
    }

    // инициализация объекта RenderManager, выполняется после инициализации OpenGL:
    // загрузка шейдеров, установка неизменных параметров и прочая инициализация
    void init(Shader shader);

    // Начало вывода очередного кадра (подготовка, очистка вектора графических объектов)
    void start();
    // установка используемой камеры
    void setCamera(Camera* camera);
    // установка используемого источника света
    void setLight(Light* light);
    // добавление в очередь рендеринга очередного объекта для вывода
    void addToRenderQueue(GraphicObject* graphicObject);
    // завершение вывода кадра (основная работа)
    void finish();

    // получение количество FPS
    float getFPS();
    int getDrawCalls();
    int getMaterialChanges();

private:
    // конструктор по умолчанию (приватный)
    RenderManager() :startTime(clock()), FPS(0), light(nullptr), camera(nullptr), elapsedTime(0), frames(0), materialChanges(0), drawCalls(0) {};
    // конструктора копирования нет
    RenderManager(const RenderManager& root) = delete;
    // оператора присваивания нет
    RenderManager& operator=(const RenderManager&) = delete;

    void SetRenderMaterial(Material* material);
    void DrawSingle(Shader& shader, std::vector<glm::mat4>& modelView, Mesh* mesh);
    void DrawInstanced(Shader& shader, std::vector<glm::mat4>& modelView, Mesh* mesh);
    // расчет количества FPS
    void calcFPS();

private:
    // используемые шейдеры
    std::vector<Shader> shaders;

    // указатель на камеру
    Camera* camera;
    // указатель на источник света
    Light* light;
    // указатели на все графические объекты, которые необходимо вывести в данном кадре
    std::vector<GraphicObject*> graphicObjects;


    // измеренное количество кадров в секунду
    float FPS;
    std::clock_t startTime;
    std::clock_t elapsedTime;
    int drawCalls;
    int materialChanges;
    int frames;
};