#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

unsigned int window_width = 800;
unsigned int window_height = 600;
const char* window_name = "OpenGL testApp";
float* back_color = new float[4]{0.2f, 0.3f, 0.3f, 1.0f};

float vertices[] =
{
    -1.0f, -0.5f, 0.0f,
    -0.5f,  0.0f, 0.0f,
     0.0f, -0.5f, 0.0f
};

float vertices1[] =
{
     0.0f,  0.5f, 0.0f,
     0.5f,  0.0f, 0.0f,
     1.0f,  0.5f, 0.0f
};

unsigned int indices[] =
{
    0, 1, 2
};

const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
"}\n";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.1f, 1.0f, 0.2f, 1.0f);\n"
"}\n";

const char* fragmentShaderSource2 =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.1f, 1.0f, 1.0f);\n"
"}\n";

int success;
char infoLog[512];

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // VERTEX SHADER
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog 
                  << std::endl;
    }
    // FRAGMENT SHADER
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog
                  << std::endl;
    }
    // FRAGMENT SHADER 2
    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);
    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader2, sizeof(infoLog), NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog
                  << std::endl;
    }
    // SHADER PROGRAM
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog
                  << std::endl;
    }
    // SHADER PROGRAM 2
    unsigned int shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);
    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram2, sizeof(infoLog), NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog
                  << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);
    
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(back_color[0], back_color[1], back_color[2], back_color[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgram2);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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