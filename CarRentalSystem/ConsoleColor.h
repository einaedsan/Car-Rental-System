#pragma once
#include <windows.h>

// فقط رنگ متن (بدون بک‌گراند)
enum TextColor {
    TC_BLACK = 0,
    TC_DARK_BLUE = 1,
    TC_DARK_GREEN = 2,
    TC_DARK_CYAN = 3,
    TC_DARK_RED = 4,
    TC_DARK_MAGENTA = 5,
    TC_DARK_YELLOW = 6,
    TC_LIGHT_GRAY = 7,

    TC_DARK_GRAY = 8,
    TC_BLUE = 9,
    TC_GREEN = 10,
    TC_CYAN = 11,
    TC_RED = 12,
    TC_MAGENTA = 13,
    TC_YELLOW = 14,
    TC_WHITE = 15
};


// تغییر رنگ متن
inline void setTextColor(TextColor color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// برگرداندن به حالت پیش‌فرض
inline void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
