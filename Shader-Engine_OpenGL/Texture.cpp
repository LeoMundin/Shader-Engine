#include "Texture.h"

Texture::Texture(const char* filePath, bool flipTexture)
{

    // Generate a texture object ID.
    glGenTextures(1, &ID);

    Bind();

    ConfigureParameters();


    // Loads the image from its file and fills the following int values with the corresponding data from the image.
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(flipTexture);
    unsigned char* imageData = stbi_load(filePath, &width, &height, &nrChannels, 0);


    // Determine the correct colour format based on the colour channels of the image data.
    GLenum colourFormat;
    switch (nrChannels) 
    {
        case 1:
            colourFormat = GL_RED;
            break;
        case 3:
            colourFormat = GL_RGB;
            break;
        case 4:
            colourFormat = GL_RGBA;
            break;
        default:
            colourFormat = GL_RGBA;
    }


    // Error checking
    if (imageData)
    {
        // Generate a texture from the image data and create a corresponding mipmap.
        glTexImage2D(GL_TEXTURE_2D, 0, colourFormat, width, height, 0, colourFormat, GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }


    // Good practice to clear the image data from memory.
    stbi_image_free(imageData);

}

void Texture::Bind() 
{
    // Bind to the object ID to configure commands for this specific texture.
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}



void Texture::ConfigureParameters() 
{
    // Configure texture wrap settings across the S and T axis.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    // Configure Filtering settings for magnifiying and minifiying operations, utilising Mipmaps for when the texture is minified.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}