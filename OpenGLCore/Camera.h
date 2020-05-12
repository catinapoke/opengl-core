#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp> 

using vec3 = glm::vec3;
using vec2 = glm::vec2;

class Camera
{
public:
    Camera(vec2 _speed = vec2(1.0f, 1.0f));
    Camera(vec3 position, vec2 _speed = vec2(180.0f, 1.0f));
    Camera(float x, float y, float z, float degrees = 180.0f, float zoom = 1.0f);

    void setPosition(glm::vec3 position);
    glm::vec3 getPosition();

    void rotateLeftRight(float miliseconds = 1000);
    void rotateUpDown(float miliseconds = 1000);
    void zoomInOut(bool closer);
    void rotate(vec2 delta);
    void moveCenter(vec3 delta);

    void setProjectionMatrix(float fovy, float aspect, float zNear, float zFar);
    glm::mat4& getProjectionMatrix();

    glm::mat4& getViewMatrix();

    glm::mat4 getModelViewMatrix(glm::vec3 modelPosition) const;
    glm::mat4 getModelViewMatrix(glm::mat4 modelMatrix) const;

private:
    void updateViewMatrix();
    void setViewMatrix(glm::vec3 cameraPosition, glm::vec3 target, glm::vec3 upVector);
    vec3 cartesianToSpherical(vec3 decartes);
    vec3 sphericalToCartesian(vec3 polar);

private:
    vec3 degree;	// (horizontal, vertical, radius)
    vec3 position;	// Расположение камеры
    vec2 speed;		// speed.x - radians, speed.y - zoom
    glm::vec3 center; // Куда смотреть
    glm::vec3 up;     // Вектор вверх

    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;

    static const float radian360; // 360 degrees = 6.283185 radians
    static const float radian85;
    static const float radian5;
};