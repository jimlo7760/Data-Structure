//
// Created by Yinzoen Louh on 2023/2/14.
//

#include "Item.h"

// Constructors
Item::Item() {
    quan = 0;
}
Item::Item(std::string& aId, int aQuan, std::string& aDes) {
    id = aId;
    quan = aQuan;
    des = aDes;
}

// Accessors
const std::string &Item::getId() const {
    return id;
}
int Item::getQuan() const {
    return quan;
}
const std::string& Item::getDes() const {
    return des;
}
// Modifiers
void Item::setQuan(int aQuan) {
    quan = aQuan;
}
void Item::increaseQuanBy(int aQuan) {
    int curQuan = this -> getQuan();
    curQuan += aQuan;
    this->setQuan(curQuan);
}
void Item::decreaseQuaBy(int aQuan){
    int curQuan = this -> getQuan();
    curQuan -= aQuan;
    this->setQuan(curQuan);
}
void Item::setDes(std::string& aDes) {
    des = aDes;
}




// Other functions

void Item::print() {
    std::cout << "id: " << this->getId() << std::endl;
    std::cout << "quan: " << this->getQuan() << std::endl;
    std::cout << "des: " << this->getDes() << std::endl;
    std::cout << "cus: ";
    for (std::list<std::string>::iterator it = cusRentLstId.begin(); it != cusRentLstId.end(); it++){
        std::cout << (*it) << " ";
    }
}
