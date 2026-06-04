#include "../include/device.h"
#include <cstdint>
#include <vector>
#include <vulkan/vulkan_core.h>

void createDevice(VkInstance *instance, VkDevice *device, ComputeQueue *queue) {
    std::vector<VkPhysicalDevice> devices;
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(*instance, &deviceCount, nullptr);
    devices.resize(deviceCount);
    vkEnumeratePhysicalDevices(*instance, &deviceCount, devices.data());
    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    } else {
        printf("number of physical devices: %u\n", deviceCount);
    }
    VkPhysicalDevice physicalDevice = devices[0];


    uint32_t queueFamilyCount;
    std::vector<VkQueueFamilyProperties> queueFamilyProperties;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
    queueFamilyProperties.resize(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilyProperties.data());
    int p = 0;
    int computeQueueIndex = 0;
    
    for (const auto &queueFamily : queueFamilyProperties) {
        if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT) {
            computeQueueIndex = p;
            break;
        }
        p++;
    }
    queue->index = computeQueueIndex;
    float priority = 1.0f;
    VkDeviceQueueCreateInfo queueInfo = {};
        queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueInfo.queueFamilyIndex = (uint32_t)computeQueueIndex;
        queueInfo.queueCount = 1;
        queueInfo.pQueuePriorities = &priority;


    VkDeviceCreateInfo deviceCreateInfo = {};
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.queueCreateInfoCount = 1;
        deviceCreateInfo.pQueueCreateInfos = &queueInfo;
        deviceCreateInfo.enabledLayerCount = 0;
        deviceCreateInfo.enabledExtensionCount = 0;
    
    if (vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    } else {
        printf("compute logical device create successfully\n");
    }

    vkGetDeviceQueue(*device, (uint32_t)computeQueueIndex, 0, &queue->queue);
}