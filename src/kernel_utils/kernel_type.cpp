#include "kernel_type.hpp"

#include "kernel_output.hpp"
#include "kernel_input.hpp"

cookie::global_descriptor_table_entry entries[7] __attribute__((section(".gdt"))) = {};
cookie::global_descriptor_table_pointer pointer = {};

namespace cookie {
    static
    void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
        entries[num].base_low    = (base & 0xFFFF);
        entries[num].base_middle = (base >> 16) & 0xFF;
        entries[num].base_high   = (base >> 24) & 0xFF;

        entries[num].limit_low   = (limit & 0xFFFF);
        entries[num].granularity = (limit >> 16) & 0x0F;

        entries[num].granularity |= gran & 0xF0;
        entries[num].access      = access;
    }

    void init_global_descriptor_table() {
        pointer.limit = sizeof(entries) - 1;
        pointer.base = reinterpret_cast<uint32_t>(entries);

        // 0xCF = 4KB pages, 32-bit protected mode

        // 0x08: Kernel Code Segment (Ring 0)
        gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xC0);

        // 0x10: Kernel Data Segment (Ring 0)
        gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xC0);

        // 0x18: Kernel Stack Segment (Ring 0) - Same as data segment
        gdt_set_gate(3, 0, 0xFFFFFFFF, 0x92, 0xC0);

        // 0x20: User Code Segment (Ring 3)
        gdt_set_gate(4, 0, 0xFFFFFFFF, 0xFA, 0xC0);

        // 0x28: User Data Segment (Ring 3)
        gdt_set_gate(5, 0, 0xFFFFFFFF, 0xF2, 0xC0);

        // 0x30: User Stack Segment (Ring 3) - Same as data segment
        gdt_set_gate(6, 0, 0xFFFFFFFF, 0xF2, 0xC0);

        gdt_flush(reinterpret_cast<cookie::uint32_t>(&pointer));
    }

    bool validate_global_descriptor_table(global_descriptor_table_pointer current) {
        return current.base == pointer.base && current.limit == pointer.limit;
    }

    void uint32_to_hex_str(cookie::uint32_t num, char* buffer) {
        buffer[0] = '0';
        buffer[1] = 'x';
        const char* hex = "0123456789ABCDEF";
        for (int i = 0; i < 8; ++i) {
            // Get the i-th hex digit from the right
            int nibble = (num >> (28 - i * 4)) & 0xF;
            buffer[i + 2] = hex[nibble];
        }
        buffer[10] = '\0'; // Null-terminate the string
    }
}