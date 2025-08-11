#include "kernel_type.hpp"

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
        pointer.limit = sizeof(entries) * sizeof(global_descriptor_table_entry) - 1;
        pointer.base = reinterpret_cast<uint32_t>(entries);

        // 0xCF = 4KB pages, 32-bit protected mode

        // 0x08: Kernel Code Segment (Ring 0)
        gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xC);

        // 0x10: Kernel Data Segment (Ring 0)
        gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xC);

        // 0x18: Kernel Stack Segment (Ring 0) - Same as data segment
        gdt_set_gate(3, 0, 0xFFFFFFFF, 0x92, 0xC);

        // 0x20: User Code Segment (Ring 3)
        gdt_set_gate(4, 0, 0xFFFFFFFF, 0xFA, 0xC);

        // 0x28: User Data Segment (Ring 3)
        gdt_set_gate(5, 0, 0xFFFFFFFF, 0xF2, 0xC);

        // 0x30: User Stack Segment (Ring 3) - Same as data segment
        gdt_set_gate(6, 0, 0xFFFFFFFF, 0xF2, 0xC);
    }
}