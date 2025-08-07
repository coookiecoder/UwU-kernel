#ifndef KERNEL_INPUT_HPP
#define KERNEL_INPUT_HPP

#define VGA_COMMAND_PORT 0x3D4
#define VGA_DATA_PORT 0x3D5

extern  "C" unsigned char in_byte(unsigned short port);

namespace cookie {
    void enable_cursor(unsigned char start, unsigned char end);
    void update_cursor(int line, int column);
}

#endif //KERNEL_INPUT_HPP
