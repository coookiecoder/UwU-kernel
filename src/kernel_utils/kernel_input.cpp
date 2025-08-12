#include "kernel_input.hpp"
#include "kernel_output.hpp"

namespace cookie {
    void enable_cursor(const uint8_t start, const uint8_t end) {
        out_byte(VGA_COMMAND_PORT, 0x0A);
        out_byte(VGA_DATA_PORT, (in_byte(VGA_DATA_PORT) & 0xC0) | start);

        out_byte(VGA_COMMAND_PORT, 0x0B);
        out_byte(VGA_DATA_PORT, (in_byte(VGA_DATA_PORT) & 0xE0) | end);
    }

    void update_cursor(const int32_t line, const int32_t column) {
        const uint16_t pos = column + line * VGA_WIDTH;

        out_byte(VGA_COMMAND_PORT, 0x0F);
        out_byte(VGA_DATA_PORT, pos & 0xFF);

        out_byte(VGA_COMMAND_PORT, 0x0E);
        out_byte(VGA_DATA_PORT, pos >> 8 & 0xFF);
    }
}
