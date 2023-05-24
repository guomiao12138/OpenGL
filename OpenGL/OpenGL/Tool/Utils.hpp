//
//  Utils.hpp
//  OpenGL
//
//  Created by guomiao on 2023/5/24.
//
#pragma once

#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>
#include <glad/glad.h>
#include <string>
#include <iostream>
using namespace::std;

class Utils
{
public:
    static string ReadShaderSource(const char* filePath);
    
    ///     /// - Parameters:
    ///   - vshaderfile: 顶点着色器文件
    ///   - fshaderfile: 片段着色器文件
    static GLuint CreateShaderProgram(const char* vshaderfile, const char* fshaderfile);
    
    static GLuint CreateVertexShader(const char* vshader, GLenum type);
    
//    static GLuint CreateShaderProgram(const char* vshader, const char* g, const char* fshader);
};


#endif /* Utils_hpp */
