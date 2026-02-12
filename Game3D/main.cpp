#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

// Load shader file
std::string loadFile(const char* path)
{
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

// Compile shader
GLuint compileShader(const char* path, GLenum type)
{
    std::string src = loadFile(path);
    const char* code = src.c_str();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    return shader;
}

// Create shader program
GLuint createProgram()
{
    GLuint vs = compileShader("shader.vert", GL_VERTEX_SHADER);
    GLuint fs = compileShader("shader.frag", GL_FRAGMENT_SHADER);

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main()
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    GLFWwindow* window =
        glfwCreateWindow(1280, 720, "RTX 3D Game", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    // Init GLAD
    gladLoadGL();

    glEnable(GL_DEPTH_TEST);

    // Cube vertices
    float vertices[] = {
        // pos
        -0.5f,-0.5f,-0.5f,
         0.5f,-0.5f,-0.5f,
         0.5f, 0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f,

        -0.5f,-0.5f, 0.5f,
         0.5f,-0.5f, 0.5f,
         0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
    };

    unsigned int indices[] = {
        0,1,2,2,3,0,
        4,5,6,6,7,4,
        0,4,7,7,3,0,
        1,5,6,6,2,1,
        3,2,6,6,7,3,
        0,1,5,5,4,0
    };

    GLuint VAO,VBO,EBO;

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(vertices),vertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,
        GL_FALSE,3*sizeof(float),(void*)0);

    glEnableVertexAttribArray(0);

    GLuint shader = createProgram();

    // Main loop
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.05f,0.05f,0.1f,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);

        // Matrices
        glm::mat4 model =
            glm::rotate(glm::mat4(1.0f),
            (float)glfwGetTime(),
            glm::vec3(0,1,0));

        glm::mat4 view =
            glm::translate(glm::mat4(1),
            glm::vec3(0,0,-3));

        glm::mat4 proj =
            glm::perspective(glm::radians(60.0f),
            1280.0f/720.0f,
            0.1f,100.0f);

        GLuint loc;

        loc = glGetUniformLocation(shader,"model");
        glUniformMatrix4fv(loc,1,0,&model[0][0]);

        loc = glGetUniformLocation(shader,"view");
        glUniformMatrix4fv(loc,1,0,&view[0][0]);

        loc = glGetUniformLocation(shader,"proj");
        glUniformMatrix4fv(loc,1,0,&proj[0][0]);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
