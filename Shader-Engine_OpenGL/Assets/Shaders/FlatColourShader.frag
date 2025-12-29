#version 330 core
out vec4 FragColor;

// Lighting
in vec3 Normal;  
in vec3 FragPos;  
uniform vec3 viewPos;
uniform vec3 lightPos;  
uniform vec3 objectColor =  vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightColor = vec3( 1.0f, 0.9f, 0.4f);

// Helper Methods
vec3 CalculateLighting();


void main()
{


    vec3 calculatedLight = CalculateLighting();

    vec4 litTexture = vec4(calculatedLight, 1.0) *  vec4(objectColor,1.0);

    FragColor = litTexture  ;

}




// Calculates phong lighting, 
// returning the combined lighting effect as vec3.
vec3 CalculateLighting()
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



    vec3 light = (ambientLight + diffuseLight + specularLight) * objectColor;

    return light;
}