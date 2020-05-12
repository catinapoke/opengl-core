#version 330 core

uniform vec4 offset;

in vec3 vPosition;
out vec3 Pos;

void main ()
{
    Pos = vPosition;
	gl_Position = vec4 (vPosition + vec3(offset), 1);
}
