//
// Created by air on 11/11/21.
//

#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <GL/glew.h>
#include <imgui.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <spdlog/spdlog.h>
#include "Shader.h"

class Camera{
public:
    // Stores the main vectors of the camera
    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 cameraMatrix = glm::mat4(1.0f);

    // Prevents the camera from jumping around when first clicking left click
    bool firstClick = true;

    // Stores the mainWindowWidth and mainWindowHeight of the window
    int width;
    int height;

    // Adjust the speed of the camera and it's sensitivity when looking around
    float speed = 0.01f;
    float sensitivity = 0.655f;

    // Camera constructor to set up initial values
    Camera(int width, int height, glm::vec3 position);

    // Updates the camera matrix to the Vertex Shader
    void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
    // Exports the camera matrix to a shader
    void Matrix(Shader& shader, const char* uniform);
    // Handles camera inputs
    void Inputs(GLFWwindow* window, ImVec2 glWindowPosition, ImVec2 glWindowSize);

    void reset();
    void scrollCallback();

    void resetView();

    void relevelView();
};
#endif
