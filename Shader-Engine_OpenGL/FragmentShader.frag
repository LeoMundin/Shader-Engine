#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixAmount = 0;

void main()
{

    float ambientStrength = 0.2f;
    vec3 ambientLight = ambientStrength * lightColor;
    vec3 calculatedAmbient = ambientLight * objectColor;

    vec4 lightTexture = vec4(calculatedAmbient, 1.0) * mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixAmount);

    FragColor = lightTexture;
}
