//
// Created by Yinzoen Louh on 2023/2/6.
//

#include "Matrix.h"

// Constructors
//default constructor
Matrix::Matrix() {
    rowSize = 0;
    colSize = 0;
    data = NULL;
}
// row / column constructor
Matrix::Matrix(sizeType rowNum, sizeType colNum, double fillVal) {
    if (rowNum == 0 || colNum == 0) {    // as either dimension = 0, create a 0*0 Matrix
        data = NULL;
        rowSize = 0;
        colSize = 0;
        return;
    }
    data = new double *[rowNum];
    for (sizeType i = 0; i < rowNum; i++) {
        data[i] = new double[colNum];
        for (sizeType j = 0; j < colNum; j++) {
            data[i][j] = fillVal;
        }
    }
    rowSize = rowNum;
    colSize = colNum;
}
// copy constructor
Matrix::Matrix(const Matrix & secMatrix){
    if(secMatrix.num_rows() == 0 || secMatrix.num_cols() == 0){
        data = NULL;
        rowSize = 0;
        colSize = 0;
        return;
    }
    data = new double *[secMatrix.num_rows()];
    for (sizeType i = 0; i < secMatrix.num_rows(); i++){
        data[i] = new double[secMatrix.num_cols()];
        for (sizeType j = 0; j < secMatrix.num_cols(); j++){
            double ele = 0;
            secMatrix.get(i, j, ele);
            data[i][j] = ele;
        }
    }
    rowSize = secMatrix.num_rows();
    colSize = secMatrix.num_cols();
}

// Destructor
void Matrix::clear() {
    if (data == NULL){
        return;
    }
    for (sizeType i = 0; i < rowSize; i++) {
        delete[] data[i];
    }
    delete[] data;
    rowSize = 0;
    colSize = 0;
}

// Operators
// equal operator
bool Matrix::operator==(const Matrix &vOther) const {
    if (rowSize != vOther.num_rows() || colSize != vOther.num_cols()) {
        return false;
    }
    for (sizeType i = 0; i < rowSize; i++) {
        for (sizeType j = 0; j < colSize; j++) {
            double otherEle = 0;
            vOther.get(i, j, otherEle);
            if (data[i][j] != otherEle) {
                return false;
            }
        }
    }
    return true;
}
// non-equal operator
bool Matrix::operator!=(const Matrix &vOther) const {
    if (rowSize != vOther.num_rows() || colSize != vOther.num_cols()) {
        return true;
    }
    for (sizeType i = 0; i < rowSize; i++) {
        for (sizeType j = 0; j < colSize; j++) {
            double otherEle = 0;
            vOther.get(i, j, otherEle);
            if (data[i][j] != otherEle) {
                return true;
            }
        }
    }
    return false;
}
// assign operator
Matrix& Matrix::operator=(const Matrix& rhsVec){
    if (this != &rhsVec){
        this->clear();
        if(rhsVec.num_rows() == 0 || rhsVec.num_cols() == 0){
            this->data = NULL;
            this->rowSize = 0;
            this->colSize = 0;
        }else{
            this->data = new double *[rhsVec.num_rows()];
            for (sizeType i = 0; i < rhsVec.num_rows(); i++){
                data[i] = new double[rhsVec.num_cols()];
                for (sizeType j = 0; j < rhsVec.num_cols(); j++){
                    double ele = 0;
                    rhsVec.get(i, j, ele);
                    data[i][j] = ele;
                }
            }
            this->rowSize = rhsVec.num_rows();
            this->colSize = rhsVec.num_cols();
        }
    }
    return *this;
}

// Accessor
const bool Matrix::get(sizeType rowNum, sizeType colNum, double &getEle) const {
    if (rowNum >= rowSize || colNum >= colSize) {
        return false;
    }
    getEle = data[rowNum][colNum];
    return true;
}

// Modifier
bool Matrix::set(sizeType rowNum, sizeType colNum, double setEle) {
    if (rowNum >= rowSize || colNum >= colSize) {
        return false;
    }
    data[rowNum][colNum] = setEle;
    return true;
}

// Public member function
void Matrix::multiply_by_coefficient(int coe) {
    for (sizeType i = 0; i < rowSize; i++) {
        for (sizeType j = 0; j < colSize; j++) {
            data[i][j] *= coe;
        }
    }
}

bool Matrix::swap_row(sizeType sour, sizeType tar) {
    if (sour >= rowSize || tar >= rowSize) {
        return false;
    }
    double tempSwap = 0;
    for (sizeType i = 0; i < colSize; i++) {
        tempSwap = data[sour][i];
        data[sour][i] = data[tar][i];
        data[tar][i] = tempSwap;
    }
    return true;
}

void Matrix::transpose() {
    // copy to tempData
    double **tempData = new double *[colSize];
    for (sizeType i = 0; i < colSize; i++) {
        tempData[i] = new double[rowSize];
        for (sizeType j = 0; j < rowSize; j++) {
            tempData[i][j] = data[j][i];
        }
    }
    sizeType tempColSize = colSize;
    sizeType tempRowSize = rowSize;
    // delete data
    this->clear();
    // re-construct data
    rowSize = tempColSize;
    colSize = tempRowSize;
    data = new double *[rowSize];
    for (sizeType i = 0; i < rowSize; i++) {
        data[i] = new double[colSize];
        for (sizeType j = 0; j < colSize; j++) {
            data[i][j] = tempData[i][j];
        }
    }
    // delete tempData
    for (sizeType i = 0; i < rowSize; i++) {
        delete[] tempData[i];
    }
    delete[] tempData;
}

const bool Matrix::add(const Matrix &b) {
    sizeType bRowSize = b.num_rows();
    sizeType bColSize = b.num_cols();
    if (rowSize != bRowSize || colSize != bColSize) {
        return false;
    }
    for (sizeType i = 0; i < rowSize; i++) {
        for (sizeType j = 0; j < colSize; j++) {
            double bEle = 0;
            b.get(i, j, bEle);
            data[i][j] += bEle;
        }
    }
    return true;
}

const bool Matrix::subtract(const Matrix &b) {
    sizeType bRowSize = b.num_rows();
    sizeType bColSize = b.num_cols();
    if (rowSize != bRowSize || colSize != bColSize) {
        return false;
    }
    for (sizeType i = 0; i < rowSize; i++) {
        for (sizeType j = 0; j < colSize; j++) {
            double bEle = 0;
            b.get(i, j, bEle);
            data[i][j] -= bEle;
        }
    }
    return true;
}

double* Matrix::get_row(sizeType rowNum) {
    if (rowNum >= rowSize) {
        return NULL;
    }
    double *pnter = new double[colSize];
    for (sizeType i = 0; i < colSize; i++) {
        pnter[i] = data[rowNum][i];
    }
    return pnter;
}

double* Matrix::get_col(sizeType colNum) {
    if (colNum >= colSize) {
        return NULL;
    }
    double *pnter = new double[rowSize];
    for (sizeType i = 0; i < rowSize; i++) {
        pnter[i] = data[i][colNum];
    }
    return pnter;
}

Matrix* Matrix::quarter() {
    Matrix* qrdnt = new Matrix[4];  // used to store 4 matrices in order
    if (rowSize % 2 == 0) {
        if (colSize % 2 == 0) {
            qrdnt[0] = Matrix(rowSize / 2, colSize / 2, 0);
            qrdnt[1] = Matrix(rowSize / 2, colSize / 2, 0);
            qrdnt[2] = Matrix(rowSize / 2, colSize / 2, 0);
            qrdnt[3] = Matrix(rowSize / 2, colSize / 2, 0);
            for (sizeType i = 0; i < rowSize / 2; i++){
                for (sizeType j = 0; j < colSize / 2; j++){
                    double ulEle = 0;
                    this->get(i, j, ulEle);
                    qrdnt[0].set(i, j, ulEle);
                    double urEle = 0;
                    this->get(i, colSize / 2 + j, urEle);
                    qrdnt[1].set(i, j, urEle);
                    double llEle = 0;
                    this->get(rowSize / 2 + i, j, llEle);
                    qrdnt[2].set(i, j, llEle);
                    double lrEle = 0;
                    this->get(rowSize / 2 + i, colSize / 2 + j, lrEle);
                    qrdnt[3].set(i, j, lrEle);
                }
            }

        } else {
            qrdnt[0] = Matrix(rowSize / 2, colSize / 2 + 1, 0);
            qrdnt[1] = Matrix(rowSize / 2, colSize / 2 + 1, 0);
            qrdnt[2] = Matrix(rowSize / 2, colSize / 2 + 1, 0);
            qrdnt[3] = Matrix(rowSize / 2, colSize / 2 + 1, 0);
            for (sizeType i = 0; i < rowSize / 2; i++){
                for (sizeType j = 0; j < colSize / 2 + 1; j++){
                    double ulEle = 0;
                    this->get(i, j, ulEle);
                    qrdnt[0].set(i, j, ulEle);
                    double urEle = 0;
                    this->get(i, colSize / 2 + j, urEle);
                    qrdnt[1].set(i, j, urEle);
                    double llEle = 0;
                    this->get(rowSize / 2 + i, j, llEle);
                    qrdnt[2].set(i, j, llEle);
                    double lrEle = 0;
                    this->get(rowSize / 2 + i, colSize / 2 + j, lrEle);
                    qrdnt[3].set(i, j, lrEle);
                }
            }
        }
    } else {
        if (colSize % 2 == 0) {
            qrdnt[0] = Matrix(rowSize / 2 + 1, colSize / 2, 0);
            qrdnt[1] = Matrix(rowSize / 2 + 1, colSize / 2, 0);
            qrdnt[2] = Matrix(rowSize / 2 + 1, colSize / 2, 0);
            qrdnt[3] = Matrix(rowSize / 2 + 1, colSize / 2, 0);
            for (sizeType i = 0; i < rowSize / 2 + 1; i++){
                for (sizeType j = 0; j < colSize / 2; j++){
                    double ulEle = 0;
                    this->get(i, j, ulEle);
                    qrdnt[0].set(i, j, ulEle);
                    double urEle = 0;
                    this->get(i, colSize / 2 + j, urEle);
                    qrdnt[1].set(i, j, urEle);
                    double llEle = 0;
                    this->get(rowSize / 2 + i, j, llEle);
                    qrdnt[2].set(i, j, llEle);
                    double lrEle = 0;
                    this->get(rowSize / 2 + i, colSize / 2 + j, lrEle);
                    qrdnt[3].set(i, j, lrEle);
                }
            }
        } else {
            qrdnt[0] = Matrix(rowSize / 2 + 1, colSize / 2 + 1, 0);
            qrdnt[1] = Matrix(rowSize / 2 + 1, colSize / 2 + 1, 0);
            qrdnt[2] = Matrix(rowSize / 2 + 1, colSize / 2 + 1, 0);
            qrdnt[3] = Matrix(rowSize / 2 + 1, colSize / 2 + 1, 0);
            for (sizeType i = 0; i < rowSize / 2 + 1; i++){
                for (sizeType j = 0; j < colSize / 2 + 1; j++){
                    double ulEle = 0;
                    this->get(i, j, ulEle);
                    qrdnt[0].set(i, j, ulEle);
                    double urEle = 0;
                    this->get(i, colSize / 2 + j, urEle);
                    qrdnt[1].set(i, j, urEle);
                    double llEle = 0;
                    this->get(rowSize / 2 + i, j, llEle);
                    qrdnt[2].set(i, j, llEle);
                    double lrEle = 0;
                    this->get(rowSize / 2 + i, colSize / 2 + j, lrEle);
                    qrdnt[3].set(i, j, lrEle);
                }
            }
        }
    }
    return qrdnt;
}

void Matrix::resize(sizeType rowNum, sizeType colNum, double filVal) {
    sizeType matRowNum = this->num_rows();      // original row num
    sizeType matColNum = this -> num_cols();    // original column num
    if (rowNum == matRowNum && rowNum == matColNum){
        return;
    }
    double** tempData = new double*[rowNum];
    for (sizeType i = 0; i < rowNum; i++){
        tempData[i] = new double[colNum];
        for (sizeType j = 0; j < colNum; j++){
            if (i < matRowNum && j < matColNum){
                double temp = 0;
                this->get(i, j, temp);
                tempData[i][j] = temp;
            }else{
                tempData[i][j] = filVal;
            }
        }
    }
    this->clear();
    rowSize = rowNum;
    colSize = colNum;
    data = new double* [rowNum];

    for (sizeType i = 0; i < rowNum; i++){
        data[i] = new double[colNum];
        for (sizeType j = 0; j < colNum; j++){
            this->set(i, j, tempData[i][j]);
        }
        delete [] tempData[i];
    }
    delete[] tempData;

}

// Output operator
std::ostream &operator<<(std::ostream &out, const Matrix &m) {
    out << m.num_rows() << " x " << m.num_cols() << " matrix:" << std::endl;
    out << "[";
    for (unsigned int i = 0; i < m.num_rows(); i++) {
        for (unsigned int j = 0; j < m.num_cols(); j++) {
            double getEle = 0;
            m.get(i, j, getEle);
            out << " " << getEle;
        }
        if (i != m.num_rows() - 1){
            out << std::endl;
        }
    }
    out << " ]" << std::endl;
    return out;
}

