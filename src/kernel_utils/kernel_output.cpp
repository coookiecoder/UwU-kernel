#include "kernel_input.hpp"
#include "kernel_output.hpp"
#include "kernel_time.hpp"

volatile cookie::uint16_t * video_memory = reinterpret_cast<unsigned short *>(0xB8000);

namespace cookie {
    void kernel_set_title(const char *str, int32_t color) {
        int offset = kernel_print_at(str, 0, 0, color);

        while (offset < VGA_WIDTH) {
            video_memory[offset++] = ' ' | color;
        }
    }


    int kernel_print_at(const char *str, const int16_t line, const int16_t column, const int32_t color) {
        const int offset = column + line * VGA_WIDTH;
        int i = 0;

        while (str[i] != '\0') {
            video_memory[offset + i] = str[i] | color;
            ++i;
        }
        
        return i;
    }

    int kernel_print_at(const char c, const int16_t line, const int16_t column, const int32_t color) {
        const int offset = column + line * VGA_WIDTH;

        video_memory[offset] = c | color;

        return 1;
    }

    int kernel_print(const char *str, int32_t color) {
        static int16_t line = 1;
        static int16_t column = 0;

        uint16_t index = 0;

        while (str[index]) {
            if (str[index] != '\n')
                kernel_print_at(str[index], line, column++, color);

            if (column == VGA_WIDTH || str[index] == '\n') {
                ++line;
                column = 0;
            }

            if (line == VGA_HEIGHT - 2) {
                kernel_print_new_line();
                line = 22;
                column = 0;
            }

            ++index;
        }

        return index;
    }

    int kernel_print(char c, int32_t color) {
        char buffer[2] = {c, 0};

        return kernel_print(buffer, color);
    }



    void kernel_clear_screen() {
        int i = 0;
        while (i < VGA_WIDTH * VGA_HEIGHT) {
            video_memory[i] = 0 | KERNEL_COLOR(WHITE_FOREGROUND, BLACK_BACKGROUND);
            ++i;
        }
    }

    void kernel_print_stack(int count) {
        auto stack_ptr = reinterpret_cast<uint32_t *>(get_stack_pointer());
        char hex_buffer[11];

        kernel_print("--- STACK DUMP ---\n");

        for (int i = 0; i < count; ++i) {
            uint32_t value = stack_ptr[i];

            // Print the address
            uint32_to_hex_str(reinterpret_cast<uint32_t>(stack_ptr + i), hex_buffer);
            kernel_print(hex_buffer);
            kernel_print(" : ");

            // Print the value at that address
            uint32_to_hex_str(value, hex_buffer);
            kernel_print(hex_buffer);
            kernel_print("\n");
        }
    }

    void kernel_print_stack_at(uint32_t address) {
        char hex_buffer[11];

        uint32_to_hex_str(address, hex_buffer);
        kernel_print(hex_buffer);
        kernel_print(" : ");

        uint32_to_hex_str(*reinterpret_cast<uint32_t *>(address), hex_buffer);
        kernel_print(hex_buffer);
        kernel_print("\n");
    }

    void kernel_print_stack_until(uint32_t address) {
        auto stack_ptr = reinterpret_cast<uint32_t *>(get_stack_pointer());
        char hex_buffer[11];

        kernel_print("--- STACK DUMP ---\n");

        for (int i = 0; stack_ptr + i != reinterpret_cast<uint32_t *>(address); ++i) {
            uint32_t value = stack_ptr[i];

            // Print the address
            uint32_to_hex_str(reinterpret_cast<uint32_t>(stack_ptr + i), hex_buffer);
            kernel_print(hex_buffer);
            kernel_print(" : ");

            // Print the value at that address
            uint32_to_hex_str(value, hex_buffer);
            kernel_print(hex_buffer);
            kernel_print("\n");
        }

        kernel_print_stack_at(address);
    }

    void kernel_print_time() {
        rtc_time time = {};
        get_current_time(time);

        get_current_time(time);

        uint8_t first = time.second % 10 + '0';
        uint8_t second = time.second / 10 + '0';

        kernel_print_at(first, 24, 79);
        kernel_print_at(second, 24, 78);
        kernel_print_at(":", 24, 77);

        first = time.minute % 10 + '0';
        second = time.minute / 10 + '0';

        kernel_print_at(first, 24, 76);
        kernel_print_at(second, 24, 75);
        kernel_print_at(":", 24, 74);

        first = time.hour % 10 + '0';
        second = time.hour / 10 + '0';

        kernel_print_at(first, 24, 73);
        kernel_print_at(second, 24, 72);
    }

    void kernel_print_new_line() {
        for (uint8_t line = 2; line < VGA_HEIGHT - 1; ++line) {
            for (uint8_t column = 0; column < VGA_WIDTH; ++column) {
                video_memory[(line - 1) * VGA_WIDTH + column] = video_memory[line * VGA_WIDTH + column];
            }
        }

        for (uint8_t column = 0; column < VGA_WIDTH; ++column) {
            video_memory[23 * VGA_WIDTH + column] = 0 | KERNEL_COLOR(WHITE_FOREGROUND, BLACK_BACKGROUND);
        }
    }

}
