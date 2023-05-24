#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Tool/Utils.hpp"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
using namespace::std;

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

float x = 0.0f; //三角形X轴位置
float inc = 0.01f; //移动三角形的偏移量
float temp = 1.0f;
GLfloat sizes[] = {};
GLfloat pointSize = 30.0f;

const char* vertexShader = "/Users/guomiao/Documents/OpenGL/OpenGL/OpenGL/vertShader.glsl";
const char* fragmentShader = "/Users/guomiao/Documents/OpenGL/OpenGL/OpenGL/fragShader.glsl";

void init(GLFWwindow* window)
{
    renderingProgram =  Utils::CreateShaderProgram(vertexShader, fragmentShader);
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
    
    
    pointSize += temp;

    if(pointSize <= 20.0f)
    {
        temp = 1.0f;
    }
    if(pointSize >= 40.0f)
    {
        temp = -1.0f;
    }
    
    glPointSize(pointSize);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
//    glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
//
//    cout << sizes[1] << endl;
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
