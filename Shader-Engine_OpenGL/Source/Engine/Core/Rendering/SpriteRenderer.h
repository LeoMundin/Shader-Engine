#pragma once
#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <glad/glad.h>
#include"Shaders/Shader.h"
#include"Texture.h"


class SpriteRenderer
{
public:

    SpriteRenderer() {};
    SpriteRenderer(Shader shader) 
    {
        _shader = shader;
        initRenderData();
    };

    /// <summary>
    /// Renders a 2D image, overlaid on top of the main renderered scene.
    /// </summary>
    void DrawSprite( float screenWidth, float sreenHeight, glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 colour = glm::vec3(1.0f), Texture* texture = nullptr) {
        // To-Do : Turn into 2D Transform Component
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position, 0.0f));
        model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
        model = glm::scale(model, glm::vec3(size, 1.0f));

        #pragma region Render Core

        _projectionMatrix = glm::ortho(0.0f, screenWidth, sreenHeight, 0.0f, -1.0f, 1.0f);

        _shader.setMat4("projection", _projectionMatrix);
        _shader.setMat4("model", model);

        // To-Do : Replace with Model.
        #pragma region Model
        _shader.setVec3("spriteColor", colour);
        _shader.useProgram();
        
        glActiveTexture(GL_TEXTURE0);   
        texture->Bind();
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        #pragma endregion

        #pragma endregion

    };

private:

    Shader _shader; // To-Do : Move out of class.
    glm::mat4 _projectionMatrix = glm::mat4(1.0f);

    // To-Do : Replace with Model object.
    #pragma region Model

    unsigned int quadVAO; 
    unsigned int VBO, VAO;

    void initRenderData() {
        // TO-DO: Replace with VAO and VBO Classes.
        float vertices[] = {
            // pos      // tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);


    };
    #pragma endregion

};

#endif

