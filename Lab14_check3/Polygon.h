//
// Created by Yinzoen Louh on 2023/4/26.
//

#ifndef LAB14_POLYGON_H
#define LAB14_POLYGON_H

#include <iostream>
#include <vector>
#include "utilities.h"

class Polygon {
public:
    // Contructors
    Polygon() {}

    Polygon(const std::string aName, const std::vector<Point> &pointVec) {
        (this->name) = aName;
        (this->points) = pointVec;
    }
    // Accessors
    virtual std::string getName(){
        return (this -> name);
    }
    bool HasAllEqualSides(){
        for (unsigned int i = 2; i < points.size(); i++){
            Point a = points[i - 2];
            Point b = points[i - 1];
            Point c = points[i];
            double lengthA = DistanceBetween(a, b);
            double lengthB = DistanceBetween(b, c);
            if (!EqualSides(lengthA, lengthB)){
                return false;
            }
        }
        return true;
    }

    bool HasAllEqualAngles(){
        for (unsigned int i = 2; i < points.size(); i++){
            Point a = points[i - 2];
            Point b = points[i - 1];
            Point c = points[i];

        }
    }

    bool HasARightAngle(){
        for (unsigned int i = 2; i < points.size(); i++){
            Point a = points[i - 2];
            Point b = points[i - 1];
            Point c = points[i];
            double ang = Angle(a, b, c);
            if (RightAngle(ang)){
                return true;
            }
        }
        return false;
    }
    //other functions


protected:
    std::string name;
    std::vector<Point> points;
};

class Triangle : public Polygon {
public:
    // Constructors:
    Triangle() {}

    Triangle(const std::string aName, const std::vector<Point> &pointVec) {
        if (pointVec.size() != 3) {
            throw 1;
        }
        (this->name) = aName;
        (this->points) = pointVec;
    }
};

class RightTriangle : public Triangle{
public:
    RightTriangle() {}
    RightTriangle(const std::string aName, const std::vector<Point> &pointVec){
        bool hasRight = Polygon::HasARightAngle();
        if (!hasRight){
            throw 1;
        }
        (this->name) = aName;
        (this->points) = pointVec;
    }
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle() {}

    IsoscelesTriangle(const std::string aName, const std::vector<Point> &pointVec) {
        if (pointVec.size() != 3) {
            throw 1;
        }

        Point a = pointVec[0];
        Point b = pointVec[1];
        Point c = pointVec[2];
        double lengthA = DistanceBetween(a, b);
        double lengthB = DistanceBetween(a, c);
        double lengthC = DistanceBetween(b, c);
        if (lengthA == lengthB || lengthA == lengthC || lengthB == lengthC) {
            (this->name) = aName;
            (this->points) = pointVec;
        } else {
            throw 1;
        }
    }
};


class IsoscelesRightTriangle : public IsoscelesTriangle{
public:
    IsoscelesRightTriangle() {}
    IsoscelesRightTriangle(const std::string aName, const std::vector<Point> &pointVec){
        bool hasRight = Polygon::HasARightAngle();
        if (!hasRight){
            throw 1;
        }
        (this->name) = aName;
        (this->points) = pointVec;
    }
};

class EquilateralTriangle : public IsoscelesTriangle {
public:
    EquilateralTriangle() {}

    EquilateralTriangle(const std::string aName, const std::vector<Point> &pointVec) {
        if (pointVec.size() != 3) {
            throw 1;
        }

        bool eq = Polygon::HasAllEqualSides();
        if (!eq){
            throw 1;
        }
        (this->name) = aName;
        (this->points) = pointVec;
    }
};

class Quadrilateral : public Polygon {
public:
    Quadrilateral() {}

    Quadrilateral(const std::string aName, const std::vector<Point> &pointVec) {
        if (pointVec.size() != 4) {
            throw 1;
        }
        (this->name) = aName;
        (this->points) = pointVec;
    }
};

class Rectangle : public Quadrilateral {
public:
    Rectangle() {}

    Rectangle(const std::string aName, const std::vector<Point> &pointVec) {
        if (pointVec.size() != 4) {
            throw 1;
        }
        Point a = pointVec[0];
        Point b = pointVec[1];
        Point c = pointVec[2];
        Point d = pointVec[3];
        double lengthA = DistanceBetween(a, b);
        double lengthB = DistanceBetween(b, c);
        double lengthC = DistanceBetween(c, d);
        double lengthD = DistanceBetween(d, a);
        bool created = false;
        if (lengthA == lengthB) {
            if (lengthC == lengthD) {
                (this->name) = aName;
                (this->points) = pointVec;
                created = true;
            }
        } else {
            if (lengthB == lengthC) {
                if (lengthD == lengthA) {
                    (this->name) = aName;
                    (this->points) = pointVec;
                    created = true;
                }
            }
        }
        if (!created) {
            throw 1;
        }
    }
};

class Square : public Rectangle {
public:
    Square() {}

    Square(const std::string aName, const std::vector<Point> &pointVec) {
        if (pointVec.size() != 4) {
            throw 1;
        }
        Point a = pointVec[0];
        Point b = pointVec[1];
        Point c = pointVec[2];
        Point d = pointVec[3];
        double lengthA = DistanceBetween(a, b);
        double lengthB = DistanceBetween(b, c);
        double lengthC = DistanceBetween(c, d);
        double lengthD = DistanceBetween(d, a);
        if (lengthA != lengthB || lengthA != lengthC || lengthA != lengthD || lengthB != lengthC ||
            lengthB != lengthD || lengthC != lengthD) {
            throw 1;
        }
        (this -> name) = aName;
        (this -> points) = pointVec;
    }
};


#endif //LAB14_POLYGON_H
