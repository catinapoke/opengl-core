#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/transform.hpp>

class CameraTrash
{
public:
    // конструктор по умолчанию
    CameraTrash();

    // Матрица проекции
    void setProjectionMatrix(float fovy, float aspect, float zNear, float zFar);
    glm::mat4& getProjectionMatrix();

    // получить матрицу вида
    glm::mat4& getViewMatrix();

    // передвинуть камеру и точку наблюдения в горизонтальной плоскости (OXZ)
    void move(glm::vec3 delta);
    // повернуть в горизонтальной и вертикальной плоскости
    void rotate(float horizontalAngle, float verticalAngle);
    void rotate(glm::vec2 deltaAngle);
    // приблизить/удалить камеру к/от точки наблюдения
    void zoom(bool zoomIn);

    glm::mat4 getModelViewMatrix(glm::vec3 modelPosition) const;
    glm::mat4 getModelViewMatrix(glm::mat4 modelMatrix) const;

    int rotationSpeed = 0.25f;

private:
    // вспомогательные методы
    void updateViewMatrix();
    void setViewMatrix(glm::vec3 cameraPosition, glm::vec3 target, glm::vec3 upVector);

private:
    // приватные поля класса
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    glm::vec3 eye;    // Расположение камеры
    glm::vec3 center; // Куда смотреть
    glm::vec3 up;     // Вектор вверх
};