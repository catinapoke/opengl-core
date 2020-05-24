#include <fstream>
#include <sstream>
#include "Shader.h"

#include <functional>
#include <glm/mat4x2.hpp>
#include <iostream>

void Shader::create(const char* vertexPath, const char* fragmentPath)
{
    unsigned int vertexShader, fragmentShader;
    vertexShader = CompileShader(vertexPath, GL_VERTEX_SHADER);
    fragmentShader = CompileShader(fragmentPath, GL_FRAGMENT_SHADER);

    // shader Program
    programId = glCreateProgram();
    glAttachShader(programId, vertexShader);
    glAttachShader(programId, fragmentShader);
    glLinkProgram(programId);
    // print linking errors if any
    int success;
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(programId, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }

    // delete the shaders as they're linked into our program now and no longer neccessery
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use()
{
    glUseProgram(programId);
}

void Shader::disable()
{
    glUseProgram(0);
}

void Shader::setUniform(const std::string& name, bool value)
{
    GLuint location = getUniformLocation(name);
    glUniform1i(location, value ? 1 : 0);
}

void Shader::setUniform(const std::string& name, int value)
{
    GLuint location = getUniformLocation(name);
    glUniform1i(location, value);
}

void Shader::setUniform(const std::string& name, float value)
{
    GLuint location = getUniformLocation(name);
    glUniform1f(location, value);
}

void Shader::setUniform(const std::string& name, glm::vec4 value)
{
    GLuint location = getUniformLocation(name);
    glUniform4f(location, value.r, value.g, value.b, value.a);
}

void Shader::setUniform(const std::string& name, glm::mat4 value)
{
    GLuint location = getUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniform(const std::string& name, std::vector<glm::mat4>& value)
{
    GLuint location = getUniformLocation(name);
    glUniformMatrix4fv(location, value.size(), GL_FALSE, glm::value_ptr(value[0]));
}

void Shader::setUniform(const std::string& name, glm::mat4* value, int arraySize)
{
    GLuint location = getUniformLocation(name);
    glUniformMatrix4fv(location, arraySize, GL_FALSE, glm::value_ptr(value[0]));
}

unsigned int Shader::CompileShader(const char* shaderPath, int shaderType)
{
    // 1. retrieve the shader source code from filePath
    std::string shaderCode;
    std::ifstream shaderFile;
    // ensure ifstream objects can throw exceptions:
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;
        // read file's buffer contents into streams
        shaderStream << shaderFile.rdbuf();
        // close file handlers
        shaderFile.close();
        // convert stream into string
        shaderCode = shaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        printf("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n");
    }
    const char* cstr_shaderCode = shaderCode.c_str();
    // 2. compile shader
    unsigned int shader;
    int success;
    char infoLog[512];

    // Compilation
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &cstr_shaderCode, NULL);
    glCompileShader(shader);
    // print compile errors if any
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
    };
    return shader;
}

GLuint Shader::getUniformLocation(std::string name)
{
    if (!uniformLocations.contains(name))
    {
        uniformLocations[name] = glGetUniformLocation(programId, name.c_str());
    }
    return uniformLocations[name];
}