//
//  Utils.cpp
//  OpenGL
//
//  Created by guomiao on 2023/5/24.
//

#include "Utils.hpp"
#include <fstream>
#include "DebugShader.hpp"

extern void PrintShaderLog(GLuint shader);
extern void CheckOpenGLError();
extern void PrintProgram(int Program);

string Utils::ReadShaderSource(const char* filePath)
{
    string content;
    ifstream fileStream(filePath, ios::in);

    string line = "";
    while (!fileStream.eof()) {
        getline(fileStream, line);
        content.append(line + "\n");
    }

    cout << line << endl;
    fileStream.close();
    return content;
}

GLuint Utils::CreateVertexShader(const char* shaderSrc, GLenum type)
{
    GLint Compiled;
    
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSrc, NULL);
    glCompileShader(shader);
    CheckOpenGLError();
    glGetShaderiv(shader, GL_COMPILE_STATUS, &Compiled);
    if(Compiled != 1)
    {
        cout << shaderSrc << " compilation failed" << endl;
        PrintShaderLog(shader);
    }
    
    return shader;
}

GLuint Utils::CreateShaderProgram(const char* vshaderfile, const char* fshaderfile)
{
    GLint linked;
    
    string vertShaderStr = ReadShaderSource(vshaderfile);
    string fragShaderStr = ReadShaderSource(fshaderfile);

    const char* vertShaderSrc = vertShaderStr.c_str();
    const char* fragShaderSrc = fragShaderStr.c_str();
    
    GLuint vShader = CreateVertexShader(vertShaderSrc, GL_VERTEX_SHADER);
    
    GLuint fShader = CreateVertexShader(fragShaderSrc, GL_FRAGMENT_SHADER);

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);
    CheckOpenGLError();
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if(linked != 1)
    {
        cout << "CreateShaderProgram() linking faild" << endl;
        PrintProgram(vfProgram);
    }
    
    return vfProgram;
}
