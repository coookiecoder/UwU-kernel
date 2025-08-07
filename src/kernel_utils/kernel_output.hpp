#ifndef KERNEL_OUTPUT_HPP
#define KERNEL_OUTPUT_HPP

#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN 0x3
#define RED 0x4
#define MAGENTA 0x5
#define BROWN 0x6
#define LIGHT_GRAY 0x7
#define GRAY 0x8
#define LIGHT_BLUE 0x9
#define LIGHT_GREEN 0xA
#define LIGHT_CYAN 0xB
#define LIGHT_RED 0xC
#define LIGHT_MAGENTA 0xD
#define LIGHT_YELLOW 0xE
#define WHITE 0xF

#define KERNEL_COLOR(FG, BG) (((BG) << 4) | (FG)) << 8

#define VGA_WIDTH 80
#define VGA_HEIGHT 25


extern "C" void out_byte(unsigned short port, unsigned char data);

namespace cookie {
    int kernel_print(const char *str, short line = 0, short column = 0);
    int kernel_print(unsigned char c, short line = 0, short column = 0);
    void kernel_clear_screen();
}

#endif
