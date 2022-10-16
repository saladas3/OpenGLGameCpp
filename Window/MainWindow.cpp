//
// Created by lucai on 10/15/2022.
//

#include "MainWindow.h"
#include "../ShaderMgr/Shader.h"
#include "../RenderSystem/VAO.h"
#include "../RenderSystem/EBO.h"

// (NOTE) Always declare vertices (coordinates) counterclockwise, so we don't draw back-facing shapes
GLfloat testVertices[] = { //             COORDINATES               /         COLORS           //
        -0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f, 0.8f, 0.3f, 0.02f, // Lower left corner
        0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f, 0.8f, 0.3f, 0.02f, // Lower right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 1.0f, 0.6f, 0.32f, // Upper corner
        -0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f, 0.9f, 0.45f, 0.17f, // Inner left
        0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f, 0.9f, 0.45f, 0.17f, // Inner right
        0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f, 0.8f, 0.3f, 0.02f  // Inner down
};

// Tells in what order to draw the vertices
GLuint indices[] = {
        0, 3, 5, // Lower left triangle
        3, 2, 4, // Lower right triangle
        5, 4, 1, // Upper triangle
};

// (NOTE) Steps for the shaders:
//  1. Read shader files
//  2. Store and compile shaders
//  3. Store and link the shaders
//  4. Use the program created from the shaders

MainWindow::MainWindow() {
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
        return;
    }

    // We are going to draw on this window -> may need to add in render cycle
    glfwMakeContextCurrent(window); // Initialize GLEW

    // Callback to a key handler for the window
    glfwSetKeyCallback(window, handleKeyInput);

    // Load GLAD to configure OpenGL
    gladLoadGL();

    // Init viewport (the area we are going to draw in, I think)
    glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);
    glViewport(0, 0, viewportWidth, viewportHeight);
}

MainWindow::~MainWindow() {
    if (window) glfwDestroyWindow(window);
    glfwTerminate();
}

void MainWindow::broadcast() {
    // Generates Shader object using shaders default.vert and default.frag
    Shader shaderProgram("../Resources/Shaders/shader.vert", "../Resources/Shaders/shader.frag");

    // Generates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(testVertices, sizeof(testVertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));

    // Links VBO to VAO
    VAO::LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *) nullptr);
    VAO::LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO::Unbind();
    VBO::Unbind();
    EBO::Unbind();

    GLint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    while (!glfwWindowShouldClose(window)) {
        // Solid color background
        glClearColor(.07f, .13f, .17f, 1.0f);
        // (NOTE) glClear and glfwSwapBuffers should be in the while loop to render next scenes?
        // Clear the screen. It can cause flickering, so it's there nonetheless.
        glClear(GL_COLOR_BUFFER_BIT);

        // Tell OpenGL which Shader Program we want to use
        shaderProgram.Activate();
        glUniform1f(uniID, .5f);
        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();
        // To draw triangles (chosen primitive), number of indices to draw, data type of indices, index of indices
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr);

        // Swap buffers the back buffer with the front buffer
        //  The front buffer holds the rendered frame while the next frame is loaded on the back buffer
        glfwSwapBuffers(window);
        // Ask for events (GLFW events) (mouse & keyboard inputs)
        glfwPollEvents();
    }

    // Cleanup
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
}

void MainWindow::handleKeyInput(GLFWwindow *_window, int key, int status, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(_window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        glClearColor(.5f, .2f, .1f, 1.0f);
    }
    if (key == GLFW_KEY_R && action == GLFW_RELEASE) {
        glClearColor(.07f, .13f, .17f, 1.0f);
    }
}
