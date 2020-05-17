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

#define debug 1

// КЛАСС ДЛЯ РАБОТЫ СО СЦЕНОЙ
class Scene
{
public:
    // конструктор по умолчанию
    Scene() = default;

    // Инициализация сцены (параметр: xml-файл с описанием моделей)
    void init(std::string filename);

    // загрузка сцены из xml-файла
    bool loadFromJSON(std::string filename);

    // Симуляция сцены (если необходимо)
    void simulate(float sec);
    // Вывод всей сцены (посредством обращения к RenderManager)
    void draw();

    // Получение и установка камеры сцены
    Camera* getCamera();
    void SetCamera(Camera* camera);

    // Установка света
    void SetLight(Light* light);

    // Получение информации о сцене (для отладки)
    std::string getSceneDescription();

private:
    // создание объекта по его идентификатору в json-файле ("models.xml")
    GraphicObject createGraphicObject(std::string str);
    // создание объекта по ссылке на его описание в rapidjson::Document
    GraphicObject createGraphicObject(rapidjson::Value::ConstMemberIterator it);
    // Чтение rapidjson::Document из файла filename
    rapidjson::Document* GetJsonDocument(std::string filename);
    // Преобразование строк в вектора с помощью потоков
    vec3 StrToVec3(std::string str);
    vec4 StrToVec4(std::string str);

private:
    // Камера
    Camera* camera;
    // Источник света
    Light* light;
    // Все графические объекты сцены
    std::vector<GraphicObject> graphicObjects;
    // json-документ в котором приводится описание всех моделей
    rapidjson::Document* modelsDescription;
    // имя файла загруженной сцены (для формирования отладочного сообщения)
    std::string sceneFilename;
};