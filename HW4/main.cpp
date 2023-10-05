#include <iostream>
#include <list>
#include <fstream>
#include <string>

#include "Item.h"
#include "Customer.h"

/// Get an item from a Item list by itemId
/// \param aId item ID
/// \param aInvent item list
/// \param aItem gotten item
/// \return true: item exist in the list; false: item not exist in the list.
bool getItemFromInvent(std::string &aId, std::list<Item> &aInvent, Item &aItem) {
    for (std::list<Item>::iterator it = aInvent.begin(); it != aInvent.end(); it++) {
        if (aId == (*it).getId()) {
            aItem = (*it);
            return true;
        }
    }
    return false;
}

/// Check if there are enough item in the inventory
/// \param aInvent Inventory list
/// \param aItem an Item
/// \return true: enough stock; false: not enough stock
bool checkItemStock(std::list<Item> &aInvent, Item &aItem) {
    for (std::list<Item>::iterator it = aInvent.begin(); it != aInvent.end(); it++) {
        if ((*it).getId() == aItem.getId() && (*it).getQuan() >= aItem.getQuan()) {
            return true;
        }
    }
    return false;
}

/// decrease the stock in the inventory
/// \param aInvent inventory list
/// \param aItem item
void decFromInvent(std::list<Item> &aInvent, Item &aItem) {
    for (std::list<Item>::iterator it = aInvent.begin(); it != aInvent.end(); it++) {
        if ((*it).getId() == aItem.getId()) {
            (*it).decreaseQuaBy(aItem.getQuan());
            return;
        }
    }
}

/// increase the stock in the inventory
/// \param aInvent inventory list
/// \param aItem item
void incFromInvent(std::list<Item> &aInvent, Item &aItem) {
    for (std::list<Item>::iterator it = aInvent.begin(); it != aInvent.end(); it++) {
        if ((*it).getId() == aItem.getId()) {
            (*it).increaseQuanBy(aItem.getQuan());
            return;
        }
    }
}

/// Add the customer ID to the CusRentLst in Item class if not exist
/// \param aInvent inventory list
/// \param itemId item id
/// \param cusId customer id
void addCusToItemRentLst(std::list<Item> &aInvent, std::string &itemId, std::string &cusId) {
    for (std::list<Item>::iterator it = aInvent.begin(); it != aInvent.end(); it++) {
        if ((*it).getId() == itemId) {
//            std::list<std::string> cusIdLst = (*it).cusRentLstId;
            bool cusExisted = false;
            for (std::list<std::string>::iterator itCus = (*it).cusRentLstId.begin();
                 itCus != (*it).cusRentLstId.end(); itCus++) {
                if ((*itCus) == cusId) {
                    cusExisted = true;
                    break;
                }
            }
            if (!cusExisted) {
                if ((*it).cusRentLstId.size() == 0) {
                    (*it).cusRentLstId.push_back(cusId);
                } else if ((*it).cusRentLstId.size() == 1) {
                    std::string oldId = (*((*it).cusRentLstId.begin()));
                    if (cusId > oldId) {
                        (*it).cusRentLstId.push_back(cusId);
                    } else {
                        (*it).cusRentLstId.push_front(cusId);
                    }
                } else {
                    std::string beginId = (*((*it).cusRentLstId.begin()));
                    std::string endId = (*(--(*it).cusRentLstId.end()));
                    (*it).cusRentLstId.end()++;
                    if (cusId < beginId) {
                        (*it).cusRentLstId.push_front(cusId);
                    } else if (cusId > endId) {
                        (*it).cusRentLstId.push_back(cusId);
                    } else {
                        std::list<std::string>::iterator itStart = (*it).cusRentLstId.begin();
                        std::list<std::string>::iterator itEnd = (*it).cusRentLstId.end();
                        (*it).cusRentLstId.end()++;
                        for (std::list<std::string>::iterator ir = itStart; ir != itEnd; ++ir) {
                            std::string curId = (*ir);
                            std::string nextId = (*(++ir));
                            if (cusId > curId && cusId < nextId) {
                                (*it).cusRentLstId.insert(ir, cusId);
                                break;
                            }
                            ir--;
                        }
                    }
                }
            }
            break;
        }
    }
}

/// check if the current customer has rented this item
/// \param aCusRent customer rent list
/// \param aNewCus the new customer object
/// \param aItem the new item object
/// \return true: rented; false: not rented.
bool checkCusRented(std::list<Customer> &aCusRent, Customer &aNewCus, Item &aItem) {
    for (std::list<Customer>::iterator ir = aCusRent.begin(); ir != aCusRent.end(); ++ir) {
        if ((*ir).getId() == aNewCus.getId()) {
            // find if item match in the rented list of current customer
            std::list<Item> cusRentedItem = (*ir).itemLst;
            for (std::list<Item>::iterator it = cusRentedItem.begin(); it != cusRentedItem.end(); ++it) {
                if ((*it).getId() == aItem.getId() && (*it).getQuan() >= aItem.getQuan()) {
                    return true;
                }
            }
        }
    }
    return false;
}

/// update customer in customer rental list
/// \param aCusRent customer rental list
/// \param aNewCus the new customer object
/// \param aItem the new item object
/// \return true: need to change the cusId list in Item object; false: doesn't need to change
bool updateCusRentLst(std::list<Customer> &aCusRent, Customer &aNewCus, Item &aItem) {
    for (std::list<Customer>::iterator cusLstIt = aCusRent.begin(); cusLstIt != aCusRent.end(); ++cusLstIt) {
        if ((*cusLstIt).getId() == aNewCus.getId()) {
            std::list<Item> cusRentedItem = (*cusLstIt).itemLst;
            for (std::list<Item>::iterator it = cusRentedItem.begin(); it != cusRentedItem.end(); ++it) {
                (*it).decreaseQuaBy(aItem.getQuan());
                if ((*it).getQuan() == 0) {
                    cusRentedItem.erase(it);
                    if (cusRentedItem.size() == 0) {
                        aCusRent.erase(cusLstIt);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

/// update rented cusID list the corresponding Item object
/// \param aInvent inventory list
/// \param aNewCus the new customer object
/// \param aItem the new item object
void updateInvenLst(std::list<Item> &aInvent, Customer &aNewCus, Item &aItem) {
    for (std::list<Item>::iterator ir = aInvent.begin(); ir != aInvent.end(); ++ir) {
        if ((*ir).getId() == aItem.getId()) {
            (*ir).increaseQuanBy(aItem.getQuan());
//            std::list<std::string> rentedCusIds = (*ir).cusRentLstId;
            for (std::list<std::string>::iterator it = (*ir).cusRentLstId.begin();
                 it != (*ir).cusRentLstId.end(); ++it) {
                if ((*it) == aNewCus.getId()) {
                    (*ir).cusRentLstId.erase(it);
                    return;
                }
            }
        }
    }
}

void sortCusLst(Customer &newCus, std::list<Customer> &cusLst) {
    std::string cusId = newCus.getId();
    if (cusLst.size() == 0) {
        cusLst.push_back(newCus);
    } else if (cusLst.size() == 1) {
        std::string oldId = (*(cusLst.begin())).getId();
        if (cusId > oldId) {
            cusLst.push_back(newCus);
        } else {
            cusLst.push_front(newCus);
        }
    } else {
        std::string beginId = (*(cusLst.begin())).getId();
        std::string endId = (*(--cusLst.end())).getId();
        cusLst.end()++;
        if (cusId < beginId) {
            cusLst.push_front(newCus);
        } else if (cusId > endId) {
            cusLst.push_back(newCus);
        } else {
            std::list<Customer>::iterator itStart = cusLst.begin();
            std::list<Customer>::iterator itEnd = cusLst.end();
            cusLst.end()++;
            for (std::list<Customer>::iterator ir = itStart; ir != itEnd; ++ir) {
                std::string curId = (*ir).getId();
                std::string nextId = (*(++ir)).getId();
                if (cusId > curId && cusId < nextId) {
                    cusLst.insert(ir, newCus);
                    break;
                }
                ir--;
            }
        }
    }
}

void sortItemLst(Item &newItem, std::list<Item> &itemLst) {
    std::string itemId = newItem.getId();
    if (itemLst.size() == 0) {
        itemLst.push_back(newItem);
    } else if (itemLst.size() == 1) {
        std::string oldId = (*(itemLst.begin())).getId();
        if (itemId > oldId) {
            itemLst.push_back(newItem);
        } else {
            itemLst.push_front(newItem);
        }
    } else {
        std::string beginId = (*(itemLst.begin())).getId();
        std::string endId = (*(--itemLst.end())).getId();
        itemLst.end()++;
        if (itemId < beginId) {
            itemLst.push_front(newItem);
        } else if (itemId > endId) {
            itemLst.push_back(newItem);
        } else {
            std::list<Item>::iterator itStart = itemLst.begin();
            std::list<Item>::iterator itEnd = itemLst.end();
            itemLst.end()++;
            for (std::list<Item>::iterator ir = itStart; ir != itEnd; ++ir) {
                std::string curId = (*ir).getId();
                std::string nextId = (*(++ir)).getId();
                if (itemId > curId && itemId < nextId) {
                    itemLst.insert(ir, newItem);
                    break;
                }
                ir--;
            }
        }
    }
}

/// things to do when customer can rent successfully
/// \param inventory inventory list
/// \param cusRent customer rent list
/// \param newItem the new item object
/// \param newCus the new customer object
void rentSuccessAction(std::list<Item> &inventory, std::list<Customer> &cusRent, Item &newItem, Customer &newCus) {
    std::string itemId = newItem.getId();
    std::string cusId = newCus.getId();
    // decrease the item quantity in the inventory list
    decFromInvent(inventory, newItem);

    // add customer id to item cusRentLst
    addCusToItemRentLst(inventory, itemId, cusId);

    // check if the new customer has existed in cusRent list
    bool cusExist = false;
    for (std::list<Customer>::iterator it = cusRent.begin(); it != cusRent.end(); ++it) {
        if (cusId == (*it).getId()) {
            cusExist = true;

            // increase item or create a new item
            Item tempItem;
            bool itemExistInCus = getItemFromInvent(itemId, (*it).itemLst, tempItem);
            if (itemExistInCus) {
                (*it).increExistItem(newItem);
            } else {
                (*it).itemLst.push_back(newItem);
            }
            break;
        }
    }

    if (!cusExist) {
        // sort cusRent list
        sortCusLst(newCus, cusRent);
    }
}

int main(int argc, char *argv[]) {
    std::ifstream inventInStr(argv[1]);
    std::ifstream cusInStr(argv[2]);
    if (inventInStr.good() && cusInStr.good()) {
        std::list<Item> inventory;
        std::list<Customer> cusRent;
        std::list<Customer> cusWait;

        // get from inventory list
        std::string inputStr;
        while (inventInStr >> inputStr) {
            std::string newId = inputStr;
            inventInStr >> inputStr;
            int newQuan = std::stoi(inputStr);
            inventInStr >> inputStr;
            std::string newDes = inputStr;
            std::list<Customer> inventCusLst;

            // check the validation of the item's input
            if (newId[0] != 'T' || newQuan <= 0) {
                std::cerr << "Invalid inventory ID " + newId + " found in the inventory file." << std::endl;
            } else {
                // the up-coming new item
                Item newItem = Item(newId, newQuan, newDes);
                // sort inventory list
                if (inventory.size() == 0) {
                    inventory.push_back(newItem);
                } else if (inventory.size() == 1) {
                    std::string oldId = (*(inventory.begin())).getId();
                    if (newId > oldId) {
                        inventory.push_back(newItem);
                    } else {
                        inventory.push_front(newItem);
                    }
                } else {
                    std::string beginId = (*(inventory.begin())).getId();
                    std::string endId = (*(--inventory.end())).getId();
                    inventory.end()++;
                    if (newId < beginId) {
                        inventory.push_front(newItem);
                    } else if (newId > endId) {
                        inventory.push_back(newItem);
                    } else {
                        std::list<Item>::iterator itStart = inventory.begin();
                        std::list<Item>::iterator itEnd = --inventory.end();
                        inventory.end()++;
                        for (std::list<Item>::iterator ir = itStart; ir != itEnd; ++ir) {
                            std::string curId = (*ir).getId();
                            std::string nextId = (*(++ir)).getId();
                            if (newId > curId && newId < nextId) {
                                inventory.insert(ir, newItem);
                                break;
                            }
                            ir--;
                        }
                    }
                }
            }
//            for (std::list<Item>::iterator ir = inventory.begin(); ir != inventory.end(); ++ir) {
//                std::cout << (*ir).getId() << std::endl;
//            }
//            std::cout << std::endl;
        }
        while (cusInStr >> inputStr) {
            std::string cusId = inputStr;
            cusInStr >> inputStr;
            std::string type = inputStr;
            cusInStr >> inputStr;
            cusInStr >> inputStr;
            int quan = std::stoi(inputStr);
            cusInStr >> inputStr;
            std::string itemId = inputStr;
            cusInStr >> inputStr;
            std::string name = inputStr;
            if (cusId[0] != 'C') {
                std::cerr << "Invalid customer information found for ID " + cusId + " in the customer file."
                          << std::endl;
            } else {
                // check if the current itemID is in the inventory list
                Item tempItem;
                bool itemExist = getItemFromInvent(itemId, inventory, tempItem);
                if (!itemExist) {
                    if (type == "rent") {
                        std::cerr << "Customer " + cusId + " requested item " + itemId +
                                     " which is not in the inventory." << std::endl;
                    } else if (type == "return") {
                        std::cerr << "Customer " + cusId + " attempted to return item " + itemId +
                                     " which is not in the inventory." << std::endl;
                    }
                } else {
                    std::string tempDes = tempItem.getDes();
                    Item newItem = Item(itemId, quan, tempDes);
                    Customer newCus = Customer(cusId, quan, name, newItem);
                    if (type == "rent") {
                        bool enoughStock = checkItemStock(inventory, newItem);
                        if (enoughStock) {
                            rentSuccessAction(inventory, cusRent, newItem, newCus);
                        } else {
                            // add to wait list
                            cusWait.push_back(newCus);
                        }
                    } else if (type == "return") {
                        // has finish checking if the item is in the inventory

                        bool rented = checkCusRented(cusRent, newCus, newItem);
                        if (!rented) {
                            std::cerr
                                    << "Customer " + newCus.getId() + " attempted to return item " + newItem.getId() +
                                       " which she/he did not rent." << std::endl;
                        } else {
                            // update the customer rent list
                            bool updateInven = updateCusRentLst(cusRent, newCus, newItem);
                            if (updateInven) {
                                updateInvenLst(inventory, newCus, newItem);
                            }

                            // check wait list
                            std::list<Customer>::iterator waitIt = cusWait.begin();
                            while (waitIt != cusWait.end()) {
                                Customer curCus = (*waitIt);
                                Item deserveItem = *(curCus.itemLst.begin());
                                bool enough = checkItemStock(inventory, deserveItem);
                                if (!enough) {
                                    waitIt++;
                                } else {
                                    rentSuccessAction(inventory, cusRent, deserveItem, curCus);
                                    waitIt = cusWait.erase(waitIt);
                                }
                            }
                        }
                    }
                }
            }
        }

        // sort pending list
        std::list<Customer> sortWaitLst;
        for (std::list<Customer>::iterator waIt = cusWait.begin(); waIt != cusWait.end(); ++waIt) {
            sortCusLst((*waIt), sortWaitLst);
        }

        std::ofstream invOutStr(argv[3]);
        std::ofstream cusOutStr(argv[4]);
        if (invOutStr.good() && cusOutStr.good()) {
            // store into inventory_output file
            for (std::list<Item>::iterator it = inventory.begin(); it != inventory.end(); ++it) {
                invOutStr << (*it).getId() << " " << (*it).getQuan() << " available " << (*it).getDes() << std::endl;
                // check customer rental list
                std::list<std::string> rentedCus = (*it).cusRentLstId;
                if (rentedCus.size() > 0) {
                    invOutStr << "Rental Customers: ";
                    for (std::list<std::string>::iterator cusIdItr = rentedCus.begin();
                         cusIdItr != rentedCus.end(); cusIdItr++) {
                        std::string cusId = (*cusIdItr);
                        for (std::list<Customer>::iterator cusInfoItr = cusRent.begin();
                             cusInfoItr != cusRent.end(); cusInfoItr++) {
                            if ((*cusInfoItr).getId() == cusId) {
                                invOutStr << (*cusInfoItr).getId() << " " << (*cusInfoItr).getName() << " ";
                                std::list<Item> rentedItem = (*cusInfoItr).itemLst;
                                for (std::list<Item>::iterator rentItemItr = rentedItem.begin();
                                     rentItemItr != rentedItem.end(); rentItemItr++) {
                                    if ((*rentItemItr).getId() == (*it).getId()) {
                                        invOutStr << "(" << (*rentItemItr).getQuan() << ") ";
                                    }
                                }
                            }
                        }
                    }
                    invOutStr << std::endl;
                }
                // check customer pending list
                bool haveOutput = false;
                for (std::list<Customer>::iterator waIt = sortWaitLst.begin(); waIt != sortWaitLst.end(); waIt++) {
                    Customer curCus = (*waIt);
                    Item ite = *(curCus.itemLst.begin());
                    if (ite.getId() == (*it).getId()) {
                        if (!haveOutput) {
                            haveOutput = true;
                            invOutStr << "Pending Customers: ";
                        }
                        invOutStr << curCus.getId() << " " << curCus.getName() << " (" << ite.getQuan() << ") ";
                    }
                }
                if (haveOutput) {
                    invOutStr << std::endl;
                }
                invOutStr << std::endl;
            }

            // remove repeated item in wait list
            for (std::list<Customer>::iterator ir = sortWaitLst.begin(); ir != sortWaitLst.end(); ++ir) {
                for (std::list<Customer>::iterator it = sortWaitLst.begin(); it != ir; it++) {
                    if ((*ir).getId() == (*it).getId()) {
                        sortItemLst(*((*ir).itemLst.begin()), ((*it).itemLst));
                    }
                }
            }

            std::list<Customer>::iterator rentalIt = cusRent.begin();
            std::list<Customer>::iterator waitIt = sortWaitLst.begin();
            while (rentalIt != cusRent.end() && waitIt != sortWaitLst.end()) {
                std::string rentId = (*rentalIt).getId();
                std::string waitId = (*waitIt).getId();
                if (rentId < waitId) {
                    cusOutStr << rentId << " " << (*rentalIt).getName() << std::endl;
                    cusOutStr << "Rentals: ";
                    for (std::list<Item>::iterator itr = (*rentalIt).itemLst.begin();
                         itr != (*rentalIt).itemLst.end(); itr++) {
                        cusOutStr << (*itr).getId() << " (" << (*itr).getQuan() << ") ";
                    }
                    cusOutStr << std::endl << std::endl;
                    rentalIt++;
                } else if (rentId > waitId) {
                    cusOutStr << waitId << " " << (*waitIt).getName() << std::endl;
                    cusOutStr << "Pending: ";
                    for (std::list<Item>::iterator itr = (*waitIt).itemLst.begin();
                         itr != (*waitIt).itemLst.end(); itr++) {
                        cusOutStr << (*itr).getId() << " (" << (*itr).getQuan() << ") ";
                    }
                    cusOutStr << std::endl << std::endl;
                    waitIt++;
                } else {
                    cusOutStr << waitId << " " << (*waitIt).getName() << std::endl;
                    cusOutStr << "Pending: ";
                    for (std::list<Item>::iterator itr = (*waitIt).itemLst.begin();
                         itr != (*waitIt).itemLst.end(); itr++) {
                        cusOutStr << (*itr).getId() << " (" << (*itr).getQuan() << ") ";
                    }
                    cusOutStr << std::endl;
                    cusOutStr << "Rentals: ";
                    for (std::list<Item>::iterator itr = (*rentalIt).itemLst.begin();
                         itr != (*rentalIt).itemLst.end(); itr++) {
                        cusOutStr << (*itr).getId() << " (" << (*itr).getQuan() << ") ";
                    }
                    cusOutStr << std::endl << std::endl;
                    waitIt++;
                    rentalIt++;
                }
            }
            while (rentalIt != cusRent.end()) {
                cusOutStr << (*rentalIt).getId() << " " << (*rentalIt).getName() << std::endl;
                cusOutStr << "Rentals: ";
                for (std::list<Item>::iterator itr = (*rentalIt).itemLst.begin();
                     itr != (*rentalIt).itemLst.end(); itr++) {
                    cusOutStr << (*itr).getId() << " (" << (*itr).getQuan() << ") ";
                }
                cusOutStr << std::endl << std::endl;
                rentalIt++;
            }
            while (waitIt != sortWaitLst.end()) {
                cusOutStr << (*waitIt).getId() << " " << (*waitIt).getName() << std::endl;
                cusOutStr << "Pending: ";
                for (std::list<Item>::iterator itr = (*waitIt).itemLst.begin();
                     itr != (*waitIt).itemLst.end(); itr++) {
                    cusOutStr << (*itr).getId() << " (" << (*itr).getQuan() << ") ";
                }
                cusOutStr << std::endl << std::endl;
                waitIt++;
            }
        }

//        std::cout << "RENTED:" << std::endl;
//        for (std::list<Customer>::iterator ir = cusRent.begin(); ir != cusRent.end(); ir++) {
//            (*ir).print();
//            std::cout << std::endl << std::endl;
//        }
//        std::cout << "Waiting: " << std::endl;
//        for (std::list<Customer>::iterator ir = cusWait.begin(); ir != cusWait.end(); ir++) {
//            (*ir).print();
//            std::cout << std::endl << std::endl;
//        }
    }
    return 0;
}