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

    GraphicObject createGraphicObject(std::string str);

    // Получение камеры (для её модификации в некоторых функциях обратного вызова)
    Camera* getCamera();

    // Получение информации о сцене (для отладки)
    std::string getSceneDescription();

private:
    // создание объекта по его идентификатору в xml-файле ("models.xml")
    GraphicObject createGraphicObject(rapidjson::Value::ConstMemberIterator it);
    std::unordered_map<std::string, rapidjson::Value::ConstMemberIterator> objectInfo;
    rapidjson::Document* GetJsonDocument(std::string filename);
    vec3 StrToVec3(std::string str);
    vec4 StrToVec4(std::string str);

private:
    // камера
    Camera camera;
    // источник света
    Light light;
    // все графические объекты
    std::vector<GraphicObject> graphicObjects;
    // json-документ в котором приводится описание всех моделей
    rapidjson::Document modelsDescription;
    // имя файла загруженной сцены (для формирования отладочного сообщения)
    std::string sceneFilename;
};