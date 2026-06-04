#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#include <cstdio>
#include <vector>
#include <iostream>


typedef struct  {
    VkQueue queue;
    uint32_t index;
} ComputeQueue;


void createDevice(VkInstance *instance, VkDevice *device, ComputeQueue *queue);