//
//  DebugShader.cpp
//  OpenGL
//
//  Created by guomiao on 2023/5/21.
//

#include "DebugShader.hpp"
#include <glad/glad.h>
#include <iostream>
using namespace::std;

void PrintShaderLog(GLuint shader)
{
    int len = 0;
    int chWrittn = 0;
    char* log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = (char*)malloc(len);
        glGetShaderInfoLog(shader, len, &chWrittn, log);
        cout << "Shader Info Log : " << log << endl;
        free(log);
    }
}

bool CheckOpenGLError()
{
    bool foundError = false;
    int glError = glGetError();
    while (glError != GL_NO_ERROR) {
        cout << "glError : " << glError << endl;
        foundError = true;
        glError = glGetError();
    }
    
    return foundError;
}

void PrintProgram(int Program)
{
    int len = 0;
    int chWrittn = 0;
    char* log;
    glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &len);
    if(len > 0)
    {
        log = (char*)malloc(len);
        glGetProgramInfoLog(Program, len, &chWrittn, log);
        cout << "Program Info Log : " << log << endl;
        free(log);
    }
}
