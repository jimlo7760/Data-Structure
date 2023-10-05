//
// Created by Yinzoen Louh on 2023/1/18.
//

#ifndef LAB2_ANIMAL_H
#define LAB2_ANIMAL_H
#include <iostream>


class Animal {
public:
    // constructor
    Animal(std::string aName);

    //accessor
    std::string getName() const;
    int getWeight() const;
    bool getLandSur() const;
    bool getWaterSur() const;
    bool getEatMeat() const;
    bool getEatPlant() const;

    //modifier
    void setWeight(int aWeight);
    void setLandSur(bool aLandSur);
    void setWaterSur(bool aWaterSur);
    void setEatMeat(bool aEatMeat);
    void setEatPlant(bool aEatPlant);

    // other function
    bool isOmni(const bool aEatMeat, const bool aEatPlant);
    bool isAmphi(const bool aLandSur, const bool aWaterSur);

private:
    std::string name;
    int weight;
    bool landSur;
    bool waterSur;
    bool eatMeat;
    bool eatPlant;
};


#endif //LAB2_ANIMAL_H
