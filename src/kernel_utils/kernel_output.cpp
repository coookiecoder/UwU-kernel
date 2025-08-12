#include "kernel_input.hpp"
#include "kernel_output.hpp"

namespace cookie { 
    int kernel_print(const char *str, const int16_t line, const int16_t column, const int32_t color) {
        volatile uint16_t * video_memory = reinterpret_cast<unsigned short *>(0xB8000);

        const int offset = column + line * VGA_WIDTH;
        int i = 0;

        while (str[i] != '\0') {
            video_memory[offset + i] = str[i] | color;
            ++i;
        }
        
        return i;
    }

    int kernel_print(const unsigned char c, const int16_t line, const int16_t column, const int32_t color) {
        volatile uint16_t * video_memory = reinterpret_cast<unsigned short *>(0xB8000);

        const int offset = column + line * VGA_WIDTH;

        video_memory[offset] = c | color;

        return 1;
    }

    void kernel_clear_screen() {
        volatile uint16_t * video_memory = reinterpret_cast<unsigned short *>(0xB8000);

        int i = 0;
        while (i < VGA_WIDTH * VGA_HEIGHT) {
            video_memory[i] = ' ' | KERNEL_COLOR(WHITE, BLACK);
            ++i;
        }
    }

    void kernel_print_stack(int count) {
        uint32_t* stack_ptr = reinterpret_cast<uint32_t*>(get_stack_pointer());
        char hex_buffer[11];

        kernel_print("--- STACK DUMP ---", 5, 0);

        for (int i = 0; i < count; ++i) {
            uint32_t value = stack_ptr[i];

            // Print the address
            uint32_to_hex_str(reinterpret_cast<uint32_t>(stack_ptr + i), hex_buffer);
            kernel_print(hex_buffer, 6 + i, 0);
            kernel_print(": ", 6 + i, 12);

            // Print the value at that address
            uint32_to_hex_str(value, hex_buffer);
            kernel_print(hex_buffer, 6 + i, 14);
        }
    }
}
