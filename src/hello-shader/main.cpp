#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <shader.h>

using namespace std;

GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // 左下
    0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // 右下
    0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f,   // 右上
    -0.5f, 0.5f,  0.0f, 1.0f, 0.0f, 1.0f,   // 左上
};

GLuint indices[] = {
    0, 1, 2,
    0, 2, 3
};

// 顶点着色器程序
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main() {
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
}
)";

// 片段着色器程序
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

in vec3 ourColor;

void main() {
    FragColor = vec4(ourColor, 1.0f);
}
)";

void handleInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Playground", nullptr, nullptr);
    if (!window)
    {
        cout << "Create GLFW window fail" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Create glad Loader fail" << endl;
        glfwTerminate();
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        });

    Shader shader = Shader::fromSource(vertexShaderSource, fragmentShaderSource);

    GLuint VAO;
    glCreateVertexArrays(1, &VAO);

    GLuint VBO;
    glCreateBuffers(1, &VBO);

    GLuint EBO;
    glCreateBuffers(1, &EBO);

    // 绑定顶点数组对象
    glBindVertexArray(VAO);
    // 把顶点数组复制到顶点缓冲中，供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 赋值索引数组到索引缓冲中，供OpenGL使用
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 使用上一步绑定的VBO中的数据，设定顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    while (!glfwWindowShouldClose(window))
    {
        handleInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        GLfloat timeValue = glfwGetTime();
        GLfloat greenColor = sin(timeValue) / 2.0f + 0.5f;
        int ourColorLocation = glGetUniformLocation(shader.getProgramId(), "ourColor");
        glUniform4f(ourColorLocation, 1.0f, greenColor, 1.0f, 1.0f);

        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}