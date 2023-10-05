//
// Created by Yinzoen Louh on 2023/1/26.
//

#include "Penalty.h"

// constructors
Penalty::Penalty(std::string aPenName) {
    penName = aPenName;
    penNum = 1;
}
// accessors
std::string Penalty::getPenName() const {
    return penName;
}
int Penalty::getPenNum() const {
    return penNum;
}
// modifiers
void Penalty::setPenName(std::string aPenName) {
    penName = aPenName;
}
void Penalty::setPenNum(int aPenNum) {
    penNum = aPenNum;
}
// other functions
