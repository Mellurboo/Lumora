#include <stdlib.h>
#include <limine.h>
#include <common.h>
#include <framebuffer.h>

framebuffer_t framebuffers_array[];

/// Request the Framebuffer from limine
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

/// @brief checks that framebuffer (id) is not null
/// @param id 
/// @return 
uint8_t verify_framebuffer(u8 id){
    if(framebuffer_request.response->framebuffers[id] == NULL ||
    framebuffer_request.response->framebuffer_count < 1){
        return 1;
    }else{
        return 0;
    }
}

framebuffer_t get_framebuffer_by_id(u8 id){
    if (verify_framebuffer(id) == 0){
        for (u8 i = 0; i < framebuffer_request.response->framebuffer_count; i++){
            framebuffers_array[i].address = framebuffer_request.response->framebuffers[i]->address;
            framebuffers_array[i].height = framebuffer_request.response->framebuffers[i]->height;
            framebuffers_array[i].width = framebuffer_request.response->framebuffers[i]->width;
            framebuffers_array[i].bpp = framebuffer_request.response->framebuffers[i]->bpp;
            framebuffers_array[i].pitch = framebuffer_request.response->framebuffers[i]->pitch;

            framebuffers_array[i].red_mask_size = framebuffer_request.response->framebuffers[i]->red_mask_size;
            framebuffers_array[i].red_mask_shift = framebuffer_request.response->framebuffers[i]->red_mask_shift;

            framebuffers_array[i].green_mask_size = framebuffer_request.response->framebuffers[i]->green_mask_size;
            framebuffers_array[i].green_mask_shift = framebuffer_request.response->framebuffers[i]->green_mask_shift;

            framebuffers_array[i].blue_mask_size = framebuffer_request.response->framebuffers[i]->blue_mask_size;
            framebuffers_array[i].blue_mask_shift = framebuffer_request.response->framebuffers[i]->blue_mask_shift;
        }
    }

    return framebuffers_array[id];
}