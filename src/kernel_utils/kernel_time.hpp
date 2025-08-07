#ifndef KERNEL_TIME_HPP
#define KERNEL_TIME_HPP

#include "kernel_type.hpp"

#define CMOS_ADDRESS 0x70
#define CMOS_DATA 0x71

namespace cookie {
    struct rtc_time {
        __uint8_t second;
        __uint8_t minute;
        __uint8_t hour;
        __uint8_t day;
        __uint8_t month;
        __uint32_t year;
    };

    inline bool operator!=(const rtc_time &a, const rtc_time &b) {
        if (a.second != b.second) {
            return true;
        } if (a.minute != b.minute) {
            return true;
        } if (a.hour != b.hour) {
            return true;
        } if (a.day != b.day) {
            return true;
        } if (a.month != b.month) {
            return true;
        } if (a.year != b.year) {
            return true;
        }

        return false;
    }

    __uint8_t read_rtc_register(__uint8_t address);
    __uint8_t bcd_to_bin(__uint8_t bcd_value);
    bool is_update_in_progress();

    void get_current_time(rtc_time &result);
}

#endif
