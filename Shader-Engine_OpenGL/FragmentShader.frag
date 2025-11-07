#version 330 core
out vec4 FragColor;


// Lighting
in vec3 Normal;  
in vec3 FragPos;  
uniform vec3 lightPos;  
uniform vec3 objectColor;
uniform vec3 lightColor;

// Texture
in vec2 TexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixAmount = 0;

void main()
{

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);  

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float ambientStrength = 0.2f;
    vec3 ambientLight = ambientStrength * lightColor;
    vec3 calculatedAmbient = ambientLight * objectColor;

    vec4 lightTexture = vec4(calculatedAmbient, 1.0) * mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixAmount);

    FragColor = lightTexture;
}
