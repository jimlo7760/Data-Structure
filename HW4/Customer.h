//
// Created by Yinzoen Louh on 2023/2/14.
//

#ifndef HW4_CUSTOMER_H
#define HW4_CUSTOMER_H

#include <iostream>
#include <list>

#include "Item.h"

class Customer {
public:
    // Contructors
    Customer(std::string& aId, int aQuan, std::string& aName, Item& aItem);

    // Accessors
    const std::string &getId() const;
    const std::string &getName() const;


    // Modifiers
    void increExistItem(Item& aItem);
    //other functions
    void print();

    std::list<Item> itemLst;
private:
    std::string id;
    std::string name;
};


#endif //HW4_CUSTOMER_H
