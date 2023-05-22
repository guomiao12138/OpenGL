#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "DebugShader.hpp"
#include <string>
#include <fstream>

using namespace::std;
extern void PrintShaderLog(GLuint shader);
extern void CheckOpenGLError();
extern void PrintProgram(int Program);

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

float x = 0.0f; //三角形X轴位置
float inc = 0.01f; //移动三角形的偏移量

string ReadShaderSource(const char* filePath)
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

GLuint createShaderProgram(){
    
    GLint vertCompiled;
    GLint fragCompiled;
    GLint linked;
    
    string vertShaderStr = ReadShaderSource("/Users/guomiao/Documents/OpenGL/OpenGL/OpenGL/vertShader.glsl");
    string fragShaderStr = ReadShaderSource("/Users/guomiao/Documents/OpenGL/OpenGL/OpenGL/fragShader.glsl");

    const char* vertShaderSrc = vertShaderStr.c_str();
    const char* fragShaderSrc = fragShaderStr.c_str();
    
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vShader);
    CheckOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
    if(vertCompiled != 1)
    {
        cout << "vertex compilation failed" << endl;
        PrintShaderLog(vShader);
    }
    
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fShader);
    CheckOpenGLError();
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
    if(fragCompiled != 1)
    {
        cout << "fragment compilation failed" << endl;
        PrintShaderLog(fShader);
    }

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);
    CheckOpenGLError();
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if(linked != 1)
    {
        cout << "linking faild" << endl;
        PrintProgram(vfProgram);
    }
    
    return vfProgram;
}

void init(GLFWwindow* window)
{
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void display(GLFWwindow* window, double currentTime)
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(renderingProgram);
    
    x += inc;
    if(x > 1.0f)
    {
        inc = -0.01f;
    }
    if(x < -1.0f)
    {
        inc = 0.01f;
    }
    
    GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset");
    glUniform1f(offsetLoc, x);
    
    
    glPointSize(30.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    

}


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(600, 600, "guomiao", NULL, NULL);

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    init(window);

    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());


        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);
}
