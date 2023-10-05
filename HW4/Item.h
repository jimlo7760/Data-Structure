//
// Created by Yinzoen Louh on 2023/2/14.
//

#ifndef HW4_ITEM_H
#define HW4_ITEM_H

#include <iostream>
#include <list>

class Item {
public:
    // Contructors
    Item();
    Item(std::string& aId, int aQuan, std::string& aDes);

    // Accessors
    const std::string &getId() const;

    int getQuan() const;
    const std::string &getDes() const;


    // Modifiers
    void setQuan(int aQuan);
    void increaseQuanBy(int aQuan);
    void decreaseQuaBy(int aQuan);
    void setDes(std::string& aDes);
    //other functions
    void print();

    std::list<std::string> cusRentLstId;
private:
    std::string id;
    int quan;
    std::string des;
};


#endif //HW4_ITEM_H
