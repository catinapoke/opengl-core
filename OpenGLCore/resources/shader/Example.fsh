#version 330 core

in vec3 Pos;
out vec4 FragColor;

uniform vec4 color;
uniform vec4 color2;

void main (void)
{
    if(Pos.x>Pos.y)
        FragColor = color;
    else
        FragColor = color2;
    
}
