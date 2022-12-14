//
// Created by lucai on 10/15/2022.
//

#ifndef OPENGLGAMECPP_MAINWINDOW_H
#define OPENGLGAMECPP_MAINWINDOW_H

#include <iostream>
#include <string>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class MainWindow {
    GLFWwindow *window = nullptr; // (In the accompanying source code, this variable is global for simplicity)
    int windowWidth = 1024, windowHeight = 768;
    int viewportWidth = 0, viewportHeight = 0;
    const char *windowName = "Test Window";
public:
    MainWindow();

    void broadcast();

    static void handleKeyInput(GLFWwindow *_window, int key, int status, int action, int mods);

    ~MainWindow();
};

#endif //OPENGLGAMECPP_MAINWINDOW_H
