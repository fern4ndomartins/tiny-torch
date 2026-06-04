#include "../include/cmb.h"
#include <cstdint>
#include <vulkan/vulkan_core.h>
#include "../include/device.h"

void createCommandBufferPool(VkDevice *device, VkCommandPool *commandPool, uint32_t queueIndex) {
    VkCommandPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueIndex;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    vkCreateCommandPool(*device, &poolInfo, nullptr, commandPool);
}

void recordCommandBuffer(VkCommandBuffer *commandBuffer, VkPipeline *pipeline) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.flags = 0;
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.pInheritanceInfo = nullptr;
    
    if (vkBeginCommandBuffer(*commandBuffer, &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin command buffer");
    }
    vkCmdBindPipeline(*commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, *pipeline);
    vkCmdDispatch(*commandBuffer, 10, 10, 1);

    if (vkEndCommandBuffer(*commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }
}

void allocateCommandBuffer(VkDevice * device, VkCommandBuffer *commandBuffer, uint32_t queueIndex) {
    VkCommandPool commandPool;
    createCommandBufferPool(device, &commandPool, queueIndex);
    VkCommandBufferAllocateInfo allocateInfo{};
    allocateInfo.commandBufferCount = 1;
    allocateInfo.commandPool = commandPool;
    allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocateInfo.pNext = nullptr;

    if (vkAllocateCommandBuffers(*device, &allocateInfo, commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffer");
    }
    
}
