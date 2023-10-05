//
// Created by Yinzoen Louh on 2023/3/19.
//

#include "Fighter.h"

// Constructors
Fighter::Fighter() {
    return;
}
Fighter::Fighter(std::string aName) {
    name = aName;
}
// Accessors
std::map<std::string, int> Fighter::getMap() {
    return move;
}
// Modifiers
void Fighter::setMove(std::string aMove, int aFrameNum) {
    move[aMove] = aFrameNum;
}
// Other functions
