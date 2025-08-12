#ifndef KERNEL_OUTPUT_HPP
#define KERNEL_OUTPUT_HPP

#define BLACK_FOREGROUND 0x0
#define BLUE_FOREGROUND 0x1
#define GREEN_FOREGROUND 0x2
#define CYAN_FOREGROUND 0x3
#define RED_FOREGROUND 0x4
#define MAGENTA_FOREGROUND 0x5
#define BROWN_FOREGROUND 0x6
#define LIGHT_GRAY_FOREGROUND 0x7
#define GRAY_FOREGROUND 0x8
#define LIGHT_BLUE_FOREGROUND 0x9
#define LIGHT_GREEN_FOREGROUND 0xA
#define LIGHT_CYAN_FOREGROUND 0xB
#define LIGHT_RED_FOREGROUND 0xC
#define LIGHT_MAGENTA_FOREGROUND 0xD
#define LIGHT_YELLOW_FOREGROUND 0xE
#define WHITE_FOREGROUND 0xF

#define BLACK_BACKGROUND 0x0
#define BLUE_BACKGROUND 0x1
#define GREEN_BACKGROUND 0x2
#define CYAN_BACKGROUND 0x3
#define RED_BACKGROUND 0x4
#define MAGENTA_BACKGROUND 0x5
#define BROWN_BACKGROUND 0x6
#define GRAY_BACKGROUND 0x7

#define KERNEL_COLOR(FG, BG) ((FG) << 8 | (BG) << 12)

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#include "kernel_type.hpp"

extern "C" void out_byte(cookie::uint16_t port, cookie::uint8_t data);

namespace cookie {
    void kernel_set_title(const char *str, int32_t color = KERNEL_COLOR(WHITE_FOREGROUND, BLACK_BACKGROUND));
    int kernel_print_at(const char *str, int16_t line = 0, int16_t column = 0, int32_t color = KERNEL_COLOR(WHITE_FOREGROUND, BLACK_BACKGROUND));
    int kernel_print_at(char c, int16_t line = 0, int16_t column = 0, int32_t color = KERNEL_COLOR(WHITE_FOREGROUND, BLACK_BACKGROUND));
    int kernel_print(const char *str, int32_t color = KERNEL_COLOR(WHITE_FOREGROUND, BLACK_BACKGROUND));
    int kernel_print(char c, int32_t color = KERNEL_COLOR(WHITE_FOREGROUND, BLACK_BACKGROUND));
    void kernel_clear_screen();
    void kernel_print_stack(int count);
    void kernel_print_stack_at(uint32_t address);
    void kernel_print_time();
    void kernel_print_new_line();
}

#endif
