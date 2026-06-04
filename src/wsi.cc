#include "../include/wsi.h"
#include "../include/wsi.h"

const int WIDTH = 900;
const int HEIGHT = 600;

void initWindow(GLFWwindow*& window) {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr); 
}

void windowLoop(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {  

        glfwPollEvents();
    }
}