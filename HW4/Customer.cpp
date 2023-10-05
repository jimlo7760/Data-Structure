//
// Created by Yinzoen Louh on 2023/2/14.
//

#include "Customer.h"

// Constructors
Customer::Customer(std::string& aId, int aQuan, std::string& aName, Item& aItem) {
    id = aId;
    name = aName;
    itemLst.push_back(aItem);
}

// Accessors
const std::string& Customer::getId() const {
    return id;
}
const std::string& Customer::getName() const {
    return name;
}

// Modifiers
void Customer::increExistItem(Item &aItem) {
    for (std::list<Item>::iterator it = (*this).itemLst.begin(); it != (*this).itemLst.end(); it++){
        if ((*it).getId() == aItem.getId()){
            (*it).increaseQuanBy(aItem.getQuan());
            return;
        }
    }
}

// Other functions
void Customer::print() {
    std::cout << "Id: " << this->getId() << std::endl;
    std::cout << "Name: " << this->getName() << std::endl;
    std::cout << "renting item: ";
    for (std::list<Item>::iterator it = (*this).itemLst.begin(); it != (*this).itemLst.end(); it++){
        std::cout << (*it).getId() << "(" << (*it).getQuan() << "), ";
    }
}