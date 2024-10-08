#version 330 core

out vec4 fragColor;

uniform vec4 uColor;

in vec2 texCoord;
in vec4 color;

uniform sampler2D ourTexture;

void main()
{
    fragColor = texture(ourTexture,texCoord);
}