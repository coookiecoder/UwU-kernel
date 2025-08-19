#include "kernel_panics.hpp"
#include "kernel_output.hpp"

namespace cookie {
    void kernel_panic(const char *message) {
        kernel_print("KERNEL PANIC, HALTING SYSTEM :\n", KERNEL_COLOR(WHITE_FOREGROUND, RED_BACKGROUND));
        kernel_print(message);

        while (true) {
            asm volatile("hlt");
        }
    }
}
