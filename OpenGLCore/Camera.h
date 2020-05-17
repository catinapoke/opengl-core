#pragma once
#include "opengl.h"
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtx/polar_coordinates.hpp>
#include <GLM/gtx/euler_angles.hpp>

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

    void zoomInOut(bool closer);
    void rotate(vec2 delta);
    void update();
    void calcSpherical();
    void moveCenter(vec2 delta);

    void setProjectionMatrix(float fovy, float aspect, float zNear, float zFar);
    glm::mat4& getProjectionMatrix();

    glm::mat4& getViewMatrix();

    glm::mat4 getModelViewMatrix(glm::vec3 modelPosition) const;
    glm::mat4 getModelViewMatrix(glm::mat4 modelMatrix) const;

private:
    void setViewMatrix(glm::vec3 cameraPosition, glm::vec3 target, glm::vec3 upVector);


private:
    vec3 spherical;	       // r phi theta
    vec3 position;	       // Расположение камеры
    vec2 speed;		       // speed.x - radians, speed.y - zoom
    glm::vec3 lookAtPoint; // Куда смотреть

    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
};