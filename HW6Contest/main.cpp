#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>


/// check if the character to the left match the word
/// \param curWord the target word gonna search
/// \param tarMatrix target grid that is being searched
/// \param curCol current column
/// \param curRow current row
/// \return true: when character matches; false: when character unmatch
bool
checkWordHorLeft(std::list<std::string> curWord, std::vector<std::vector<std::string > > &tarMatrix, int curCol,
                 int curRow) {
    int wordSize = curWord.size();
    if (wordSize == 0) {
        return true;
    }
    std::string curChar = curWord.front();
    curWord.pop_front();
    if (curChar == tarMatrix[curRow][curCol]) {
        return checkWordHorLeft(curWord, tarMatrix, --curCol, curRow);
    }
    return false;
}

/// check if the character to the right match the word
/// \param curWord the target word gonna search
/// \param tarMatrix target grid that is being searched
/// \param curCol current column
/// \param curRow current row
/// \return true: when character matches; false: when character unmatch
bool checkWordHorRight(std::list<std::string> curWord, std::vector<std::vector<std::string > > &tarMatrix, int curCol,
                       int curRow) {
    int wordSize = curWord.size();
    if (wordSize == 0) {
        return true;
    }
    std::string curChar = curWord.front();
    curWord.pop_front();
    if (curChar == tarMatrix[curRow][curCol]) {
        return checkWordHorRight(curWord, tarMatrix, ++curCol, curRow);
    }
    return false;
}

/// check if the character upward match the word
/// \param curWord the target word gonna search
/// \param tarMatrix target grid that is being searched
/// \param curCol current column
/// \param curRow current row
/// \return true: when character matches; false: when character unmatch
bool checkWordVerUp(std::list<std::string> curWord, std::vector<std::vector<std::string > > &tarMatrix, int curCol,
                    int curRow) {
    int wordSize = curWord.size();
    if (wordSize == 0) {
        return true;
    }
    std::string curChar = curWord.front();
    curWord.pop_front();
    if (curChar == tarMatrix[curRow][curCol]) {
        return checkWordVerUp(curWord, tarMatrix, curCol, --curRow);
    }
    return false;
}

/// check if the character downward match the word
/// \param curWord the target word gonna search
/// \param tarMatrix target grid that is being searched
/// \param curCol current column
/// \param curRow current row
/// \return true: when character matches; false: when character unmatch
bool checkWordVerDown(std::list<std::string> curWord, std::vector<std::vector<std::string > > &tarMatrix, int curCol,
                      int curRow) {
    int wordSize = curWord.size();
    if (wordSize == 0) {
        return true;
    }
    std::string curChar = curWord.front();
    curWord.pop_front();
    if (curChar == tarMatrix[curRow][curCol]) {
        return checkWordVerDown(curWord, tarMatrix, curCol, ++curRow);
    }
    return false;
}

/// check if the character downward along the main diagonal match the word
/// \param curWord the target word gonna search
/// \param tarMatrix target grid that is being searched
/// \param curCol current column
/// \param curRow current row
/// \return true: when character matches; false: when character unmatch
bool
checkWordDiaMainDown(std::list<std::string> curWord, std::vector<std::vector<std::string > > &tarMatrix, int curCol,
                     int curRow) {
    int wordSize = curWord.size();
    if (wordSize == 0) {
        return true;
    }
    std::string curChar = curWord.front();
    curWord.pop_front();
    if (curChar == tarMatrix[curRow][curCol]) {
        return checkWordDiaMainDown(curWord, tarMatrix, ++curCol, ++curRow);
    }
    return false;
}

/// check if the character upward along the main diagonal match the word
/// \param curWord the target word gonna search
/// \param tarMatrix target grid that is being searched
/// \param curCol current column
/// \param curRow current row
/// \return true: when character matches; false: when character unmatch
bool checkWordDiaMainUp(std::list<std::string> curWord, std::vector<std::vector<std::string > > &tarMatrix, int curCol,
                        int curRow) {
    int wordSize = curWord.size();
    if (wordSize == 0) {
        return true;
    }
    std::string curChar = curWord.front();
    curWord.pop_front();
    if (curChar == tarMatrix[curRow][curCol]) {
        return checkWordDiaMainUp(curWord, tarMatrix, --curCol, --curRow);
    }
    return false;
}

/// check if the character downward along the sub diagonal match the word
/// \param curWord the target word gonna search
/// \param tarMatrix target grid that is being searched
/// \param curCol current column
/// \param curRow current row
/// \return true: when character matches; false: when character unmatch
bool checkWordDiaSubDown(std::list<std::string> curWord, std::vector<std::vector<std::string > > &tarMatrix, int curCol,
                         int curRow) {
    int wordSize = curWord.size();
    if (wordSize == 0) {
        return true;
    }
    std::string curChar = curWord.front();
    curWord.pop_front();
    if (curChar == tarMatrix[curRow][curCol]) {
        return checkWordDiaSubDown(curWord, tarMatrix, --curCol, ++curRow);
    }
    return false;
}

/// check if the character upward along the sub diagonal match the word
/// \param curWord the target word gonna search
/// \param tarMatrix target grid that is being searched
/// \param curCol current column
/// \param curRow current row
/// \return true: when character matches; false: when character unmatch
bool checkWordDiaSubUp(std::list<std::string> curWord, std::vector<std::vector<std::string > > &tarMatrix, int curCol,
                       int curRow) {
    int wordSize = curWord.size();
    if (wordSize == 0) {
        return true;
    }
    std::string curChar = curWord.front();
    curWord.pop_front();
    if (curChar == tarMatrix[curRow][curCol]) {
        return checkWordDiaSubUp(curWord, tarMatrix, ++curCol, --curRow);
    }
    return false;
}

/// Helper function to start the word checking
/// \param colNum number of column of the grid
/// \param rowNum number of row of the grid
/// \param curWord given word
/// \param tarMatrix grid is searched
/// \return true: if the grid contain the word; false: if the grid not contain the word
bool checkWordDriver(int colNum, int rowNum, std::string curWord, std::vector<std::vector<std::string > > &tarMatrix) {
    // split the word into a vector
    std::list<std::string> wordLst;
    for (unsigned int i = 0; i < curWord.size(); i++) {
        std::string tempStr(1, curWord[i]);
        wordLst.push_back(tempStr);
    }
    for (int i = 0; i < rowNum; i++) {
        for (int j = 0; j < colNum; j++) {
            int wordSize = curWord.size();
            bool haveFound = false;
            // left word search
            if (j - wordSize >= -1) {
                haveFound = haveFound || checkWordHorLeft(wordLst, tarMatrix, j, i);
            }
            // right word search
            if (j + wordSize <= colNum) {
                haveFound = haveFound || checkWordHorRight(wordLst, tarMatrix, j, i);
            }
            // upward word search
            if (i - wordSize >= -1) {
                haveFound = haveFound || checkWordVerUp(wordLst, tarMatrix, j, i);
            }
            // downward word search
            if (i + wordSize <= rowNum) {
                haveFound = haveFound || checkWordVerDown(wordLst, tarMatrix, j, i);
            }
            // upward search along the main diagonal
            if (j - wordSize >= -1 && i - wordSize >= -1) {
                haveFound = haveFound || checkWordDiaMainUp(wordLst, tarMatrix, j, i);
            }
            // downward search along the main diagonal
            if (j + wordSize <= colNum && i + wordSize <= rowNum) {
                haveFound = haveFound || checkWordDiaMainDown(wordLst, tarMatrix, j, i);
            }
            // downward search along the sub diagonal
            if (j - wordSize >= -1 && i + wordSize <= rowNum) {
                haveFound = haveFound || checkWordDiaSubDown(wordLst, tarMatrix, j, i);
            }
            // upward search along the sub diagonal
            if (j + wordSize <= colNum && i - wordSize >= -1) {
                haveFound = haveFound || checkWordDiaSubUp(wordLst, tarMatrix, j, i);
            }
            if (haveFound) {
                return true;
            }
        }
    }
    return false;
}

/// create a empty matrix, initial all slots as "0"
/// \param rowNum number of rows need to generate
/// \param colNum number of columns need to generate
/// \return the created grid
std::vector<std::vector<std::string> > createEmpMatrix(int rowNum, int colNum) {
    std::vector<std::vector<std::string > > temp;
    for (int i = 0; i < rowNum; i++) {
        std::vector<std::string> tempRow(colNum, "0");
        temp.push_back(tempRow);
    }
    return temp;
}

/// Add the word horizontally
/// \param curWord word that is being added
/// \param curMatrix Grid that is adding to
/// \param curRow current row number
/// \param curCol current column number
/// \return true: if the word can be added successfully; false: if the word cannot be added successfully
bool addWordHor(std::string curWord, std::vector<std::vector<std::string> > &curMatrix, int curRow, int curCol) {
    int wordSize = curWord.size();
    unsigned int tempCmp = curCol + wordSize;
    if (tempCmp > curMatrix[curRow].size()) {
        return false;
    }
    for (unsigned int i = 0; i < curWord.size(); i++) {
        unsigned int curColPos = curCol + i;
        std::string tempStr(1, curWord[i]);
        if (curMatrix[curRow][curColPos] == "0" || curMatrix[curRow][curColPos] == tempStr) {
            curMatrix[curRow][curColPos] = tempStr;
        } else {
            // undo the modifications on the matrix
            for (int j = i - 1; j >= 0; j--) {
                int restoreColPos = curCol + j;
                curMatrix[curRow][restoreColPos] = "0";
            }
            return false;
        }
    }
    return true;
}

/// Add the word vertically
/// \param curWord word that is being added
/// \param curMatrix Grid that is adding to
/// \param curRow current row number
/// \param curCol current column number
/// \return true: if the word can be added successfully; false: if the word cannot be added successfully
bool addWordVer(std::string curWord, std::vector<std::vector<std::string> > &curMatrix, int curRow, int curCol) {
    int wordSize = curWord.size();
    unsigned int tempCmp = curRow + wordSize;
    if (tempCmp> curMatrix.size()) {
        return false;
    }
    for (unsigned int i = 0; i < curWord.size(); i++) {
        unsigned int curRowPos = curRow + i;
        std::string tempStr(1, curWord[i]);
        if (curMatrix[curRowPos][curCol] == "0" || curMatrix[curRowPos][curCol] == tempStr) {
            curMatrix[curRowPos][curCol] = tempStr;
        } else {
            // undo the modifications on the matrix
            for (int j = i - 1; j >= 0; j--) {
                int restoreRowPos = curRow + j;
                curMatrix[restoreRowPos][curCol] = "0";
            }
            return false;
        }
    }
    return true;
}

/// Add the word along the main diagonal
/// \param curWord word that is being added
/// \param curMatrix Grid that is adding to
/// \param curRow current row number
/// \param curCol current column number
/// \return true: if the word can be added successfully; false: if the word cannot be added successfully
bool addWordDiaMain(std::string curWord, std::vector<std::vector<std::string> > &curMatrix, int curRow, int curCol) {
    unsigned int wordSize = curWord.size();
    unsigned int tempComp1 = curRow + wordSize;
    unsigned int tempComp2 = curCol + wordSize;
    if (tempComp1 > curMatrix.size() || tempComp2 > curMatrix[curRow].size()) {
        return false;
    }
    for (unsigned int i = 0; i < curWord.size(); i++) {
        unsigned int curRowPos = curRow + i;
        unsigned int curColPos = curCol + i;
        std::string tempStr(1, curWord[i]);
        if (curMatrix[curRowPos][curColPos] == "0" || curMatrix[curRowPos][curColPos] == tempStr) {
            curMatrix[curRowPos][curColPos] = tempStr;
        } else {
            // undo the modifications on the matrix
            if (i != 0){
                for (int j = i - 1; j >= 0; j--) {
                    unsigned int restoreRowPos = curRow + j;
                    unsigned int restoreColPos = curCol + j;
                    curMatrix[restoreRowPos][restoreColPos] = "0";
                }
            }
            return false;
        }
    }
    return true;
}

/// Add the word along the sub diagonal
/// \param curWord word that is being added
/// \param curMatrix Grid that is adding to
/// \param curRow current row number
/// \param curCol current column number
/// \return true: if the word can be added successfully; false: if the word cannot be added successfully
bool addWordDiaSub(std::string curWord, std::vector<std::vector<std::string> > &curMatrix, int curRow, int curCol) {
    unsigned int wordSize = curWord.size();
    int tempCmp1 = curRow - wordSize;
    unsigned int tempCmp2 = curCol + wordSize;
    if (tempCmp1 < -1 || tempCmp2 > curMatrix[curRow].size()) {
        return false;
    }
    for (unsigned int i = 0; i < curWord.size(); i++) {
        unsigned int curRowPos = curRow - i;
        unsigned int curColPos = curCol + i;
        std::string tempStr(1, curWord[i]);
        if (curMatrix[curRowPos][curColPos] == "0" || curMatrix[curRowPos][curColPos] == tempStr) {
            curMatrix[curRowPos][curColPos] = tempStr;
        } else {
            // undo the modifications on the matrix
            for (int j = i - 1; j >= 0; j--) {
                unsigned int restoreRowPos = curRow - j;
                unsigned int restoreColPos = curCol + j;
                curMatrix[restoreRowPos][restoreColPos] = "0";
            }
            return false;
        }
    }
    return true;
}

/// Recursive function to add the word
/// \param reqWord Vector of words that need to include in the grid
/// \param colNum number of columns of the grid
/// \param rowNum number of rows of the grid
/// \param res Vector of grids that stores all the possible grids
/// \param curCol current column
/// \param curRow current row
/// \param tempMatrix matrix that is currently being processed with
/// \return true: the grid has been filled with all required words; false: the grid has not been filled with all required words.
bool addWordRec(std::list<std::string> reqWord, int colNum, int rowNum,
                std::vector<std::vector<std::vector<std::string> > > &res,
                std::vector<std::vector<std::string> > tempMatrix) {
    if (reqWord.size() == 0) {
        // grid creation is finished
        return true;
    }
    std::vector<std::vector<std::string> > curMatrix = tempMatrix;
    std::string curWord = reqWord.front();
    reqWord.pop_front();
    // check if the grid has included the word
    // include: no need to add; not include: need to add.
    bool wordExist = checkWordDriver(colNum, rowNum, curWord, tempMatrix);
    if (!wordExist) {
        for (int k = 0; k <= 1; k++) {
            for (int i = 0; i < rowNum; i++) {
                for (int j = 0; j < colNum; j++) {

                    // check if the word can be added horizontally
                    bool horReturn = addWordHor(curWord, tempMatrix, i, j);
                    if (horReturn) {
                        bool addRet = addWordRec(reqWord, colNum, rowNum, res, tempMatrix);
                        if (addRet) {
                            res.push_back(tempMatrix);
                        }
                    }
                    tempMatrix = curMatrix;

                    // check if the word can be added vertically
                    bool verReturn = addWordVer(curWord, tempMatrix, i, j);
                    if (verReturn) {
                        bool addRet = addWordRec(reqWord, colNum, rowNum, res, tempMatrix);
                        if (addRet) {
                            res.push_back(tempMatrix);
                        }
                    }
                    tempMatrix = curMatrix;

                    // check if the word can be added along the main diagonal
                    bool mainDiaReturn = addWordDiaMain(curWord, tempMatrix, i, j);
                    if (mainDiaReturn) {
                        bool addRet = addWordRec(reqWord, colNum, rowNum, res, tempMatrix);
                        if (addRet) {
                            res.push_back(tempMatrix);
                        }
                    }
                    tempMatrix = curMatrix;

                    // check if the word can be added the sub diagonal
                    bool subDiaReturn = addWordDiaSub(curWord, tempMatrix, i, j);
                    if (subDiaReturn) {
                        bool addRet = addWordRec(reqWord, colNum, rowNum, res, tempMatrix);
                        if (addRet) {
                            res.push_back(tempMatrix);
                        }
                    }
                }
            }
            // reverse the current word to enumerate other possibilities
            std::reverse(curWord.begin(), curWord.end());
        }
    }
    return false;
}

/// Helper function to search the add-word function
/// \param reqWord list of all words required to be in the grid
/// \param colNum number of columns of the grid
/// \param rowNum number of rows of the grid
/// \param res vector storing all the generated grids
void addWordDriver(std::list<std::string> &reqWord, int colNum, int rowNum,
                   std::vector<std::vector<std::vector<std::string> > > &res) {
    std::vector<std::vector<std::string> > tempMatrix = createEmpMatrix(rowNum, colNum);
    addWordRec(reqWord, colNum, rowNum, res, tempMatrix);
}

/// Fill all the "0" in the grid with all possibilities
/// \param res vector storing all the generated grids
/// \param rowNum number of rows in the grid
/// \param colNum number of columns in the grid
/// \param curRow current row
/// \param curCol current vector
/// \param tempVec current grid that is processing with
/// \param forbidWord vector of forbidden words in the grid
/// \return true: if the current grid is valid and has added to the grid; false: the current word is invalid.
bool fillGrid(std::vector<std::vector<std::vector<std::string> > > &res, int rowNum, int colNum, int curRow, int curCol,
              std::vector<std::vector<std::string> > tempVec, std::vector<std::string> &forbidWord) {
    if (curRow == rowNum) {
        // check if the grid have existed
        for (unsigned int i = 0; i < res.size(); i++) {
            if (tempVec == res[i]) {
                return false;
            }
        }

        // check if the current grid include forbid words
        for (unsigned int i = 0; i < forbidWord.size(); i++) {
            std::string curWord = forbidWord[i];
            bool wordExist = checkWordDriver(colNum, rowNum, curWord, tempVec);
            if (wordExist) {
                return false;
            }
        }

        res.push_back(tempVec);
//        for (int i = 0; i < tempVec.size(); i++){
//            for (int j = 0; j < tempVec[i].size(); j++){
//                std::cout << tempVec[i][j] << " ";
//            }
//            std::cout << std::endl;
//        }
        return true;
    }
    // change line
    if (curCol == colNum) {
        curCol = 0;
        curRow++;
        return fillGrid(res, rowNum, colNum, curRow, curCol, tempVec, forbidWord);
    }
    // an empty has been found
    if (tempVec[curRow][curCol] == "0") {
        // list all the possible letters to fill
        for (int i = 97; i <= 122; i++) {
            char charAscii = static_cast<char>(i);
            std::string strAsc(1, charAscii);
            tempVec[curRow][curCol] = strAsc;
            fillGrid(res, rowNum, colNum, curRow, curCol + 1, tempVec, forbidWord);
        }
    }
    // go to next slot if the current slot is not empty
    return fillGrid(res, rowNum, colNum, curRow, curCol + 1, tempVec, forbidWord);
}

/// erase the grids that contains forbidden words
/// \param res vectors storing all grids
/// \param forbidWord vector storing all forbidden words
/// \param rowNum number of rows of the grid
/// \param colNum number of columns of the grid
void cleanForbidGrid(std::vector<std::vector<std::vector<std::string> > > &res, std::vector<std::string> &forbidWord,
                     int rowNum, int colNum) {
    std::vector<std::vector<std::vector<std::string> > >::iterator it = res.begin();
    while (it != res.end()) {
        std::vector<std::vector<std::string> > curVec = (*it);
        bool wordExist = false;
        for (unsigned int i = 0; i < forbidWord.size(); i++) {
            std::string curWord = forbidWord[i];
            wordExist = checkWordDriver(colNum, rowNum, curWord, curVec);
            if (wordExist) {
                break;
            }
        }
        if (wordExist) {
            res.erase(it);
        } else {
            it++;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "Invalid input" << std::endl;
        return 0;
    }
    std::ifstream in_str(argv[1]);
    if (in_str.good()) {
        // list to store the requiring words
        std::list<std::string> reqWord;
        // list to store the forbidden words
        std::vector<std::string> forbidWord;
        std::string col = "0";
        in_str >> col;
        int colNum = std::stoi(col);
        std::string row = "0";
        in_str >> row;
        int rowNum = std::stoi(row);
        std::string x;
        std::string word;
        while (in_str >> x) {
            in_str >> word;
            if (x == "+") {
                reqWord.push_back(word);
            } else {
                forbidWord.push_back(word);
            }
        }
        std::vector<std::vector<std::vector<std::string> > > res;
        addWordDriver(reqWord, colNum, rowNum, res);

        // search every grid, erase the grid containing forbidden word
        cleanForbidGrid(res, forbidWord, rowNum, colNum);

        // remove duplicate grids
        std::vector<std::vector<std::vector<std::string> > >::iterator iti = res.begin();
        while (iti != res.end()) {
            std::vector<std::vector<std::vector<std::string> > >::iterator itj = ++iti;
            iti--;
            while (itj != res.end()) {
                if ((*iti) == (*itj)) {
                    res.erase(itj);
                } else {
                    itj++;
                }
            }
            iti++;
        }

        // search every grid, check and fill the empty space to generate a new matrix
        for (unsigned int i = 0; i < res.size(); i++) {
            std::vector<std::vector<std::string> > curGrid = res[i];
            fillGrid(res, rowNum, colNum, 0, 0, curGrid, forbidWord);
        }

        // search every grid, erase the grid containing forbidden word
        cleanForbidGrid(res, forbidWord, rowNum, colNum);

        // empty the grids containing "0"
        std::vector<std::vector<std::vector<std::string> > >::iterator it = res.begin();
        while (it != res.end()) {
            std::vector<std::vector<std::string> > curVec = (*it);
            bool hasZero = false;
            for (unsigned int i = 0; i < curVec.size(); i++) {
                for (unsigned int j = 0; j < curVec[i].size(); j++) {
                    if (curVec[i][j] == "0") {
                        hasZero = true;
                    }
                }
            }
            if (hasZero) {
                res.erase(it);
            } else {
                break;
            }
        }

        // output to the file
        std::ofstream out_str(argv[2]);
        if (out_str.good()) {
            if (res.size() == 0) {
                out_str << "No solutions found";
            } else {
                std::string numSol(argv[3]);
                if (numSol != "one_solution") {
                    out_str << res.size() << " solution(s)" << std::endl;
                }
                for (unsigned int i = 0; i < res.size(); i++) {
                    out_str << "Board: " << std::endl;
                    std::vector<std::vector<std::string> > curVec = res[i];
                    for (unsigned int j = 0; j < curVec.size(); j++) {
                        out_str << "  ";
                        for (unsigned int k = 0; k < curVec[j].size(); k++) {
                            out_str << curVec[j][k];
                        }
                        out_str << std::endl;
                    }
                    if (numSol == "one_solution") {
                        break;
                    }
                }
            }
        }
    }
}
