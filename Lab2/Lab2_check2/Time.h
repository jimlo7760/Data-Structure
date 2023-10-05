//
// Created by Yinzoen Louh on 2023/1/18.
//

#ifndef LAB2_CHECK2_TIME_H
#define LAB2_CHECK2_TIME_H


class Time {
public:
    //constructor
    Time();
    Time(int aHour, int aMinute, int aSecond);

    // accessor
    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    //modifier
    void setHour(int aHour);
    void setMinute(int aMinute);
    void setSecond(int aSecond);

    //other functions
    void PrintAMPM();


private:
    int hour;
    int minute;
    int second;
};

bool IsEarlierThan(const Time& t1, const Time& t2);


#endif //LAB2_CHECK2_TIME_H
