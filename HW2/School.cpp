//
// Created by Yinzoen Louh on 2023/1/23.
//

#include "School.h"

// constructor
School::School(std::string teamName) {
    name = teamName;
    winNum = 0;
    loseNum = 0;
    tieNum = 0;
    goalNum = 0;
    penNum = 0;
}

// accessors
std::string School::getSchName() const {
    return name;
}

int School::getSchWinNum() const{
    return winNum;
}

int School::getSchLoseNum() const {
    return loseNum;
}

int School::getSchTieNum() const{
    return tieNum;
}

int School::getSchGoalNum() const{
    return goalNum;
}

int School::getSchPenNum() const{
    return penNum;
}

// modifiers
void School::setSchName(std::string aSchName) {
    name = aSchName;
}

void School::setSchWinNum(int aSchWinNum) {
    winNum = aSchWinNum;
}

void School::setSchLoseNum(int aSchLoseNum) {
    loseNum = aSchLoseNum;
}

void School::setSchTieNum(int aSchTieNum) {
    tieNum = aSchTieNum;
}

void School::setSchGoalNum(int aSchGoalNum) {
    goalNum = aSchGoalNum;
}

void School::setSchPenNum(int aSchPenNum) {
    penNum = aSchPenNum;
}

// other functions
/// get the win percentage of the school
/// \return win percentage as double
double School::getWinPer() const{
    return (winNum + 0.5 * tieNum) / (winNum + loseNum + tieNum);
}