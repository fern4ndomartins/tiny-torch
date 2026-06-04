#include <vulkan/vk_layer.h>
#include <vulkan/vulkan.h>
#include <string.h>
#include <vulkan/vulkan_core.h>
#include <stdio.h>
#include <assert.h>

#define PUBLIC __attribute__((visibility("default")))


static VkResult myFunction(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance) {
   printf("Hello From Layer 1!!!\n");
   
   VkLayerInstanceCreateInfo *chain_info = NULL;
   
   const void *current = pCreateInfo->pNext;

   while (current) {

      const VkBaseInStructure *header = (VkBaseInStructure*)current;

      if (header->sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO) {
         const VkLayerInstanceCreateInfo *this_info = (VkLayerInstanceCreateInfo*)header;
         if (this_info->function==VK_LAYER_LINK_INFO) {
            printf("found layer struct?\n");
            chain_info = (VkLayerInstanceCreateInfo *)this_info;
            break;
         }

      }

      current = header->pNext;
   }

   assert(chain_info->u.pLayerInfo);
   PFN_vkGetInstanceProcAddr GetInstanceProcAddr =
      chain_info->u.pLayerInfo->pfnNextGetInstanceProcAddr;
   PFN_vkCreateInstance fpCreateInstance =
      (PFN_vkCreateInstance)GetInstanceProcAddr(NULL, "vkCreateInstance");
   if (fpCreateInstance == NULL) {
      return VK_ERROR_INITIALIZATION_FAILED;
   }
   printf("calling the thing now ....\n");
   VkResult result = fpCreateInstance(pCreateInfo, pAllocator, pInstance);

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
   printf("\nfirst time the layer 1 gets called\n");
   if (pVersionStruct->loaderLayerInterfaceVersion < 2)
      return VK_ERROR_INITIALIZATION_FAILED;
   pVersionStruct->loaderLayerInterfaceVersion = 2;

   pVersionStruct->pfnGetInstanceProcAddr = get_instance_proc_addr;

   return VK_SUCCESS;
}