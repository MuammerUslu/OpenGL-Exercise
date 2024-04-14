#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inTexCoord;

uniform mat4 uMtxTransform;

out vec4 color;
out vec2 texCoord;

void main()
{
     gl_Position = uMtxTransform*vec4(inPosition, 1.0);
     color = inColor;
     texCoord = inTexCoord;
}
