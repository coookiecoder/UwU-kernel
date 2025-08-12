#include "kernel_time.hpp"

#include "kernel_input.hpp"
#include "kernel_output.hpp"

namespace cookie {
    uint8_t read_rtc_register(const uint8_t address) {
        out_byte(CMOS_ADDRESS, 1 << 7 | address);
        return in_byte(CMOS_DATA);
    }

    uint8_t bcd_to_bin(const uint8_t bcd_value) {
        return (bcd_value & 0x0F) + (bcd_value >> 4) * 10;
    }

    bool is_update_in_progress() {
        return read_rtc_register(0x0A) & 0x80;
    }

    void get_current_time(rtc_time &result) {
        rtc_time last = {};

        while (is_update_in_progress()) {}

        result.second = read_rtc_register(0x00);
        result.minute = read_rtc_register(0x02);
        result.hour = read_rtc_register(0x04);
        result.day = read_rtc_register(0x07);
        result.month = read_rtc_register(0x08);
        result.year = read_rtc_register(0x09);

        do {
            last = result;

            while (is_update_in_progress()) {}

            result.second = read_rtc_register(0x00);
            result.minute = read_rtc_register(0x02);
            result.hour = read_rtc_register(0x04);
            result.day = read_rtc_register(0x07);
            result.month = read_rtc_register(0x08);
            result.year = read_rtc_register(0x09);

        } while (result != last);

        uint8_t register_b = read_rtc_register(0x0B);

        result.second = bcd_to_bin(result.second);
        result.minute = bcd_to_bin(result.minute);
        result.hour = bcd_to_bin(result.hour);
        result.day = bcd_to_bin(result.day);
        result.month = bcd_to_bin(result.month);
        result.year = bcd_to_bin(result.year);

        if (register_b & 0x02 == false && result.hour & 0x80) {
            result.hour = (result.hour & 0x7F + 12) % 24;
        }

        result.year += 2000;
    }

}
