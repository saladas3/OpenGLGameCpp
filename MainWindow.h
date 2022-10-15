//
// Created by lucai on 10/15/2022.
//

#ifndef OPENGLGAMECPP_MAINWINDOW_H
#define OPENGLGAMECPP_MAINWINDOW_H

#include <iostream>
#include <string>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class MainWindow {
    GLFWwindow *window = nullptr; // (In the accompanying source code, this variable is global for simplicity)
    const char *windowName = "Test Window";
public:
    MainWindow();

    void broadcast();

    static void handleKeyInput(GLFWwindow *_window, int key, int status, int action, int mods);

    ~MainWindow();
};

#endif //OPENGLGAMECPP_MAINWINDOW_H
