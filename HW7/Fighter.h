//
// Created by Yinzoen Louh on 2023/3/19.
//

#ifndef HW7_FIGHTER_H
#define HW7_FIGHTER_H

#include <iostream>
#include <string>
#include <set>
#include <map>


class Fighter {
public:
    // Contructors
    Fighter();
    Fighter(std::string aName);
    // Accessors
    std::map<std::string, int> getMap();
    // Modifiers
    void setMove(std::string aMove, int aFrameNum);
    //other functions


private:
    std::string name;
    std::map<std::string, int> move;
};


#endif //HW7_FIGHTER_H
