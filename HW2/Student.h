//
// Created by Yinzoen Louh on 2023/1/23.
//
#include <iostream>

#ifndef HW2_STUDENT_H
#define HW2_STUDENT_H


class Student {
public:
    // Contructors
    Student(std::string aName, std::string aSchName);
    // Accessors
    std::string getStudName() const;
    std::string getStudSch() const;
    int getStudGoalNum() const;
    int getStudAssistNum() const;
    int getStudPenNum() const;
    // Modifiers
    void setStudName(std::string aStudName);
    void setStudSch(std::string aStudSch);
    void setStudGoalNum(int aStudGoalNum);
    void setStudAssistNum(int aStudAssistNum);
    void setStudPenNum(int aStudPenNum);
    //other functions

private:
    std::string name;
    std::string schName;
    int goalNum;
    int assistNum;
    int penNum;
};



#endif //HW2_STUDENT_H
