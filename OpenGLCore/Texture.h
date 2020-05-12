#pragma once
#include <string>
#include <GL/glew.h>

// КЛАСС ДЛЯ РАБОТЫ С ТЕКСТУРОЙ 
class Texture
{
public:
    // загрузка текстуры из внешнего файла
    void load (std::string filename);
    // применение текстуры (привязка к текстурному блоку)
    void bind (GLenum texUnit = GL_TEXTURE0); 

private:
    // индекс текстурного объекта в OpenGL
    GLuint texIndex; 
};