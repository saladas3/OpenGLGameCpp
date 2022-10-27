//
// Created by lucai on 10/15/2022.
//

#include "MainWindow.h"
#include "../MeshMgr/Mesh.h"
#include "../MeshMgr/Model.h"

// (NOTE) Always declare vertices (coordinates) counterclockwise, so we don't draw back-facing shapes
Vertex vertices[] = {
        //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
        Vertex{glm::vec3(-1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
               glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
               glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
               glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
               glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
};

Vertex lightVertices[] = {
        Vertex{glm::vec3(-0.1f, -0.1f, 0.1f)},
        Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, -0.1f, 0.1f)},
        Vertex{glm::vec3(-0.1f, 0.1f, 0.1f)},
        Vertex{glm::vec3(-0.1f, 0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, 0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, 0.1f, 0.1f)}
};

GLuint lightIndices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 4, 7,
        0, 7, 3,
        3, 7, 6,
        3, 6, 2,
        2, 6, 5,
        2, 5, 1,
        1, 5, 4,
        1, 4, 0,
        4, 5, 6,
        4, 6, 7
};

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
}

MainWindow::~MainWindow() {
    if (window) glfwDestroyWindow(window);
    glfwTerminate();
}

void MainWindow::broadcast() {
    // Generates Shader object using shaders default.vert and default.frag
    Shader shaderProgram("../Resources/Shaders/shader.vert", "../Resources/Shaders/shader.frag");

    // Shader used to outline 3D models
    //Shader outliningProgram("../Resources/Shaders/outlining.vert", "../Resources/Shaders/outlining.frag");

    // Take care of all the light related things
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    //lightModel = glm::translate(lightModel, lightPos);

    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    // Enable the Depth Buffer -> to render pixels correctly to get the perspective of depth
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS); // something with depth - see docs
    //glEnable(GL_STENCIL_TEST);
    //glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    // Enable FACE culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);

    // Disable Vsync? recommended not to use this?
    //glfwSwapInterval(0);

    // Creates camera object
    Camera camera(windowWidth, windowHeight, glm::vec3(.0f, .0f, 2.0f));

    // Load in a model
    // Model model("../Resources/Models/boombox/boombox.gltf");
    Model model("../Resources/Models/map/scene.gltf");

    double prevTime = .0f, crnTime, timeDiff;
    unsigned int counter = 0;

    // A frame is one loop in the main while loop
    while (!glfwWindowShouldClose(window)) {
        crnTime = glfwGetTime();
        timeDiff = crnTime - prevTime;
        counter++;
        if (timeDiff >= 1.0f / 30.0f) {
            std::string FPS = std::to_string((1.0f / timeDiff) * counter);
            std::string ms = std::to_string((timeDiff / counter) * 1000);
            std::string newTitle = "FPS test - " + FPS + " FPS / " + ms + " ms"; // NOLINT(performance-inefficient-string-concatenation)
            glfwSetWindowTitle(window, newTitle.c_str());
            prevTime = crnTime;
            counter = 0;
        }

        // Init viewport (the area we are going to draw in)
        glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);
        glViewport(0, 0, viewportWidth, viewportHeight);

        // Solid color background
        glClearColor(.5f, .1f, .20f, 1.0f);
        // (NOTE) glClear and glfwSwapBuffers should be in the while loop to render next scenes?
        // Clear the screen. It can cause flickering, so it's there nonetheless.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Handles camera inputs
        camera.Inputs(window); // this is moved in the if statement for FPS so that responsiveness of inputs don't vary with the FPS
        // Updates and exports the camera matrix to the Vertex Shader
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        // Draw a model
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
        model.Draw(shaderProgram, camera);

        //glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        //glStencilMask(0x00);
        //glDisable(GL_DEPTH_TEST);
        //outliningProgram.Activate();
        //glUniform1f(glGetUniformLocation(outliningProgram.ID, "outlining"), 0.08f);
        //model.Draw(outliningProgram, camera);

        //glStencilMask(0xFF);
        //glStencilFunc(GL_ALWAYS, 0, 0xFF);
        //glEnable(GL_DEPTH_TEST);

        // To draw triangles (chosen primitive), number of indices to draw, data type of indices, index of indices
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, nullptr);
        // Swap buffers the back buffer with the front buffer
        //  The front buffer holds the rendered frame while the next frame is loaded on the back buffer
        glfwSwapBuffers(window);
        // Ask for events (GLFW events) (mouse & keyboard inputs)
        glfwPollEvents();
    }

    // Cleanup
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
