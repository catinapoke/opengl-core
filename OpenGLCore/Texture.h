#pragma once
#include <string>

#include "opengl.h"

#include "IL\il.h"
#include "IL\ilu.h"
#include "IL\ilut.h"

// КЛАСС ДЛЯ РАБОТЫ С ТЕКСТУРОЙ
class Texture
{
public:
    Texture();
    Texture(std::string filename);
    // загрузка текстуры из внешнего файла
    void load(std::string filename);
    // применение текстуры (привязка к текстурному блоку)
    void bind(GLenum texUnit = GL_TEXTURE0);
    static void unbind();

private:
    // индекс текстурного объекта в OpenGL
    GLuint texIndex;
};