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
 * @brief init GLFW
 *
 * @param resizable window resizable status
 **/
void init_glfw(bool resizable = false);

/**
 * @brief destroy window and terminate GLFW
 *
 * @param window pointer of window to destroy
 **/
void terminate_window(GLFWwindow* window);

/**
 * @brief Poll events if GLFW Window is not closed.
 */
void poll_events_if_window_open(GLFWwindow* window);

/**
 * @brief Initialize a Window
 *
 * @param width window width
 * @param height window height
 * @param title window title
 **/
void initialize_window(int width, int height, const char* title);
