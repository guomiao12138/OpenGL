#include <glad/glad.h>
#include <GLFW/glfw3.h>
 
#include <iostream>


//#define numVAOs 1
//
//GLuint renderingProgram;
//GLuint vao[numVAOs];
//
//GLuint createShaderProgram()
//{
//    const char* vshaderSource =
//        "#version 410 \n"
//        "void main(void) \n"
//        "{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";
//
//    const char* fshaderSource =
//        "#version 410 \n"
//        "out vec4 color; \n"
//        "void main(void) \n"
//        "{ color = vec4(0.0, 0.0, 1.0, 1.0); }";
//
//    GLuint vShader = glCreateShader(GL_VERTEX_SHADER); // 创建类型 GL_VERTEX_SHADER 的着色器，返回引用它的序号
//    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER); // 创建类型 GL_FRAGMENT_SHADER 的着色器，返回引用它的序号
//
//    glShaderSource(vShader, 1, &vshaderSource, NULL); // 将GLSL代码从字符串载入空着色器对象中
//    glShaderSource(fShader, 1, &fshaderSource, NULL);
//    glCompileShader(vShader); // 编译各着色器
//    glCompileShader(fShader);
//
//    GLuint vfProgram = glCreateProgram(); // 创建程序对象，并储存指向它的整数ID
//    glAttachShader(vfProgram, vShader); // 将着色器加入程序对象
//    glAttachShader(vfProgram, fShader);
//    glLinkProgram(vfProgram); // 让GLSL编译器确保它们的兼容性
//
//    return vfProgram;
//}

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

GLuint createShaderProgram(){
    const char* vshaderSource =
        "#version 410 \n"
        "void main(void) \n"
        "{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";

    const char* fshaderSource =
        "#version 410 \n"
        "out vec4 color; \n"
        "void main(void) \n"
        "{ color = vec4(0.0, 0.0, 1.0, 1.0); }";

    
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);
    glCompileShader(vShader);
    glCompileShader(fShader);

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);


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
    glUseProgram(renderingProgram);
    glPointSize(100.0f);
    glDrawArrays(GL_POINTS, 0, 1);

//    glClear(GL_COLOR_BUFFER_BIT);
//    glClearColor(1.0, 0.0,0.0,1.0);
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
//    return 0;
}
