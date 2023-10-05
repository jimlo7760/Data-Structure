//
// Created by Yinzoen Louh on 2023/1/23.
//

#ifndef HW2_SCHOOL_H
#define HW2_SCHOOL_H


#include <vector>
#include <string>

class School {
public:
    // Contructors
    School(std::string teamName);

    // Accessors
    std::string getSchName() const;

    int getSchWinNum() const;

    int getSchLoseNum() const;

    int getSchTieNum() const;

    int getSchGoalNum() const;

    int getSchPenNum() const;

    // Modifiers
    void setSchName(std::string aSchName);

    void setSchWinNum(int aSchWinNum);

    void setSchLoseNum(int aSchLoseNum);

    void setSchTieNum(int aSchTieNum);

    void setSchGoalNum(int aSchGoalNum);

    void setSchPenNum(int aSchPenNum);
    //other functions
    double getWinPer() const;


private:
    std::string name;
    int winNum;
    int loseNum;
    int tieNum;
    int goalNum;
    int penNum;
};


#endif //HW2_SCHOOL_H
