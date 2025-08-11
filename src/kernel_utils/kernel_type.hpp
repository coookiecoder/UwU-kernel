#ifndef KERNEL_TYPE_HPP
#define KERNEL_TYPE_HPP

namespace cookie {
    typedef signed char int8_t;
    typedef unsigned char uint8_t;
    typedef signed short int int16_t;
    typedef unsigned short int uint16_t;
    typedef signed int int32_t;
    typedef unsigned int uint32_t;
    typedef signed long int int64_t;
    typedef unsigned long int uint64_t;

    typedef struct global_descriptor_table_entry {
        uint16_t limit_low;       // The lower 16 bits of the limit
        uint16_t base_low;        // The lower 16 bits of the base
        uint8_t  base_middle;     // The next 8 bits of the base
        uint8_t  access;          // Access flags (e.g., present, privilege level, type)
        uint8_t  granularity;     // Granularity (is limit in bytes or pages?), and high limit bits
        uint8_t  base_high;       // The last 8 bits of the base
    } global_descriptor_table_entry __attribute__((packed));

    typedef struct global_descriptor_table_pointer {
        uint16_t limit;
        uint32_t base;
    } global_descriptor_table_pointer __attribute__((packed));

    void init_global_descriptor_table();
}

extern "C" void gdt_flush(cookie::uint32_t gdt_ptr_addr);

#endif
