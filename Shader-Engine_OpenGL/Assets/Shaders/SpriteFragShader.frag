#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform bool canLoadTexture = true;
uniform vec3 spriteColor;

void main()
{    
    if(canLoadTexture){
        color = vec4(spriteColor, 1.0) * texture(image, TexCoords); // For when textures are needed.

    }else{
        color = vec4(spriteColor, 1.0) ;

    }
}  