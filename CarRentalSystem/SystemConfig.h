#pragma once
#pragma once

class SystemDate {
private:
    static int currentDay;
public:
    static int getDay() { return currentDay; }
    static void advanceDay(int days = 1) { currentDay += days; }
    static void setDay(int day) { currentDay = day; }
};

 // روز شروع سیستم

class SystemConfig {
public:
    static const int MAX_ACTIVE_RENTALS;
    static const double MAX_DEBT;
    static const double DAILY_LATE_FINE;
};
