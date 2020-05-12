#pragma once
#include <string>
#include <GL/glew.h>

// ����� ��� ������ � ��������� 
class Texture
{
public:
    // �������� �������� �� �������� �����
    void load (std::string filename);
    // ���������� �������� (�������� � ����������� �����)
    void bind (GLenum texUnit = GL_TEXTURE0); 

private:
    // ������ ����������� ������� � OpenGL
    GLuint texIndex; 
};