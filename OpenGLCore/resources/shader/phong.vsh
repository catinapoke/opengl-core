#version 330 core

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoord;

out vec3 position;
out vec3 normal;
void main ()
{
    position = vec3(modelViewMatrix * vec4 (vPosition, 1));
    normal = vec3(modelViewMatrix * vec4 (vNormal, 0));
    gl_Position = projectionMatrix * modelViewMatrix * vec4 (vPosition, 1);
}
