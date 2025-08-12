#include "kernel_utils/kernel_input.hpp"
#include "kernel_utils/kernel_output.hpp"
#include "kernel_utils/kernel_time.hpp"

extern "C" void kernel_main(void* multiboot_structure, unsigned int magic_number) {
    cookie::kernel_clear_screen();
    cookie::enable_cursor(0, 0);
    cookie::update_cursor(0, 0);

    cookie::init_global_descriptor_table();

    cookie::global_descriptor_table_pointer current;
    gdt_get(&current);

    if (cookie::validate_global_descriptor_table(current)) {
        cookie::kernel_print("GLOBAL DESCRIPTOR TABLE LOADED AND WORKING\n", KERNEL_COLOR(GREEN, BLACK));
    } else {
        cookie::kernel_print("GLOBAL DESCRIPTOR TABLE NOT LOADED OR NOT WORKING\n", KERNEL_COLOR(RED, BLACK));
    }

    cookie::kernel_set_title("HELLO WORLD FROM UWU KERNEL", KERNEL_COLOR(LIGHT_MAGENTA, BLACK));

    cookie::kernel_print('\n');
    cookie::kernel_print_stack(500);
    cookie::kernel_print('\n');


    cookie::kernel_print("MAGIC NUMBER ADDRESS AND VALUE : \n");
    cookie::kernel_print_stack_at(reinterpret_cast<cookie::uint32_t>(&magic_number));

    while (true) {
        cookie::kernel_print_time();
    }
}
