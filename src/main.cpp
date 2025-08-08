#include "kernel_utils/kernel_input.hpp"
#include "kernel_utils/kernel_output.hpp"
#include "kernel_utils/kernel_time.hpp"

extern "C" void kernel_main(void* multiboot_structure, unsigned int magic_number) {
    cookie::kernel_clear_screen();
    cookie::enable_cursor(0, 15);

    const int len = cookie::kernel_print("HELLO WORLD FROM UWU KERNEL");

    cookie::update_cursor(1, 0);

    cookie::rtc_time time = {};

    while (true) {
        cookie::get_current_time(time);

        __uint8_t first = time.second % 10 + '0';
        __uint8_t second = time.second / 10 + '0';

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
