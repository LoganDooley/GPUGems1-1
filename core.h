#pragma once

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#include <iostream>
#include <memory>

class Core
{
public:
    Core();
    ~Core();
    int update();
    int draw();
    void keyEvent(int key, int action);
    void mousePosEvent(double xpos, double ypos);
    void mouseButtonEvent(int button, int action);
    void scrollEvent(double distance);
    void windowResizeEvent(int width, int height);
    void framebufferResizeEvent(int width, int height);
};
