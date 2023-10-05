#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include "Student.h"
#include "School.h"
#include "Penalty.h"

// manipulating studArr

/// get the index of the current student in studArr
/// \param studArr student array
/// \param studName student's name
/// \param schName name of student's school
/// \return the index of the student
unsigned int getStudIndex(std::vector<Student> &studArr, std::string studName, std::string schName) {
    for (unsigned int i = 0; i < studArr.size(); i++) {
        if (studArr[i].getStudName() == studName && studArr[i].getStudSch() == schName) {
            return i;
        }
    }
    Student aStud(studName, schName);
    studArr.push_back(aStud);
    return studArr.size() - 1;
}

/// increase the goal number of the student
/// \param studArr student array
/// \param studIndex index of the student in the array
void studGoal(std::vector<Student> &studArr, unsigned int studIndex) {
    int goalNum = studArr[studIndex].getStudGoalNum();
    goalNum++;
    studArr[studIndex].setStudGoalNum(goalNum);
}

/// increase the assistance number of the student
/// \param studArr student array
/// \param studIndex index of the student in the array
void studAssist(std::vector<Student> &studArr, unsigned int studIndex) {
    int assistNum = studArr[studIndex].getStudAssistNum();
    assistNum++;
    studArr[studIndex].setStudAssistNum(assistNum);
}

/// increase the penalty number of the student
/// \param studArr student array
/// \param studIndex index of the student in the array
void studPen(std::vector<Student> &studArr, unsigned int studIndex) {
    int penNum = studArr[studIndex].getStudPenNum();
    penNum++;
    studArr[studIndex].setStudPenNum(penNum);
}

// manipulating schArr
/// get the index of the current school in schArr
/// \param schArr school array
/// \param schName name of the current school
/// \return the index of the student
unsigned int getSchIndex(std::vector<School> &schArr, std::string schName) {
    for (unsigned int i = 0; i < schArr.size(); i++) {
        if (schArr[i].getSchName() == schName) {
            return i;
        }
    }
    School aSch(schName);
    schArr.push_back(aSch);
    return schArr.size() - 1;
}

/// increase the goal number of the school
/// \param schArr school array
/// \param schIndex index of the school in the array
void schGoal(std::vector<School> &schArr, unsigned int schIndex) {
    int goalNum = schArr[schIndex].getSchGoalNum();
    goalNum++;
    schArr[schIndex].setSchGoalNum(goalNum);
}

/// increase the penalty number of the school
/// \param schArr school array
/// \param schIndex index of the school in the array
void schPen(std::vector<School> &schArr, unsigned int schIndex) {
    int penNum = schArr[schIndex].getSchPenNum();
    penNum++;
    schArr[schIndex].setSchPenNum(penNum);
}

/// increase the win number of the school
/// \param schArr school array
/// \param schIndex index of the school in the array
void schWin(std::vector<School> &schArr, unsigned int schIndex) {
    int winNum = schArr[schIndex].getSchWinNum();
    winNum++;
    schArr[schIndex].setSchWinNum(winNum);
}

/// increase the lose number of the school
/// \param schArr school array
/// \param schIndex index of the school in the array
void schLose(std::vector<School> &schArr, unsigned int schIndex) {
    int loseNum = schArr[schIndex].getSchLoseNum();
    loseNum++;
    schArr[schIndex].setSchLoseNum(loseNum);
}

/// increase the tie number of the school
/// \param schArr school array
/// \param schIndex index of the school in the array
void schTie(std::vector<School> &schArr, unsigned int schIndex) {
    int tieNum = schArr[schIndex].getSchTieNum();
    tieNum++;
    schArr[schIndex].setSchTieNum(tieNum);
}

// manipulating penArr
/// increase the number committed of the current penalty
/// \param penArr penalty array
/// \param penName name of the current panelty
/// \return (meaningless, just to determinate the function)
bool accuPen(std::vector<Penalty> &penArr, std::string penName) {
    for (unsigned int i = 0; i < penArr.size(); i++){
        std::string curPenName = penArr[i].getPenName();
        if (curPenName == penName){
            int curPenNum = penArr[i].getPenNum();
            curPenNum ++;
            penArr[i].setPenNum(curPenNum);
            return true;
        }
    }
    Penalty newPen(penName);
    penArr.push_back(newPen);
    return true;
}

// sorting
/// sorting the school array with --team_stats instructed
/// \param firSch first school
/// \param secSch second school
/// \return a bool value to indicate the sequence should followed
bool schFromTopper(School firSch, School secSch) {
    double firWinPer = firSch.getWinPer();
    double secWinPer = secSch.getWinPer();
    if (firWinPer > secWinPer) {     // comparing win percentage
        return true;
    }
    if (firWinPer == secWinPer) {
        int firGoalNum = firSch.getSchGoalNum();
        int secGoalNum = secSch.getSchGoalNum();
        if (firGoalNum > secGoalNum) {       // comparing goal number
            return true;
        }
        if (firGoalNum == secGoalNum) {
            std::string firName = firSch.getSchName();
            std::string secName = secSch.getSchName();
            if (firName < secName) {     // comparing alpha
                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}

/// sorting the school array with --player_stats instructed
/// \param firStud first student
/// \param secStud second student
/// \return a bool to indicate the sequence should followed
bool studFromTopper(Student firStud, Student secStud) {
    int firGoalAndAss = firStud.getStudGoalNum() + firStud.getStudAssistNum();
    int secGoalAndAss = secStud.getStudGoalNum() + secStud.getStudAssistNum();
    if (firGoalAndAss > secGoalAndAss) {
        return true;
    }
    if (firGoalAndAss == secGoalAndAss) {
        int firPen = firStud.getStudPenNum();
        int secPen = secStud.getStudPenNum();
        if (firPen < secPen) {
            return true;
        }
        if (firPen == secPen) {
            std::string firName = firStud.getStudName();
            std::string secName = secStud.getStudName();
            if (firName < secName) {
                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}

/// sorting the penalty array from greatest committed number, than the alphabetical order
/// \param firPen first penalty
/// \param secPen second penalty
/// \return a bool value to indicate the sequence should followed
bool penFromTopper(Penalty firPen, Penalty secPen) {
    int firPenNum = firPen.getPenNum();
    int secPenNum = secPen.getPenNum();
    if (firPenNum > secPenNum) {
        return true;
    }
    if (firPenNum == secPenNum) {
        std::string firPenName = firPen.getPenName();
        std::string secPenName = secPen.getPenName();
        if (firPenName < secPenName) {
            return true;
        }
        return false;
    }
    return false;
}

int main(int argc, char *argv[]) {
    std::ifstream in_str(argv[1]);
    if (in_str.good()) {
        std::string x;
        std::vector<Student> studArr;   // An array storing student objects
        std::vector<School> schArr;     // An array storing school objects
        std::vector<Penalty> penArr;    // An array storing penalty objects
        while (in_str >> x) {
            // skip date
            for (int i = 0; i < 7; i++) {
                in_str >> x;
            }
            while (x != "FINAL" && x != "OVERTIME") {
                if (x == "PERIOD") {
                    in_str >> x;    // skip
                    in_str >> x;

                } else {
                    std::string schName;
                    in_str >> schName;
                    std::string event;
                    in_str >> event;
                    std::string studName;
                    in_str >> studName;
                    if (event == "goal") {   // when score
                        unsigned int studIndex = getStudIndex(studArr, studName, schName);
                        studGoal(studArr, studIndex);
                        unsigned int schIndex = getSchIndex(schArr, schName);
                        schGoal(schArr, schIndex);
                        in_str >> x;
                        if (x == "(") {      // accumulate assistance students
                            in_str >> x;
                            while (x != ")") {
                                std::string assStudName;
                                assStudName = x;
                                unsigned int assStudIndex = getStudIndex(studArr, assStudName, schName);
                                studAssist(studArr, assStudIndex);
                                in_str >> x;
                            }
                        }
                        in_str >> x;
                    } else if (event == "penalty") {
                        if (studName != "BENCH") {
                            unsigned int studIndex = getStudIndex(studArr, studName, schName);
                            studPen(studArr, studIndex);
                        }
                        unsigned int schIndex = getSchIndex(schArr, schName);
                        schPen(schArr, schIndex);
                        in_str >> x;    // skip
                        in_str >> x;
                        accuPen(penArr, x);
                        in_str >> x;
                    }
                }
            }
            if (x == "OVERTIME") {
                in_str >> x;
                while (x != "FINAL") {
                    std::string schName;
                    in_str >> schName;
                    std::string event;
                    in_str >> event;
                    std::string studName;
                    in_str >> studName;
                    if (event == "goal") {   // when score
                        unsigned int studIndex = getStudIndex(studArr, studName, schName);
                        studGoal(studArr, studIndex);
                        unsigned int schIndex = getSchIndex(schArr, schName);
                        schGoal(schArr, schIndex);
                        in_str >> x;
                        if (x == "(") {      // accumulate assistance students
                            in_str >> x;
                            while (x != ")") {
                                std::string assStudName;
                                assStudName = x;
                                unsigned int assStudIndex = getStudIndex(studArr, assStudName, schName);
                                studAssist(studArr, assStudIndex);
                                in_str >> x;
                            }
                        }
                        in_str >> x;
                    } else if (event == "penalty") {
                        if (studName != "BENCH") {
                            unsigned int studIndex = getStudIndex(studArr, studName, schName);
                            studPen(studArr, studIndex);
                        }
                        unsigned int schIndex = getSchIndex(schArr, schName);
                        schPen(schArr, schIndex);
                        in_str >> x;    // skip
                        in_str >> x;
                        accuPen(penArr, x);
                        in_str >> x;
                    }
                }
            }
            if (x == "FINAL") {
                std::string firSch;
                std::string firSchScore;
                in_str >> firSch;
                in_str >> firSchScore;
                std::string secSch;
                std::string secSchScore;
                in_str >> secSch;
                in_str >> secSchScore;
                unsigned int firSchIndex = getSchIndex(schArr, firSch);
                unsigned int secSchIndex = getSchIndex(schArr, secSch);
                if (firSchScore > secSchScore) {
                    schWin(schArr, firSchIndex);
                    schLose(schArr, secSchIndex);
                } else if (secSchScore > firSchScore) {
                    schWin(schArr, secSchIndex);
                    schLose(schArr, firSchIndex);
                } else {
                    schTie(schArr, firSchIndex);
                    schTie(schArr, secSchIndex);
                }
            }
        }
        std::ofstream out_str(argv[2]);
        if (out_str.good()) {
            std::string outType = argv[3];
            if (outType == "--team_stats") {
                std::sort(schArr.begin(), schArr.end(), schFromTopper);
                unsigned int teamNameWidth = 14;
                unsigned int teamWinWidth = 0;
                unsigned int teamLoseWidth = 4;
                unsigned int teamTieWidth = 4;
                unsigned int teamWinPerWidth = 7;
                unsigned int teamGoalWidth = 7;
                unsigned int teamPenWidth = 11;
                for (unsigned int i = 0; i < schArr.size(); i++) {
                    unsigned int curNameWidth = schArr[i].getSchName().size() + 2;
                    teamNameWidth = std::max(curNameWidth, teamNameWidth);

                    unsigned int curWinWidth = std::to_string(schArr[i].getSchWinNum()).size();
                    teamWinWidth = std::max(curWinWidth, teamWinWidth);

                    unsigned int curLoseWidth = std::to_string(schArr[i].getSchLoseNum()).size() + 2;
                    teamLoseWidth = std::max(curLoseWidth, teamLoseWidth);

                    unsigned int curTieWidth = std::to_string(schArr[i].getSchTieNum()).size() + 2;
                    teamTieWidth = std::max(curTieWidth, teamTieWidth);

                    unsigned int curGoalWidth = std::to_string(schArr[i].getSchGoalNum()).size() + 2;
                    teamGoalWidth = std::max(curGoalWidth, teamGoalWidth);

                    unsigned int curPenWidth = std::to_string(schArr[i].getSchPenNum()).size() + 2;
                    teamPenWidth = std::max(curPenWidth, teamPenWidth);
                }
                out_str << std::left << std::setw(teamNameWidth) << "Team Name";
                out_str << std::right << std::setw(teamWinWidth) << "W";
                out_str << std::right << std::setw(teamLoseWidth) << "L";
                out_str << std::right << std::setw(teamTieWidth) << "T";
                out_str << std::right << std::setw(teamWinPerWidth) << "Win%";
                out_str << std::right << std::setw(teamGoalWidth) << "Goals";
                out_str << std::right << std::setw(teamPenWidth) << "Penalties" << std::endl;

                for (unsigned int i = 0; i < schArr.size(); i++) {
                    out_str << std::left << std::setw(teamNameWidth) << schArr[i].getSchName();
                    out_str << std::right << std::setw(teamWinWidth) << schArr[i].getSchWinNum();
                    out_str << std::right << std::setw(teamLoseWidth) << schArr[i].getSchLoseNum();
                    out_str << std::right << std::setw(teamTieWidth) << schArr[i].getSchTieNum();
                    out_str << std::right << std::setw(teamWinPerWidth) << std::fixed << std::setprecision(2)
                            << schArr[i].getWinPer();
                    out_str << std::right << std::setw(teamGoalWidth) << schArr[i].getSchGoalNum();
                    out_str << std::right << std::setw(teamPenWidth) << schArr[i].getSchPenNum();
                    out_str << std::endl;
                }

            } else if (outType == "--player_stats") {
                std::sort(studArr.begin(), studArr.end(), studFromTopper);
                unsigned int playNameWidth = 17;
                unsigned int playTeamWidth = 13;
                unsigned int playGoalWidth = 5;
                unsigned int playAssWidth = 9;
                unsigned int playPenWidth = 11;
                for (unsigned int i = 0; i < studArr.size(); i++) {
                    unsigned int curNameWidth = studArr[i].getStudName().size() + 2;
                    playNameWidth = std::max(curNameWidth, playNameWidth);

                    unsigned int curTeamWidth = studArr[i].getStudSch().size() + 2;
                    playTeamWidth = std::max(curTeamWidth, playTeamWidth);

                    unsigned int curGoalWidth = std::to_string(studArr[i].getStudPenNum()).size() + 2;
                    playGoalWidth = std::max(curGoalWidth, playGoalWidth);

                    unsigned int curAssWidth = std::to_string(studArr[i].getStudAssistNum()).size() + 2;
                    playAssWidth = std::max(curAssWidth, playAssWidth);

                    unsigned int curPenWidth = std::to_string(studArr[i].getStudPenNum()).size() + 2;
                    playPenWidth = std::max(curPenWidth, playPenWidth);
                }
                out_str << std::left << std::setw(playNameWidth) << "Player Name";
                out_str << std::left << std::setw(playTeamWidth) << "Team";
                out_str << std::right << std::setw(playGoalWidth) << "Goals";
                out_str << std::right << std::setw(playAssWidth) << "Assists";
                out_str << std::right << std::setw(playPenWidth) << "Penalties" << std::endl;

                for (unsigned int i = 0; i < studArr.size(); i++) {
                    out_str << std::left << std::setw(playNameWidth) << studArr[i].getStudName();
                    out_str << std::left << std::setw(playTeamWidth) << studArr[i].getStudSch();
                    out_str << std::right << std::setw(playGoalWidth) << studArr[i].getStudGoalNum();
                    out_str << std::right << std::setw(playAssWidth) << studArr[i].getStudAssistNum();
                    out_str << std::right << std::setw(playPenWidth) << studArr[i].getStudPenNum();
                    out_str << std::endl;
                }
            } else if (outType == "--custom_stats") {
                std::sort(penArr.begin(), penArr.end(), penFromTopper);
                unsigned int penNameWidth = 14;
                unsigned int penNumWidth = 18;
                for (unsigned int i=0; i < penArr.size(); i++){
                    unsigned int curPenNameWidth = penArr[i].getPenName().size() + 2;
                    penNameWidth = std::max(curPenNameWidth, penNameWidth);

                    unsigned int curPenNumWidth = std::to_string(penArr[i].getPenNum()).size() + 2;
                    penNumWidth = std::max(curPenNumWidth, penNumWidth);
                }
                out_str << std::left << std::setw(penNameWidth) << "Penalty Name";
                out_str << std::right << std::setw(penNumWidth) << "Number Committed";
                out_str << std::endl;

                for (unsigned int i=0; i < penArr.size(); i++){
                    out_str << std::left << std::setw(penNameWidth) << penArr[i].getPenName();
                    out_str << std::right << std::setw(penNumWidth) << penArr[i].getPenNum();
                    out_str << std::endl;
                }
            }
        } else {
            std::cerr << "Can't open " << argv[2] << "to read" << std::endl;
            exit(1);
        }
    } else {
        std::cerr << "Can't open " << argv[1] << "to read" << std::endl;
    }
    return 0;
}