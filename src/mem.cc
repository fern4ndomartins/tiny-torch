#include "../include/mem.h"
#include <cstdint>
#include <stdexcept>
#include <vulkan/vulkan_core.h>

void createBuffer(VkDevice device, VkBuffer *storageBuffer, uint64_t size, VkPhysicalDevice physicalDevice) {
    VkBufferCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    createInfo.size = size;
    createInfo.usage = VK_BUFFER_USAGE_2_STORAGE_BUFFER_BIT;
    createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(device, &createInfo, nullptr, storageBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create buffer\n");
    }

    VkMemoryRequirements memReq;
    vkGetBufferMemoryRequirements(device, *storageBuffer, &memReq);
    
    VkPhysicalDeviceMemoryProperties memPro;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memPro);
    uint32_t typeFilter;
    uint32_t x;
    for (uint32_t i = 0; i < memPro.memoryTypeCount; i++) {
        if (typeFilter & (1 << i) && (memPro.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) == (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)) {
            x = i;
            break;
        } else {
            throw std::runtime_error("failed to find suitable memory type!");
        }
    } 


}    