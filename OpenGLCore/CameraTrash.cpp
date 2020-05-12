#include "CameraTrash.h"

CameraTrash::CameraTrash()
{
    eye = glm::vec3(0.0, 3.0, 5.0);     // Расположение камеры
    center = glm::vec3(0, 0, 0);        // Куда смотреть
    up = glm::vec3(0, 1, 0);            // Вектор вверх
    setViewMatrix(eye, center, up);
}

void CameraTrash::setProjectionMatrix(float fovy, float aspect, float zNear, float zFar)
{
    projectionMatrix = glm::perspective(glm::radians(fovy), aspect, zNear, zFar);
}

glm::mat4& CameraTrash::getProjectionMatrix()
{
    return projectionMatrix;
}

glm::mat4& CameraTrash::getViewMatrix()
{
    return viewMatrix;
}

void CameraTrash::move(glm::vec3 delta)
{
    viewMatrix = glm::translate(viewMatrix, delta);
}

void CameraTrash::rotate(float horizontalAngle, float verticalAngle)
{
    rotate(glm::vec2(horizontalAngle, verticalAngle));
}

void CameraTrash::rotate(glm::vec2 deltaAngle)
{
    float len = glm::length(deltaAngle);
    if (len == 0)
        return;
    glm::vec3 normalized = glm::normalize(glm::vec3(deltaAngle.y, deltaAngle.x, 0));
    printf("Delta - %f %f %f; Normalized - %f %f %f; Len - %f\n", deltaAngle.x, deltaAngle.y, 0, normalized.x, normalized.y, normalized.z, len);
    printf("Center - %f %f %f\n", center.x, center.y, center.z);

    viewMatrix = glm::translate(viewMatrix, -center);
    viewMatrix = glm::rotate(viewMatrix, glm::radians(len), normalized); // glm::vec3(1.0f, 0.0f, 0.0f)
    viewMatrix = glm::translate(viewMatrix, center);
}

void CameraTrash::zoom(bool zoomIn)
{
    glm::vec3 direction = glm::vec3(viewMatrix[3]) - center;
    if (zoomIn)
        direction *= -1;
    move(glm::normalize(direction));
}

glm::mat4 CameraTrash::getModelViewMatrix(glm::vec3 modelPosition) const
{
    glm::mat4 modelMatrix;
    modelMatrix = glm::mat4(
        glm::vec4(1, 0, 0, 0),  // 1-ый столбец: направление оси X
        glm::vec4(0, 1, 0, 0),  // 2-ой столбец: направление оси Y
        glm::vec4(0, 0, 1, 0),  // 3-ий столбец: направление оси Z
        glm::vec4(modelPosition.x, modelPosition.y, modelPosition.z, 1)); // 4-ый столбец: позиция объекта (начала координат)
    return getModelViewMatrix(modelMatrix);
}

glm::mat4 CameraTrash::getModelViewMatrix(glm::mat4 modelMatrix) const
{
    return viewMatrix * modelMatrix;
}

void CameraTrash::updateViewMatrix()
{
    setViewMatrix(eye, center, up);
}

void CameraTrash::setViewMatrix(glm::vec3 cameraPosition, glm::vec3 target, glm::vec3 upVector)
{
    viewMatrix = glm::lookAt(cameraPosition, target, upVector);
}