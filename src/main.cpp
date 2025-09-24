#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

unsigned int window_width = 800;
unsigned int window_height = 600;
const char* window_name = "OpenGL testApp";
float* back_color = new float[4]{0.2f, 0.3f, 0.3f, 1.0f};

const char* vertexShaderFilePath = "/home/anton/testApp/src/vertexShader.txt";
const char* fragmentShaderFilePath = "/home/anton/testApp/src/fragmentShader.txt";

float vertices[] =
{
     0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f
};

unsigned int indices[] =
{
    0, 1, 2
};

//------------------------------------------------------------------------------
int main()
{
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, 
                                          window_name, NULL, NULL);
    if(window == NULL)
    {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        delete[] back_color;
        back_color = nullptr;
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        delete[] back_color;
        back_color = nullptr;
        return -1;
    }

    // GL BUFFER MANAGEMENT
    unsigned int VBOs[2], VAOs[2];
    unsigned int EBO;
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    Shader ourShader(vertexShaderFilePath, fragmentShaderFilePath);
    
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(back_color[0], back_color[1], back_color[2], back_color[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    delete[] back_color;
    back_color = nullptr;
    return 0;
}
//------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}