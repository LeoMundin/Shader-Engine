#version 330 core
out vec4 FragColor;

// Lighting
in vec3 Normal;  
in vec3 FragPos;  
uniform vec3 viewPos;
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

    vec3 vertexNormal = normalize(Normal);

    // Ambient Light - Consistent encompasing light, multiplied by the lights strength and colour.
    float ambientStrength = 0.2f;
    vec3 ambientLight = ambientStrength * lightColor;

    // Diffuse Light - Adjusts light strength based on how much the fragment is facing away from the light direction.
    vec3 lightDir = normalize(lightPos - FragPos);
    float lightAngle = max(dot(vertexNormal, lightDir), 0.0);
    vec3 diffuseLight = lightAngle * lightColor;

    // Specular Light
    float specularStrength = 0.5;
    float specularShininess = 32; // Higher the value the more concentrated the shine.
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, vertexNormal);  
    float specularAngle = pow(max(dot(viewDir, reflectDir), 0.0), specularShininess);
    vec3 specularLight = specularStrength * specularAngle * lightColor;  



    vec3 calculatedLight = (ambientLight + diffuseLight + specularLight) * objectColor;

    vec4 litTexture = vec4(calculatedLight, 1.0) * mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixAmount);
    FragColor = litTexture;

}
