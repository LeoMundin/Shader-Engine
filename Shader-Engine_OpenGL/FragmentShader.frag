#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// Provides access to our texture
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixAmount = 0.2;

void main()
{
    // Linearly interpolates between the two values based on the third parameter.
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixAmount);
}

