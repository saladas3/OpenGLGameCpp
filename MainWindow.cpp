//
// Created by lucai on 10/15/2022.
//

#include <fstream>
#include <sstream>
#include "MainWindow.h"

std::string readFile(const std::string &fileLoc) {
    std::ifstream file;
    std::stringstream contents;

    file.open(fileLoc, std::ios::in);

    if (!file.fail()) {
        contents << file.rdbuf();
    }

    return contents.str();
}

GLuint createAndCompileShader(const std::string &fileLoc, GLuint shaderType) {
    const std::string shaderSource = readFile(fileLoc);
    const char *cShader = shaderSource.c_str();

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &cShader, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char ifLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, ifLog);
        std::cerr << "Shader error: " << ifLog << std::endl;
    }

    return shader;
}

GLuint createAndLinkProgram() {
    GLuint vertexShader = createAndCompileShader("../Shaders/shader.vert", GL_VERTEX_SHADER);
    GLuint fragmentShader = createAndCompileShader("../Shaders/shader.frag", GL_FRAGMENT_SHADER);
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char ifLog[512];
        glGetProgramInfoLog(program, 512, nullptr, ifLog);
        std::cerr << "GL program link error: " << ifLog << std::endl;
    }

    return program;
}

// (NOTE) Always declare vertices (coordinates) counterclockwise, so we don't draw back-facing shapes
const float testVertices[] = {
        -.5f, -.5f, .0f, // bottom left of triangle (point)
        .5f, -.5f, .0f, // bottom right of triangle
        .0f, .5f, .0f // top of triangle
};

// (NOTE) Steps for the shaders:
//  1. Read shader files
//  2. Store and compile shaders
//  3. Store and link the shaders
//  4. Use the program created from the shaders

MainWindow::MainWindow() {
    glewExperimental = GL_TRUE; // Needed in core profile
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make macOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(1024, 768, windowName, nullptr, nullptr);
    if (window == nullptr) {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
    }

    // We are going to draw on this window -> may need to add in render cycle
    glfwMakeContextCurrent(window); // Initialize GLEW
    glfwSetKeyCallback(window, handleKeyInput);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
    }
}

MainWindow::~MainWindow() {
    if (window) glfwDestroyWindow(window);
    glfwTerminate();
}

void MainWindow::broadcast() {
    GLuint shaderProgram = createAndLinkProgram();
    GLuint VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(testVertices), testVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Solid color background
    glClearColor(.3f, .3f, .4f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        // Ask for events (mouse & keyboard inputs)
        glfwPollEvents();

        // Clear the screen. It can cause flickering, so it's there nonetheless.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Init viewport (the area we are going to draw in, I think)
        glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);
        glViewport(0, 0, viewportWidth, viewportHeight);

        // Apply shaders to the scene (draw)
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}

void MainWindow::handleKeyInput(GLFWwindow *_window, int key, int status, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(_window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        glClearColor(.5f, .2f, .1f, 1.0f);
    }
    if (key == GLFW_KEY_R && action == GLFW_RELEASE) {
        glClearColor(.3f, .3f, .4f, 1.0f);
    }
}
