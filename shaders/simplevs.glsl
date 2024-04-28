#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;

out vec3 ourColor;

void main()
{
    ourColor = inColor;
    gl_Position = vec4(inPosition, 1.0);
}