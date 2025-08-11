#include "kernel_utils/kernel_input.hpp"
#include "kernel_utils/kernel_output.hpp"
#include "kernel_utils/kernel_time.hpp"

#define KBD_STATUS_PORT 0x64
#define KBD_CMD_PORT 0x64
#define KBD_DATA_PORT 0x60

void a20_enable() {
    cookie::uint8_t port_val = in_byte(0x92);
    port_val |= 2;
    port_val &= ~1;
    out_byte(0x92, port_val);
}

void a20_disable() {
    cookie::uint8_t port_val = in_byte(0x92);
    port_val &= ~2;
    out_byte(0x92, port_val);
}

extern "C" void kernel_main(void* multiboot_structure, unsigned int magic_number) {
    a20_disable();

    // cookie::init_global_descriptor_table();

    cookie::kernel_clear_screen();
    cookie::enable_cursor(14, 15);

    cookie::kernel_print("HELLO WORLD FROM UWU KERNEL", 0, 0, KERNEL_COLOR(LIGHT_MAGENTA, BLACK));
    cookie::kernel_print("HERE IS YOUR 42 UwU", 1, 0);

    volatile cookie::uint32_t* test_ptr = (cookie::uint32_t*)0x200000;

    cookie::uint32_t magic_gdt_number = 0xDEADBEEF;
    *test_ptr = magic_gdt_number;
    cookie::kernel_print("Wrote 0xDEADBEEF to address 0x200000", 3);

    cookie::uint32_t read_value = *test_ptr;
    cookie::kernel_print("Read back value from address 0x200000", 4);

    if (read_value == magic_gdt_number) {
        cookie::kernel_print("SUCCESS: Memory at 2MB is accessible!", 5, 0, KERNEL_COLOR(GREEN, BLACK));
    } else {
        cookie::kernel_print("FAILURE: Memory test failed!", 5, 0, KERNEL_COLOR(RED, BLACK));
    }

    cookie::update_cursor(10, 0);

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
