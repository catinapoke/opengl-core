#pragma once
#include <string>

#include "opengl.h"

#include "IL\il.h"
#include "IL\ilu.h"
#include "IL\ilut.h"

// ����� ��� ������ � ���������
class Texture
{
public:
    Texture();
    Texture(std::string filename);
    // �������� �������� �� �������� �����
    void load(std::string filename);
    // ���������� �������� (�������� � ����������� �����)
    void bind(GLenum texUnit = GL_TEXTURE0);
    static void unbind();

private:
    // ������ ����������� ������� � OpenGL
    GLuint texIndex;
};