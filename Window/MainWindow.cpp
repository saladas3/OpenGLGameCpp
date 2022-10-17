//
// Created by lucai on 10/15/2022.
//

#include "MainWindow.h"
#include "../TextureMgr/Texture.h"
#include "../RenderSystem/VAO.h"
#include "../RenderSystem/EBO.h"
#include "../stb/stb_image.h"
#include "../Camera/Camera.h"

// (NOTE) Always declare vertices (coordinates) counterclockwise, so we don't draw back-facing shapes
GLfloat vertices[] = {
        //     COORDINATES              /           COLORS            /      TexCoord      //
        -0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
        -0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f,
        0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f,
        0.0f, 0.8f, 0.0f, 0.92f, 0.86f, 0.76f, 2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
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
    window = glfwCreateWindow(windowWidth, windowHeight, windowName, nullptr, nullptr);
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
    VBO VBO1(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));

    // Links VBO to VAO
    VAO::LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *) nullptr);
    VAO::LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    VAO::LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO::Unbind();
    VBO::Unbind();
    EBO::Unbind();

    // Texture
    Texture popCat("../Resources/Textures/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture::texUnit(shaderProgram, "tex0", 0);
    popCat.Unbind();

    // Enable the Depth Buffer -> to render pixels correctly to get the perspective of depth
    glEnable(GL_DEPTH_TEST);

    Camera camera(windowWidth, windowHeight, glm::vec3(.0f, .0f, 2.0f));

    while (!glfwWindowShouldClose(window)) {
        // Solid color background
        glClearColor(.07f, .13f, .17f, 1.0f);
        // (NOTE) glClear and glfwSwapBuffers should be in the while loop to render next scenes?
        // Clear the screen. It can cause flickering, so it's there nonetheless.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use
        shaderProgram.Activate();

        camera.Inputs(window);
        camera.Matrix(45.0f, .1f, 100.0f, shaderProgram, "camMatrix");

        // Binds texture so that is appears in rendering
        popCat.Bind();
        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();
        // To draw triangles (chosen primitive), number of indices to draw, data type of indices, index of indices
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, nullptr);

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
    popCat.Delete();
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
