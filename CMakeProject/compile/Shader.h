#pragma once
#include <glad/glad.h>; 
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <helpers/RootDir.h>
class Shader
{
public:
    // ����ID
	unsigned int ID;

    // ��������ȡ��������ɫ��
    Shader(const char* vertexPath, const char* fragmentPath) {
        const char* vertexShaderSource = load_shader(vertexPath);
        const char* fragmentShaderSource = load_shader(fragmentPath);
        unsigned int vertexShader, fragmentShader;

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        check_error(vertexShader, "VERTEX");

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        check_error(fragmentShader, "FRAGMENT");

        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);
        check_error(ID, "PROGRAM");

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    // ʹ��/�������
    void use() {
        glUseProgram(ID);
    }
    // uniform���ߺ���
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
private:
    auto load_shader(std::string filename) -> const char* {

        std::ifstream loader("shaders/" + filename);
        std::stringstream buffer;
        buffer << loader.rdbuf();
        return buffer.str().c_str();
    }
    auto check_error(GLuint shader, std::string type) -> void {
        GLint success;
        GLchar infoLog[512];
        auto error_str = "ERROR::SHADER_COMPILATION_ERROR::";

        if (type == "PROGRAM") {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            error_str = "ERROR::SHADER_LINK_ERROR::";
        }
        else glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << error_str << type << "\n" << infoLog << std::endl;
        }
    }
};