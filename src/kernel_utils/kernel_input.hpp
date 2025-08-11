#ifndef KERNEL_INPUT_HPP
#define KERNEL_INPUT_HPP

#define VGA_COMMAND_PORT 0x3D4
#define VGA_DATA_PORT 0x3D5

#include "kernel_type.hpp"

extern "C" unsigned char in_byte(cookie::uint16_t port);

namespace cookie {
    void enable_cursor(uint8_t start, uint8_t end);
    void update_cursor(int32_t line, int32_t column);
}

#endif //KERNEL_INPUT_HPP
