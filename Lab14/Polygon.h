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
    std::string getName(){
        return (this -> name);
    }
protected:
    virtual bool HasAllEqualSides(){
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
    // Modifiers

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

class EquilateralTriangle : public IsoscelesTriangle {
public:
    EquilateralTriangle() {}

    EquilateralTriangle(const std::string aName, const std::vector<Point> &pointVec) {
        if (pointVec.size() != 3) {
            throw 1;
        }

        Point a = pointVec[0];
        Point b = pointVec[1];
        Point c = pointVec[2];
        double lengthA = DistanceBetween(a, b);
        double lengthB = DistanceBetween(a, c);
        double lengthC = DistanceBetween(b, c);
        if (!EqualSides(lengthA, lengthB) || !EqualSides(lengthA, lengthC) || !EqualSides(lengthB, lengthC)) {
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
        if (EqualSides(lengthA, lengthB)) {
            if (EqualSides(lengthC, lengthD)) {
                (this->name) = aName;
                (this->points) = pointVec;
                created = true;
            }
        } else {
            if (EqualSides(lengthB, lengthD)) {
                if (EqualSides(lengthA, lengthC)) {
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
