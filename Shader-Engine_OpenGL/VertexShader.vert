#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float xOffset;

out vec3 ourColor;

void main()
{

    vec3 inversePos = -aPos;
    inversePos.x = inversePos.x + xOffset;

    gl_Position = vec4(inversePos, 1.0);
    ourColor = aColor;
}