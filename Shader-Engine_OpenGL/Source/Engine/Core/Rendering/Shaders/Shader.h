#pragma once
#ifndef SHADER_H
#define SHADER_H


#include <glad.h> // include glad to get all the required OpenGL headers
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader() {};
    Shader(const char* vertexPath, const char* fragmentPath);

    // use/activate the shader
    void useProgram();
    void StopProgram();

    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, float x, float y, float z)const;
    void setVec3(const std::string& name, const glm::vec3 vec3)const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;



};

#endif
