#include <limine.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <common.h>
#include <framebuffer.h>
#include <terminal/terminal.h>
#include <main.h>

// Access the limine base revision and then mark the 
// attribute as used, the base revision is 3 as it is 
// the latest.
ATTRIBUTE_USED(".limine_requests")
static volatile LIMINE_BASE_REVISION(3);
ATTRIBUTE_USED(".limine_requests_start")
static volatile LIMINE_REQUESTS_START_MARKER
ATTRIBUTE_USED(".limine_requests_end")
static volatile LIMINE_REQUESTS_END_MARKER

/// @brief the Kernel entry point equivilant to int main
/// @param void 
void kmain(void){
    init_flanterm();
}