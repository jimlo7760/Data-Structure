//
// Created by Yinzoen Louh on 2023/1/18.
//

#include <iostream>
#include "Animal.h"

// constructor
Animal::Animal(std::string aName) {
    name = aName;
}

//accessor
std::string Animal::getName() const {
    return name;
}
int Animal::getWeight() const {
    return weight;
}
bool Animal::getLandSur() const {
    return landSur;
}
bool Animal::getWaterSur() const {
    return waterSur;
}
bool Animal::getEatMeat() const {
    return eatMeat;
}
bool Animal::getEatPlant() const {
    return eatPlant;
}

//modifier
void Animal::setWeight(int aWeight) {
    weight = aWeight;
}
void Animal::setLandSur(bool aLandSur) {
    landSur = aLandSur;
}
void Animal::setWaterSur(bool aWaterSur) {
    waterSur = aWaterSur;
}
void Animal::setEatMeat(bool aEatMeat) {
    eatMeat = aEatMeat;
}
void Animal::setEatPlant(bool aEatPlant) {
    eatPlant = aEatPlant;
}

// other functions
bool Animal::isOmni(const bool aEatMeat, const bool aEatPlant) {
    if (aEatMeat && aEatPlant){
        return true;
    }
}
bool Animal::isAmphi(const bool aLandSur, const bool aWaterSur) {
    if (aLandSur && aWaterSur){
        return true;
    }
}