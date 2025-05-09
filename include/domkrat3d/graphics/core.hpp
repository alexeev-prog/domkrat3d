/**
 * @file
 * @brief Physics utils for kinematics
 * @authors alxvdev
 */

#pragma once

#include "GLFW/glfw3.h"

/**
 * @brief Create GLFW Window
 *
 * @param width window width
 * @param height window height
 * @param title window title
 *
 * @return glfw window
 **/
auto create_window(int width, int height, const char* title) -> GLFWwindow*;

/**
 * @brief destroy window and terminate GLFW
 *
 * @param window pointer of window to destroy
 **/
void terminate_window(GLFWwindow* window);

/**
 * @brief Initialize a Window
 *
 * @param width window width
 * @param height window height
 * @param title window title
 **/
void initialize_window(int width, int height, const char* title);
