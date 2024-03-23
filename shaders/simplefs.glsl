#version 330 core
out vec4 fragColor;
uniform float uMoveX;
void main()
{
    fragColor = vec4(sin(abs(uMoveX)),cos(uMoveX),0.0f,1.0f);
}