#include <iostream>
#include <fstream>
#include <map>
#include "ds_hashset.h"

// hash function from the lab
class hash_string_obj {
public:

    // ----------------------------------------------------------
    // EXPERIMENT WITH THE HASH FUNCTION FOR CHECKPOINT 1, PART 2

    unsigned int operator() ( const std::string &key) const{
        //  This implementation comes from
        //  http://www.partow.net/programming/hashfunctions/
        //
        //  This is a general-purpose, very good hash function for strings.
        unsigned int hash = 1315423911;
        for(unsigned int i = 0; i < key.length(); i++)
            hash ^= ((hash << 5) + key[i] + (hash >> 2));
        return hash;
    }

};

typedef ds_hashset<std::pair<std::string, std::vector<int> >, hash_string_obj> ds_hashset_type;
int main() {
    std::string input;
    std::cin >> input;
    std::cin >> input;
    std::string fileName = input;
    std::fstream in_file(fileName);
    if (in_file.good()){
        float occu = 0.5;
        int tableSize = 100;
        std::cin >> input;
        if (input == "table_size"){
            std::cin >> input;
            tableSize = std::stoi(input);
            std::cin >> input;
        }
        if (input == "occupancy"){
            std::cin >> input;
            occu = std::stof(input);
            std::cin >> input;
        }
        int kmer = 0;
        if (input == "kmer"){
            std::cin >> input;
            kmer = std::stoi(input);
        }
        // create a instance of hash table
        ds_hashset_type hashSet(tableSize, occu);
        std::string database;
        std::string curRow;
        // store every rows in the file as a big string
        while (in_file >> curRow){
            // k-mer the current row
            for (unsigned int i = 0; i < curRow.size(); i++){
                database.push_back(curRow[i]);
            }
        }
        // "sliding" to get each k-mer substring and insert into the hash table
        for (unsigned int i = 0; (i + kmer) <= database.size(); i++){
            std::string curKmer;
            for (unsigned int j = i; j < (i + kmer); j++){
                curKmer.push_back(database[j]);
            }
            hashSet.insert(curKmer, i);
        }

        while (std::cin >> input){
            if (input == "quit"){
                break;
            }
            if (input == "query"){
                std::cin >> input;
                int misMatch = std::stoi(input);
                std::cin >> input;
                std::string target = input;

                // get the first k char in the target query
                std::string targetKmer;
                for (unsigned int i = 0; i < kmer; i++){
                    targetKmer.push_back(input[i]);
                }
                std::cout << "Query: " << target << std::endl;
                // find the target k-mer in the hash table
                std::vector<int> index = hashSet.find(targetKmer);
                if (index.size() == 0){
                    std::cout << "No Match" << std::endl;
                }else{
                    // vector to store the strings that meet the requirement
                    std::vector<std::pair<std::pair<int, int>, std::string> > matchStr;
                    for (unsigned int i = 0; i < index.size(); i++){
                        std::string curStr;
                        int curIndex = index[i];
                        int curMisMatch = 0;
                        for (unsigned int j = 0; j < target.size(); j++){
                            if (target[j] != database[curIndex + j]){
                                curMisMatch++;
                            }
                            curStr.push_back(database[curIndex + j]);
                        }
                        // compare the curren number of mismatch letters with the query string
                        if (curMisMatch <= misMatch){
                            matchStr.push_back(std::make_pair(std::make_pair(curIndex, curMisMatch), curStr));
                        }
                    }
                    if (matchStr.size() == 0){
                        std::cout << "No Match" << std::endl;
                    }else{
                        for (unsigned int i = 0; i < matchStr.size(); i++){
                            std::cout << matchStr[i].first.first << " "  << matchStr[i].first.second << " " << matchStr[i].second << std::endl;
                        }
                    }
                }
            }
        }
    }


    return 0;
}
