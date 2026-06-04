#include "../include/main.h"
#include "../include/device.h"
#include "../include/instance.h"
#include "../include/wsi.h"
#include "../include/pipeline.h"
#include <vulkan/vulkan_core.h>
#include "../include/cmb.h"
#include <pybind11/pybind11.h>

int main() {
    GLFWwindow* window = nullptr;
    initWindow(window);

    VkInstance instance;
    createInstance(&instance);

    VkDevice device;

    ComputeQueue queue = {};

    createDevice(&instance, &device, &queue);

    VkPipeline pipeline;

    createPipeline(&pipeline, &device); // <- should actually also pass compute shader file name here ?      

    VkCommandBuffer commandBuffer;

    allocateCommandBuffer(&device, &commandBuffer, queue.index);

    recordCommandBuffer(&commandBuffer, &pipeline);

    VkSubmitInfo submitInfo = {};
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;
    
    submitInfo.signalSemaphoreCount = 0;
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    printf("special things\n");
    VkResult v = vkQueueSubmit(queue.queue, 1, &submitInfo, nullptr);
    // mainLoop(window);

    // glfwDestroyWindow(window);
    // glfwTerminate();
}



PYBIND11_MODULE(modd, m) {
    m.doc() = "pybind11 example module";

    m.def("spec", &main, "A special function");

}