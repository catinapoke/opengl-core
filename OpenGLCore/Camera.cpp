#include "Camera.h"

const float Camera::radian360 = 6.283185f; // 360 degrees = 6.283185 radians
const float Camera::radian85 = 1.48353f;
const float Camera::radian5 = 0.087266f;

Camera::Camera(vec2 _speed) :Camera(vec3(2), _speed)
{
}

Camera::Camera(float x, float y, float z, float degrees, float zoom) : Camera(vec3(x, y, z), vec2(degrees, zoom))
{
}

Camera::Camera(vec3 position, vec2 _speed)
{
    setPosition(position);
    speed = _speed;
    speed.x = glm::radians(speed.x);

    center = vec3(0.f, 0.f, 0.f);
    up = vec3(0.f, 1.f, 0.f);
    updateViewMatrix();
}

void Camera::setPosition(vec3 _position)
{
    position = _position;
    degree = cartesianToSpherical(position - center);

    updateViewMatrix();
}

void Camera::moveCenter(vec3 delta)
{
    delta = vec3(delta.x, delta.y, -delta.z);
    glm::vec3 cameraDirection = glm::normalize(position - center);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    //glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

    float dem = glm::orientedAngle(vec3(0.0f, 0.0f, 1.0f), cameraDirection, up);
    printf("Dir: %f %f %f\n", cameraDirection.x, cameraDirection.y, cameraDirection.z);
    printf("Angle: %f rad = %f\n", dem, glm::degrees(dem));
    printf("Delta before: %f %f %f", delta.x, delta.y, delta.z);
    delta = glm::rotateY(delta, dem);
    printf(" Delta: %f %f %f\n", delta.x, delta.y, delta.z);

    center += delta;
    position += delta;
    updateViewMatrix();
}

vec3 Camera::getPosition()
{
    return position;
}

void Camera::rotate(vec2 delta)
{
    rotateLeftRight(delta.x);
    rotateUpDown(delta.y);
    updateViewMatrix();
}

void Camera::rotateLeftRight(float delta)
{
    degree.x += delta * speed.x;
    if (degree.x > radian360)
        degree.x -= radian360;
    else if (degree.x < 0)
        degree.x += radian360;

    position = sphericalToCartesian(degree) + center;
}

void Camera::rotateUpDown(float delta)
{
    degree.y += delta * speed.x;
    if (degree.y > radian85)
        degree.y = radian85;
    else
    {
        if (degree.y < radian5)
            degree.y = radian5;
    }

    position = sphericalToCartesian(degree) + center;
}

void Camera::zoomInOut(bool closer)
{
    degree.z += (closer ? -1 : 1) * speed.y;

    if (degree.z < 1)
        degree.z = 1;
    else if (degree.z > 50)
        degree.z = 50;

    position = sphericalToCartesian(degree) + center;

    updateViewMatrix();
}

void Camera::setProjectionMatrix(float fovy, float aspect, float zNear, float zFar)
{
    projectionMatrix = glm::perspective(glm::radians(fovy), aspect, zNear, zFar);
}

glm::mat4& Camera::getProjectionMatrix()
{
    return projectionMatrix;
}

glm::mat4& Camera::getViewMatrix()
{
    return viewMatrix;
}

glm::mat4 Camera::getModelViewMatrix(glm::vec3 modelPosition) const
{
    glm::mat4 modelMatrix;
    modelMatrix = glm::mat4(
        glm::vec4(1, 0, 0, 0),  // 1-ый столбец: направление оси X
        glm::vec4(0, 1, 0, 0),  // 2-ой столбец: направление оси Y
        glm::vec4(0, 0, 1, 0),  // 3-ий столбец: направление оси Z
        glm::vec4(modelPosition.x, 
            modelPosition.y, modelPosition.z, 1)); // 4-ый столбец: позиция объекта (начала координат)
    return getModelViewMatrix(modelMatrix);
}

glm::mat4 Camera::getModelViewMatrix(glm::mat4 modelMatrix) const
{
    return viewMatrix * modelMatrix;
}

void Camera::setViewMatrix(glm::vec3 cameraPosition, glm::vec3 target, glm::vec3 upVector)
{
    viewMatrix = glm::lookAt(cameraPosition, target, upVector);
}

void Camera::updateViewMatrix()
{
    setViewMatrix(position, center, up);
}


vec3 Camera::cartesianToSpherical(vec3 cartesian)
{
    vec3 polar;
    if (cartesian.z == 0)
    {
        if (cartesian.x > 0)
            polar.x = 1.570796;// 90 deg = 1.570796 rad
        else
            polar.x = 4.712389;// 270 degree
    }
    else
        polar.x = atan(cartesian.x / cartesian.z);

    double OM = sqrt(cartesian.x * cartesian.x + cartesian.z * cartesian.z);

    if (OM == 0)
    {
        if (cartesian.y > 0)
            polar.y = 1.570796;// 90 deg = 1.570796 rad
        else
            polar.y = 4.712389;// 270 degree
    }
    else
        polar.y = atan(cartesian.y / OM);

    polar.z = sqrt(cartesian.y * cartesian.y + OM * OM);

    return polar;
}

vec3 Camera::sphericalToCartesian(vec3 polar)
{
    vec3 cartesian;
    cartesian.y = polar.z * sin(polar.y);
    float OM = polar.z * cos(polar.y);
    cartesian.z = OM * cos(polar.x);
    cartesian.x = OM * sin(polar.x);
    return cartesian;
}