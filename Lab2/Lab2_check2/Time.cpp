//
// Created by Yinzoen Louh on 2023/1/18.
//

#include <iostream>
#include "Time.h"

// constructor
Time::Time() {
    hour = 0;
    minute = 0;
    second = 0;
}
Time::Time(int aHour, int aMinute, int aSecond) {
    hour = aHour;
    minute = aMinute;
    second = aSecond;
}

//accessor
int Time::getHour() const {
    return hour;
}
int Time::getMinute() const {
    return minute;
}
int Time::getSecond() const {
    return second;
}

//modifier
void Time::setHour(int aHour) {
    hour = aHour;
}
void Time::setMinute(int aMinute) {
    minute = aMinute;
}
void Time::setSecond(int aSecond) {
    second = aSecond;
}

//other functions
void Time::PrintAMPM() {
    std::string hourStr;
    std::string minuteStr;
    std::string secondStr;
    int pntHour = hour;
    int pntMinute = minute;
    int pntSecond = second;
    bool am = true;
    if (hour >= 12){
        am = false;
        pntHour -= 12;
    }
    hourStr = std::to_string(pntHour);
    if (pntMinute < 10){
        minuteStr = '0' + std::to_string(pntMinute);
    }
    if (pntSecond < 10){
        secondStr = '0' + std::to_string(pntSecond);
    }
    std::cout << hourStr << ':' << minuteStr << ':' << secondStr << ' ';
    if (am){
        std::cout << "am";
    }else{
        std::cout << "pm";
    }
}

// comparing two time
bool IsEarlierThan(const Time& time1, const Time& time2){
    if (time1.getHour() < time2.getHour()){
        return true;
    }
    if (time1.getHour() == time2.getHour() && time1.getMinute() < time2.getMinute()){
        return true;
    }
    if (time1.getHour() == time2.getHour() && time1.getMinute() == time2.getMinute()
    && time1.getSecond() < time2.getSecond()){
        return true;
    }
    return false;
}