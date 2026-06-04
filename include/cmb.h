#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

void createCommandBufferPool(VkDevice *device, VkCommandPool *commandPool, uint32_t queueIndex);
void recordCommandBuffer(VkCommandBuffer *commandBuffer, VkPipeline *pipeline);
void allocateCommandBuffer(VkDevice *device, VkCommandBuffer *commandBuffer, uint32_t queueIndex);
