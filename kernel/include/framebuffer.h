#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H  1

#include <stdint.h>
#include <common.h>

/// @brief Framebuffer Structure
typedef struct{
    void *address;
    u32 width;
    u32 height;
    u32 pitch;
    u32 bpp;

    u8 red_mask_size;
    u8 red_mask_shift;

    u8 green_mask_size;
    u8 green_mask_shift;

    u8 blue_mask_size;
    u8 blue_mask_shift;
}framebuffer_t;

framebuffer_t get_framebuffer_by_id(u8 id);

extern framebuffer_t framebuffers_array[];

#endif