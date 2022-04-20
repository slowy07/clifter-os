#ifndef _ARCH_MM_PAGE_FRAME_H_
#define _ARCH_MM_PAGE_FRAME_H_

#define PAGE_SIZE 4096
#define PAGE_SHIFT 12
#define NUMBER_OF_BUDDIES 4

extern void init_page_frame();
extern uint32_t free_mem_start;

#endif // _ARCH_MM_PAGE_FRAME_H_