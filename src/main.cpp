#include "kernel_utils/kernel_input.hpp"
#include "kernel_utils/kernel_output.hpp"
#include "kernel_utils/kernel_time.hpp"

extern "C" void kernel_main(void* multiboot_structure, unsigned int magic_number) {
    cookie::init_global_descriptor_table();
    cookie::enable_cursor(14, 15);
    cookie::update_cursor(0, 0);

    cookie::kernel_clear_screen();

    cookie::kernel_print("HELLO WORLD FROM UWU KERNEL", 0, 0, KERNEL_COLOR(LIGHT_MAGENTA, BLACK));
    cookie::kernel_print("HERE IS YOUR 42 UwU", 1, 0);

    cookie::global_descriptor_table_pointer current;
    gdt_get(&current);

    if (cookie::validate_global_descriptor_table(current)) {
        cookie::kernel_print("GLOBAL DESCRIPTOR TABLE WORKING", 3, 0, KERNEL_COLOR(GREEN, BLACK));
    } else {
        cookie::kernel_print("GLOBAL DESCRIPTOR TABLE NOT WORKING", 3, 0, KERNEL_COLOR(RED, BLACK));
    }

    cookie::kernel_print_stack(18);

    cookie::rtc_time time = {};

    while (true) {
        cookie::get_current_time(time);

        cookie::uint8_t first = time.second % 10 + '0';
        cookie::uint8_t second = time.second / 10 + '0';

        cookie::kernel_print(first, 24, 79);
        cookie::kernel_print(second, 24, 78);
        cookie::kernel_print(":", 24, 77);

        first = time.minute % 10 + '0';
        second = time.minute / 10 + '0';

        cookie::kernel_print(first, 24, 76);
        cookie::kernel_print(second, 24, 75);
        cookie::kernel_print(":", 24, 74);

        first = time.hour % 10 + '0';
        second = time.hour / 10 + '0';

        cookie::kernel_print(first, 24, 73);
        cookie::kernel_print(second, 24, 72);
    }
}
