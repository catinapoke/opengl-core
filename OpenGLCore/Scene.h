#pragma once
#include <string>
#include <vector>
#include "rapidjson/document.h"

#include "Camera.h"
#include "GraphicObject.h"
#include "Light.h"

// КЛАСС ДЛЯ РАБОТЫ СО СЦЕНОЙ 
class Scene
{
public:
    // конструктор по умолчанию 
    Scene();

    // Инициализация сцены (параметр: xml-файл с описанием моделей)
    void init(std::string filename); 
    // загрузка сцены из xml-файла 
    bool loadFromXML(std::string filename);

    // Симуляция сцены (если необходимо) 
    void simulate(float sec);
    // Вывод всей сцены (посредством обращения к RenderManager) 
    void draw();

    // Получение камеры (для её модификации в некоторых функциях обратного вызова)
    Camera* getCamera(); 

    // Получение информации о сцене (для отладки) 
    std::string getSceneDescription();

private:
    // создание объекта по его идентификатору в xml-файле ("models.xml")
    GraphicObject createGraphicObject(std::string model_id); 

private:
    // камера  
    Camera camera;
    // источник света 
    Light light;
    // все графические объекты 
    std::vector<GraphicObject> graphicObjects;
    // xml-документ в котором приводится описание всех моделей   
    rapidjson::Document modelsDescription;
    // имя файла загруженной сцены (для формирования отладочного сообщения)
    std::string sceneFilename; 
};