#ifndef KERNEL_PANICS_HPP
#define KERNEL_PANICS_HPP

namespace cookie {
    void kernel_panic(const char * message) __attribute__((noreturn));
}

#endif
