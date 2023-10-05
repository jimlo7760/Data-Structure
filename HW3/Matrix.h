//
// Created by Yinzoen Louh on 2023/2/6.
//

#ifndef HW3_MATRIX_H
#define HW3_MATRIX_H
#include <iostream>

class Matrix {
public:
    typedef unsigned int sizeType;
    // Contructors
    Matrix();
    Matrix(sizeType rowNum, sizeType colNum, double fillVal);
    Matrix(const Matrix& secMatrix);
    // Destructor:
    ~Matrix() {clear();}
    void clear();

    // Operators
    bool operator==(const Matrix& vOther) const;
    bool operator!=(const Matrix& vOther) const;
    Matrix& operator=(const Matrix& rhsVec);

    // Accessor
    const bool get(sizeType rowNum, sizeType colNum, double& getEle) const;
    // Modifier
    bool set(sizeType rowNum, sizeType colNum, double setEle);

    // Public member functions
    const sizeType& num_rows() const {return rowSize;}
    const sizeType& num_cols() const {return colSize;}
    void multiply_by_coefficient(int coe);
    bool swap_row(sizeType sour, sizeType tar);
    void transpose();
    const bool add(const Matrix& b);
    const bool subtract(const Matrix& b);
    double* get_row(sizeType rowNum);
    double* get_col(sizeType colNum);
    Matrix* quarter();
    void resize(sizeType rowNum, sizeType colNum, double filVal);
private:
    double** data;
    sizeType rowSize;
    sizeType colSize;
};

// Output operator
std::ostream& operator<< (std::ostream& out, const Matrix& m);

#endif //HW3_MATRIX_H
