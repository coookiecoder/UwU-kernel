#include "kernel_input.hpp"
#include "kernel_output.hpp"

namespace cookie {
    int kernel_print(const char *str, const short line, const short column) {
        volatile unsigned short * video_memory = reinterpret_cast<unsigned short *>(0xB8000);

        const int offset = column + line * VGA_WIDTH;
        int i = 0;

        while (str[i] != '\0') {
            video_memory[offset + i] = str[i] | KERNEL_COLOR(WHITE, BLACK);
            ++i;
        }

        return i;
    }

    int kernel_print(const unsigned char c, const short line, const short column) {
        volatile unsigned short * video_memory = reinterpret_cast<unsigned short *>(0xB8000);

        const int offset = column + line * VGA_WIDTH;

        video_memory[offset] = c | KERNEL_COLOR(WHITE, BLACK);

        return 1;
    }

    void kernel_clear_screen() {
        volatile unsigned short * video_memory = reinterpret_cast<unsigned short *>(0xB8000);

        int i = 0;
        while (i < VGA_WIDTH * VGA_HEIGHT) {
            video_memory[i] = ' ' | KERNEL_COLOR(WHITE, BLACK);
            ++i;
        }
    }
}