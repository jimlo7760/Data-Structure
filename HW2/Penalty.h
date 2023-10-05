//
// Created by Yinzoen Louh on 2023/1/26.
//

#ifndef HW2_PENALTY_H
#define HW2_PENALTY_H

#include <iostream>

class Penalty {
public:
    // Contructors
    Penalty(std::string aPenName);
    // Accessors
    std::string getPenName() const;
    int getPenNum() const;
    // Modifiers
    void setPenName(std::string aPenName);
    void setPenNum(int aPenNum);
    //other functions


private:
    std::string penName;
    int penNum;
};


#endif //HW2_PENALTY_H
