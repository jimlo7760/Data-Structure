//
// Created by Yinzoen Louh on 2023/4/12.
//

#ifndef HW9_DS_HASHSET_H
#define HW9_DS_HASHSET_H

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

template<class KeyType, class HashFunc>
class ds_hashset {
public:
    // constructor:
    ds_hashset(int &aSize, float &aMaxOccu) {
        (this->table) = std::vector<KeyType>(aSize);
        this->keyNum = 0;
        this->maxOccu = aMaxOccu;
    }

    /// insert function
    /// \param strKey the k-mer
    /// \param strIndex the start index of k-mer in the original string
    void insert(std::string &strKey, int strIndex) {
        // compare the current occupancy to determine whether we need to resize the table
        float tempKeyNum = (this -> keyNum);
        float tempTableSize = (this -> table).size();
        float curOccu = tempKeyNum / tempTableSize;
        if (curOccu > (this -> maxOccu)) {
            this->resizeTable(2 * (this->table).size());
        }

        // get the index should be put in the hash table
        unsigned int hashVal = hashFunc(strKey);
        unsigned int index = hashVal % (this->table).size();
        // by linear probing, store the string in the first empty space
        while ((this->table)[index].first != "") {
            // check if the current string has previously existed
            if ((this -> table)[index].first == strKey){
                break;
            }
            index++;
            if (index == (this -> table).size()){
                index = 0;
            }
        }
        ((this->table)[index].first) = strKey;
        // add the new location to the current string
        ((this->table)[index].second).push_back(strIndex);
        this->keyNum++;
    }

    /// insert function from the resize function (copy data from the genome sequence)
    /// \param strKey the actual string to insert
    /// \param strIndexVec the locations of the string
    void insert(std::string &strKey, std::vector<int> strIndexVec){
        unsigned int hashVal = hashFunc(strKey);
        unsigned int index = hashVal % (this->table).size();
        (this->table)[index].first = strKey;
        (this->table)[index].second = strIndexVec;
        this->keyNum++;
    }

    /// resize table to the given size
    /// \param newSize given the size of table
    void resizeTable(int newSize) {
        std::vector<KeyType> newTable(newSize);
        std::vector<KeyType> oldTable = (this -> table);
        (this -> table) = newTable;
        for (unsigned int i = 0; i < oldTable.size(); i++){
            // search for the non-empty pairs in the old table, copy it to the new table
            if (oldTable[i].first != ""){
                this ->insert(oldTable[i].first, oldTable[i].second);
            }
        }
    }

    /// find the locations of the k-mer appears in the genome sequence
    /// \param key k-mer
    /// \return a vector of locations in the genome sequence
    std::vector<int> find(const std::string& key){
        std::vector<int> matchIndex;
        unsigned int hashVal = hashFunc(key);
        unsigned int index = hashVal % (this->table).size();

        matchIndex = (this->table)[index].second;
        return matchIndex;
    }

private:
    std::vector<KeyType> table;
    HashFunc hashFunc;
    unsigned int keyNum;
    float maxOccu;
};


#endif //HW9_DS_HASHSET_H
