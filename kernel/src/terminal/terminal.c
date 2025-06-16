#include <framebuffer.h>
#include <flanterm/flanterm.h>
#include <flanterm/flanterm_backends/fb.h>
#include <stdlib.h>

framebuffer_t mainframebuffer;

int init_flanterm(){
    mainframebuffer = get_framebuffer_by_id(0);
    struct flanterm_context *ft_ctx = flanterm_fb_init(
        NULL,
        NULL,
        mainframebuffer.address, mainframebuffer.width, mainframebuffer.height, mainframebuffer.pitch,
        mainframebuffer.red_mask_size, mainframebuffer.red_mask_shift,
        mainframebuffer.green_mask_size, mainframebuffer.green_mask_shift,
        mainframebuffer.blue_mask_size, mainframebuffer.blue_mask_shift,
        NULL,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL,
        NULL, 0, 0, 1,
        0, 0,
        0
    );

    const char message[] = "hello\n";
    flanterm_write(ft_ctx, message, sizeof(message));
}