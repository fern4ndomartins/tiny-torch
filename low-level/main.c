#include <libdrm/amdgpu.h>
#include <libdrm/amdgpu_drm.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
// use ldconfig -p to list away all your libs
// -I/usr/include/libdrm for header files and -l with this libs name for linking (apparently if static or dynamic the linker is who decides)

int main() {
    int fd = open("/dev/dri/renderD128", O_RDWR | O_CLOEXEC);
    if (!fd) {
        printf("failed to load\n");
        return -1;
    } 
    printf("file descriptor: %d\n", fd);
    uint32_t major_version, minor_version;
    amdgpu_device_handle device;

    if (!amdgpu_device_initialize(fd, &major_version, &minor_version, &device)) {
        printf("sucessfully initialized device\n");
    }
    
    uint64_t size = 3000000;

    struct amdgpu_bo_alloc_request req = {
    .alloc_size       = size,
    .phys_alignment   = 4096,  
    .preferred_heap   = AMDGPU_GEM_DOMAIN_VRAM,
    .flags            = AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED | AMDGPU_GEM_CREATE_VRAM_CLEARED,
    };

    amdgpu_bo_handle buffer_handle = NULL;
    int ret = amdgpu_bo_alloc(device, &req, &buffer_handle);
    if (ret != 0) {
        printf("failed\n");
        return -1;
    } else {
        printf("worked\n");
    }
    uint32_t count;

    amdgpu_query_hw_ip_count(device, AMDGPU_HW_IP_DMA , &count);
    printf("number of ips: %u\n", count);
}