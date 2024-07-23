/*
 * Copyright (c) 2024 Karf5
 * PS4 11.00 Disable Updates
 */

#include "ps4.h"
void* kernel_base = NULL;
int kpayload(struct thread *td){

 kernel_base = &((uint8_t*)__readmsr(0xC0000082))[-0x1C0];
 return 0;
}

int _main(struct thread *td) {
    static int (*sceKernelDebugOutText)(int, const char*) = NULL;

    initKernel();
    initLibc();
    initNetwork();
    initSysUtil();

  unlink("/update/PS4UPDATE.PUP.net.temp");
  rmdir("/update/PS4UPDATE.PUP.net.temp");
  mkdir("/update/PS4UPDATE.PUP.net.temp", 777);

  unlink("/update/PS4UPDATE.PUP");
  rmdir("/update/PS4UPDATE.PUP");
  mkdir("/update/PS4UPDATE.PUP", 777);

    int libk = sceKernelLoadStartModule("libkernel_sys.sprx", 0, NULL, 0, 0, 0);
    RESOLVE(libk, sceKernelDebugOutText);

    if (sceKernelDebugOutText) {
        sceKernelDebugOutText(0, "");
        sceKernelDebugOutText(0, "");
        sceKernelDebugOutText(0, "");
    }

    printf_notification("Disable System Updates!" "\nCoded By Karf5");
    syscall(11, kpayload);
    char buf[255];
    sprintf(buf, "kernel_base: %p\n", kernel_base);
    sceKernelDebugOutText(0, buf);
    
    return 0;
}
