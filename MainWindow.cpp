//
// Created by lucai on 10/15/2022.
//

#include "MainWindow.h"

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
    // Solid color background
    glClearColor(.3f, .3f, .4f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        // Ask for events (mouse & keyboard inputs)
        glfwPollEvents();
        // Clear the screen. It can cause flickering, so it's there nonetheless.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Swap buffers
        glfwSwapBuffers(window);

        // TODO: game :)
    }
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
