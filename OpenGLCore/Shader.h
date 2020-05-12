#pragma once
#include <string>
#include <map>
#include <GL/glew.h>


#include "freeglut/freeglut.h"
#include <glm/vec4.hpp>
#include <glm/matrix.hpp>
#include "glm/gtc/type_ptr.hpp"

class Shader
{
private:
    unsigned int programId;

public:
    void create(const char* vertexPath, const char* fragmentPath);
    void use();
    static void disable();

    // utility uniform functions
    void setUniform(const std::string& name, bool value);
    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, glm::vec4 value);
    void setUniform(const std::string& name, glm::mat4 value);

private:
    unsigned int CompileShader(const char* shaderPath, int shaderType);
    std::map <std::string, GLuint> uniformLocations;
    GLuint getUniformLocation(std::string name);
};