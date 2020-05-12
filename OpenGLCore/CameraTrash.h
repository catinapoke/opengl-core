#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/transform.hpp>

class CameraTrash
{
public:
    // ����������� �� ���������
    CameraTrash();

    // ������� ��������
    void setProjectionMatrix(float fovy, float aspect, float zNear, float zFar);
    glm::mat4& getProjectionMatrix();

    // �������� ������� ����
    glm::mat4& getViewMatrix();

    // ����������� ������ � ����� ���������� � �������������� ��������� (OXZ)
    void move(glm::vec3 delta);
    // ��������� � �������������� � ������������ ���������
    void rotate(float horizontalAngle, float verticalAngle);
    void rotate(glm::vec2 deltaAngle);
    // ����������/������� ������ �/�� ����� ����������
    void zoom(bool zoomIn);

    glm::mat4 getModelViewMatrix(glm::vec3 modelPosition) const;
    glm::mat4 getModelViewMatrix(glm::mat4 modelMatrix) const;

    int rotationSpeed = 0.25f;

private:
    // ��������������� ������
    void updateViewMatrix();
    void setViewMatrix(glm::vec3 cameraPosition, glm::vec3 target, glm::vec3 upVector);

private:
    // ��������� ���� ������
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    glm::vec3 eye;    // ������������ ������
    glm::vec3 center; // ���� ��������
    glm::vec3 up;     // ������ �����
};