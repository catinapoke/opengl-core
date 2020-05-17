#include "Camera.h"

Camera::Camera(vec2 _speed) :Camera(vec3(2), _speed)
{
}

Camera::Camera(float x, float y, float z, float degrees, float zoom) : Camera(vec3(x, y, z), vec2(degrees, zoom))
{
}

Camera::Camera(vec3 position, vec2 _speed)
{
    speed = _speed;
    speed.x = glm::radians(speed.x);

    this->position = position;
    this->lookAtPoint = vec3(0);
    calcSpherical();
    update();
}

void Camera::setPosition(vec3 _position)
{
    position = _position;
    calcSpherical();
    update();
}

void Camera::moveCenter(vec2 delta)
{
    vec3 lookEye = lookAtPoint - position;
    lookEye.y = 0;
    vec3 forward = normalize(lookEye);
    vec3 right = cross(vec3(0, 1, 0), forward);
    vec3 dpos = forward * delta.x + right * delta.y;
    this->position += dpos;
    this->lookAtPoint += dpos;
    update();
}

vec3 Camera::getPosition()
{
    return position;
}

// Delta.x - horizontal, delta.y - vertical
void Camera::rotate(vec2 delta)
{
    this->spherical.y += delta.x;
    if (spherical.y < -360 || spherical.y > 360)
        spherical.y -= spherical.y;
    this->spherical.z = glm::clamp<float>(spherical.z + delta.y, 5.0f, 85.0f);
    update();
}

void Camera::update()
{
    glm::mat4 R = glm::yawPitchRoll<float>(-glm::radians(spherical.y), -glm::radians(spherical.z), 0);
    glm::vec4 T = R * glm::vec4(0, 0, spherical.x, 0);
    position = lookAtPoint + vec3(T);
    this->viewMatrix = glm::lookAt(this->position, this->lookAtPoint, vec3(0, 1, 0));
    // debug();
}

void Camera::calcSpherical()
{
    float dist = glm::distance(lookAtPoint, position);

    vec3 projXY = vec3(position.x, position.y, 0);
    vec3 projZX = vec3(position.x, 0, position.z);
    this->spherical = vec3(
        dist,
        glm::degrees((glm::acos(glm::dot(glm::normalize(position), glm::normalize(projZX))))),	// PHI Y
        glm::degrees(glm::acos(glm::dot(glm::normalize(projXY), glm::normalize(projZX))))		// THETA Z
    );
}

void Camera::zoomInOut(bool closer)
{
    float distance = (closer ? -1 : 1) * speed.y;
    this->spherical.x = glm::clamp<float>(this->spherical.x + distance, 3.0f, 120.0f);
    update();
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