#include "kernel_utils/kernel_input.hpp"
#include "kernel_utils/kernel_output.hpp"

extern "C" void kernel_main(void* multiboot_structure, unsigned int magic_number) {
    cookie::kernel_clear_screen();

    const int len = cookie::kernel_print("HELLO WORLD FROM UWU KERNEL");

    cookie::enable_cursor(15, 15);

    cookie::update_cursor(0, len);

    while (true) {}
}