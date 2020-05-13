//
//  shader.cpp
//
//  Created by Lax Zhang on 2019/2/23.
//  Copyright © 2019 Lax Zhang. All rights reserved.
//

#include "shader.hpp"

using namespace std;


Shader::Shader(void){
    cout << "shader is construct.." << endl;
}

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath){
    string vertexCode;
    string fragmentCode;
    ifstream vShaderFile;
    ifstream fShaderFile;
    
    vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // 关闭文件
        vShaderFile.close();
        fShaderFile.close();
        // 将流存入字符串中
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (ifstream::failure e) {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
    }
    // 返回着色器的源码
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    unsigned int vertex, fragment;
    int success;
    char infoLog[255];
    
    // 顶点着色器
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // 打印编译错误
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }
    
    // 片段着色器
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        cout <<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }
    
    // 着色器程序
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << endl;
    }
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use(){
    glUseProgram(ID);
}

void Shader::setBool1(const std::string &name, bool value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt1(const std::string &name, int value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat1(const std::string &name, float value) const{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat3(const std::string &name, float value1, float value2, float value3) const{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3);
}

void Shader::setFloat4(const std::string &name, float value1, float value2, float value3, float value4) const{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3, value4);
}

void Shader::setMat2(const std::string &name, const glm::mat4 &mat) const{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat4 &mat) const{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &vec) const{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &vec[0]);
}

void Shader::setVec3(const std::string &name, const float x, const float y, const float z) const{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setDirectionLight(const glm::vec3 &direction, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular){
    setVec3("dirLight.direction", direction);
    setVec3("dirLight.ambient", ambient);
    setVec3("dirLight.diffuse", diffuse);
    setVec3("dirLight.specular", specular);
}

void Shader::setSpotLight(const glm::vec3 &front, const glm::vec3 &pos, const float &cutoff, const float &outerCutoff, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular){
    setVec3("spotLight.direction", front);
    setVec3("spotLight.position", pos);
    setFloat1("spotLight.cutoff", cutoff);
    setFloat1("spotLight.outerCutoff", outerCutoff);
    setVec3("spotLight.ambient", ambient);
    setVec3("spotLight.diffuse", diffuse);
    setVec3("spotLight.specular", specular);
}

void Shader::setPointLight(glm::vec3 *pos, const float &constant, const float &linear, const float &quadratic, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, const unsigned int size){
    
    for (int i = 0; i < size; i++) {
        setVec3("pointLight[" + to_string(i) + "].position", pos[i]);
        setVec3("pointLight[" + to_string(i) + "].ambient", ambient);
        setVec3("pointLight[" + to_string(i) + "].diffuse", diffuse);
        setVec3("pointLight[" + to_string(i) + "].specular", specular);
        setFloat1("pointLight[" + to_string(i) + "].constant", constant);
        setFloat1("pointLight[" + to_string(i) + "].linear", linear);
        setFloat1("pointLight[" + to_string(i) + "].quadratic", quadratic);
    }
    
}
