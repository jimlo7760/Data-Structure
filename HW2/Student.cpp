//
// Created by Yinzoen Louh on 2023/1/23.
//

#include "Student.h"

// constructor
Student::Student(std::string aName, std::string aSchName) {
    name = aName;
    schName = aSchName;
    goalNum = 0;
    assistNum = 0;
    penNum = 0;
}

// accessors
std::string Student::getStudName() const{
    return name;
}
std::string Student::getStudSch() const {
    return schName;
}
int Student::getStudGoalNum() const{
    return goalNum;
}
int Student::getStudAssistNum() const {
    return assistNum;
}
int Student::getStudPenNum() const {
    return penNum;
}

// modifiers
void Student::setStudName(std::string aStudName) {
    name = aStudName;
}
void Student::setStudSch(std::string aStudSch) {
    schName = aStudSch;
}
void Student::setStudGoalNum(int aStudGoalNum) {
    goalNum = aStudGoalNum;
}
void Student::setStudAssistNum(int aStudAssistNum) {
    assistNum = aStudAssistNum;
}
void Student::setStudPenNum(int aStudPenNum) {
    penNum = aStudPenNum;
}
