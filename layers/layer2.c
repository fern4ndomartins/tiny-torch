#include <vulkan/vk_layer.h>
#include <vulkan/vulkan.h>
#include <string.h>
#include <vulkan/vulkan_core.h>
#include <stdio.h>

#define PUBLIC __attribute__((visibility("default")))

static VkResult myFunction(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance) {
    printf("Hello From Layer 2!!!\n");

    VkLayerInstanceCreateInfo *chain_info = NULL;



    

    return VK_SUCCESS;
}

static void (*get_instance_proc_addr(VkInstance instance, const char *name))()
{
   if (strcmp(name, "vkGetInstanceProcAddr") == 0)
      return (void (*)())get_instance_proc_addr;
   if (strcmp(name, "vkCreateInstance") == 0)
      return (void (*)())myFunction;
   return NULL;
}

PUBLIC VkResult vkNegotiateLoaderLayerInterfaceVersion(VkNegotiateLayerInterface *pVersionStruct)
{
   if (pVersionStruct->loaderLayerInterfaceVersion < 2)
      return VK_ERROR_INITIALIZATION_FAILED;
   pVersionStruct->loaderLayerInterfaceVersion = 2;

   pVersionStruct->pfnGetInstanceProcAddr = get_instance_proc_addr;

   return VK_SUCCESS;
}