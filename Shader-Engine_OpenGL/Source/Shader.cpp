#include "Header/Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) 
{

#pragma region Read file paths.

    // Read file path.
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        // read file's contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // close file handlers
        vShaderFile.close();
        fShaderFile.close();

        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    // Error Handling.
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

#pragma endregion


#pragma region Compile & Link shaders

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];


    // Create Vertex Shader object and compile shader code.
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    // Error Handling.
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };


    // Create Fragment Shader object and compile shader code.
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    // Error Handling.
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    };


    // Create Shader Program object and, link in shader objects.
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    // Error Handling.
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }


    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);

#pragma endregion

}

void Shader::useProgram()
{
    glUseProgram(ID);
}
void Shader::StopProgram()
{
    glUseProgram(0);
}

#pragma region Uniform setters.

void Shader::setBool(const std::string& name, bool value) const
{
    glUseProgram(ID);
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    glUseProgram(0);
}
void Shader::setInt(const std::string& name, int value) const
{
    glUseProgram(ID);
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    glUseProgram(0);
}
void Shader::setFloat(const std::string& name, float value) const
{
    glUseProgram(ID);
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    glUseProgram(0);
}
void Shader :: setVec3(const std::string& name, float x, float y, float z) const
{
    glUseProgram(ID);
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    glUseProgram(0);
}


void Shader :: setMat4(const std::string& name, const glm::mat4& mat) const
{
    glUseProgram(ID);
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    glUseProgram(0);
}

#pragma endregion