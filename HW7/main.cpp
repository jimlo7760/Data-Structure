#include <string>
//You may add additional typedefs, includes, etc. up here
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include "Fighter.h"


//This is the only array you are allowed to have in your program.
const std::string move_names[7] = {"jab", "forward-tilt", "up-tilt", "down-tilt", "forward-smash", "up-smash",
                                   "down-smash"};

//Feel free to put forward declarations here
// map store the fighters and their data
std::map<std::string, Fighter> friMap;
// map store the move and its data
std::map<std::string, std::map<int, std::set<std::string>>> moveMap;

int main(int argc, char **argv) {
    // Argument parsing
    if (argc != 4) {
        std::cerr << "Proper usage is " << argv[0] << " [database file] [input file] [output file]" << std::endl;
        return -1;
    }

    std::ifstream dbfile(argv[1]);
    if (!dbfile) {
        std::cerr << "Failed to open database " << argv[1] << " for reading." << std::endl;
    }

    std::ifstream infile(argv[2]);
    if (!infile) {
        std::cerr << "Failed to open input " << argv[2] << " for reading." << std::endl;
    }

    std::ofstream outfile(argv[3]);
    if (!outfile) {
        std::cerr << "Failed to open output " << argv[3] << " for writing." << std::endl;
    }

    ///////Fill in the rest of main below:
    std::string x;
    for (int i = 0; i < 8; i++) {
        dbfile >> x;
    }
    while (dbfile >> x) {
        std::string charName = x;
        for (int i = 0; i < 7; i++) {
            dbfile >> x;
            std::string moveName = move_names[i];
            int moveFrame = std::stoi(x);
            friMap[charName].setMove(moveName, moveFrame);
            moveMap[moveName][moveFrame].insert(charName);
        }
    }
    typedef std::map<std::string, Fighter>::iterator friMapItr;
    typedef std::map<std::string, std::map<int, std::set<std::string>>>::iterator moveMapItr;
    typedef std::map<int, std::set<std::string>>::iterator moveFriMapItr;

    typedef std::map<int, std::set<std::string>> moveFriMap;
    while (infile >> x) {
        std::string query = x;
        infile >> x;
        std::string name = x;
        infile >> x;
        std::string thiKey = x;
        if (query == "-q") {
            friMapItr itr = friMap.find(name);
            if (itr == friMap.end()) {
                outfile << "Invalid character name: " << name << std::endl;
            } else {
                typedef std::map<std::string, int>::iterator friMoveItr;
                // get the fighter's data
                Fighter curFighter = itr->second;
                std::map<std::string, int> friMoveMap = curFighter.getMap();
                if (thiKey == "all") {
                    // traverse all moves of the current fighter
                    for (friMoveItr it = friMoveMap.begin(); it != friMoveMap.end(); it++) {
                        std::string moveName = it->first;
                        int moveFrame = it->second;
                        outfile << name << " " << moveName << ": " << moveFrame << std::endl;
                    }
                } else {
                    // find the specific move in the current fighter
                    friMoveItr it = friMoveMap.find(thiKey);
                    if (it == friMoveMap.end()) {
                        outfile << "Invalid move name: " << thiKey << std::endl;
                    } else {
                        std::string moveName = it->first;
                        int moveFrame = it->second;
                        outfile << name << " " << moveName << ": " << moveFrame << std::endl;
                    }
                }
            }
        } else if (query == "-f") {
            moveMapItr it = moveMap.find(name);
            if (it == moveMap.end()) {
                outfile << "Invalid move name: " << name << std::endl;
            } else {
                outfile << query << " " << name << " " << thiKey << std::endl;
                // get the map of fighters of the current move
                moveFriMap moveFriTempMap = it->second;
                moveFriMapItr moveFriTempMapItr = moveFriTempMap.begin();
                int limit = std::stoi(thiKey);
                int frameNum = moveFriTempMapItr->first;
                // get the set of fighters in the move at this frame
                std::set<std::string> curFriSet = moveFriTempMapItr->second;
                std::set<std::string>::iterator curFriSetItr = curFriSet.begin();
                unsigned int curFriNum = curFriSet.size();
                while (true) {
                    // when the number of fighters in the current frame of current move is greater than limit
                    if (limit <= curFriNum) {
                        break;
                    }
                    limit -= curFriNum;
                    while (curFriSetItr != curFriSet.end()) {
                        outfile << (*curFriSetItr) << " " << frameNum << std::endl;
                        curFriSetItr++;
                    }
                    moveFriTempMapItr++;
                    frameNum = moveFriTempMapItr->first;
                    curFriSet = moveFriTempMapItr->second;
                    curFriNum = curFriSet.size();
                    curFriSetItr = curFriSet.begin();
                }
                // output the rest of fighters
                for (int i = 0; i < limit; i++) {
                    outfile << (*curFriSetItr) << " " << frameNum << std::endl;
                    curFriSetItr++;
                }
            }
        }else if (query == "-s"){
            moveMapItr it = moveMap.find(name);
            if (it == moveMap.end()) {
                outfile << "Invalid move name: " << name << std::endl;
            } else {
                outfile << query << " " << name << " " << thiKey << std::endl;
                moveFriMap moveFriTempMap = it->second;
                // set the start iterator be the largest frame, indicating the slowest fighters
                moveFriMapItr moveFriTempMapItr = moveFriTempMap.end();
                moveFriTempMapItr--;
                int limit = std::stoi(thiKey);
                int frameNum = moveFriTempMapItr->first;
                std::set<std::string> curFriSet = moveFriTempMapItr->second;
                std::set<std::string>::iterator curFriSetItr = curFriSet.begin();
                unsigned int curFriNum = curFriSet.size();
                while (true) {
                    if (limit <= curFriNum) {
                        break;
                    }
                    limit -= curFriNum;
                    while (curFriSetItr != curFriSet.end()) {
                        outfile << (*curFriSetItr) << " " << frameNum << std::endl;
                        curFriSetItr++;
                    }
                    moveFriTempMapItr--;
                    frameNum = moveFriTempMapItr->first;
                    curFriSet = moveFriTempMapItr->second;
                    curFriNum = curFriSet.size();
                    curFriSetItr = curFriSet.begin();
                }
                for (int i = 0; i < limit; i++) {
                    outfile << (*curFriSetItr) << " " << frameNum << std::endl;
                    curFriSetItr++;
                }
            }
        }else if (query == "-d"){
            moveMapItr it = moveMap.find(name);
            if (it == moveMap.end()) {
                outfile << "Invalid move name: " << name << std::endl;
            } else {
                // get the set of fighters on the particular frame
                outfile << query << " " << name << " " << thiKey << std::endl;
                int frameNum = std::stoi(thiKey);
                std::set<std::string> moveFriSet = moveMap[name][frameNum];
                std::set<std::string>::iterator setIt;
                for (setIt = moveFriSet.begin(); setIt != moveFriSet.end(); ++setIt){
                    outfile << (*setIt) << std::endl;
                }
            }
        }
        outfile << std::endl;
    }


    return 0;
}
