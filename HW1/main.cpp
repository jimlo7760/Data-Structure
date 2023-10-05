#include <iostream>
#include <fstream>
#include <vector>
#include <string>

/// function used to deal with long text in full-justify mode
/// \param x input string
/// \param lineArr array containing the strings that will be assigned in the current line
/// \param lineSize the designated size of each line
/// \param textLen the total length of the texts in the current line
/// \param midLines lines in the middle part
void long_text_full(std::string &x, std::vector<std::string> &lineArr, unsigned int lineSize, unsigned int &textLen,
                    std::string &midLines) {
    if (!lineArr.empty()) {         /// there are numbers in the array that should be arranged as flush_left mode before dealing with long text
        std::string lastSpace(lineSize - textLen - (lineArr.size() - 1), ' ');
        for (unsigned int i = 0; i < lineArr.size(); i++) {
            midLines += (lineArr[i] + ' ');
        }
        midLines += lastSpace + "|\n| ";
        lineArr.clear();
    }
    while (x.size() > lineSize) {
        midLines += x.substr(0, lineSize - 1) + "- |\n| ";
        x = x.substr(lineSize - 1, x.size() - lineSize + 1);
    }
    lineArr.push_back(x);
    textLen = x.size();
}

/// function used to deal with long text in left_flush mode
/// \param x input string
/// \param lineSize the designated size of each line
/// \param curSize size of the current line
/// \param midLines lines in the middle part
void long_text_left(std::string &x, unsigned int lineSize, unsigned int &curSize, std::string &midLines) {
    if (curSize > 0) {
        std::string restSpace(lineSize - curSize, ' ');
        midLines += (restSpace + " |\n| ");
    }
    while (x.size() > lineSize) {
        midLines += x.substr(0, lineSize - 1) + "- |\n| ";
        x = x.substr(lineSize - 1, x.size() - lineSize + 1);
    }
    midLines += "| " + x + ' ';
    curSize = x.size() + 1;
}

/// function used to deal with long text in right_flush mode
/// \param x input string
/// \param lineSize the designated size of each line
/// \param curSize the size of the current line
/// \param midLines liens in the middle part
/// \param lineTemp temporary store the middle part of the current line
void long_text_right(std::string &x, unsigned int lineSize, unsigned int &curSize, std::string &midLines,
                     std::string lineTemp) {
    if (curSize > 0) {
        std::string restSpace(lineSize - curSize, ' ');
        midLines += (restSpace + lineTemp + " |\n| ");
    }
    while (x.size() > lineSize) {
        midLines += x.substr(0, lineSize - 1) + "- |\n| ";
        x = x.substr(lineSize - 1, x.size() - lineSize + 1);
    }
    lineTemp = x;
    curSize = x.size();
}

/// function of flush_left mode
/// \param x input string
/// \param curSize size of the current line
/// \param lineSize the designated size of each line
/// \param midLines lines in the middle part
void flush_left(std::string &x, unsigned int &curSize, unsigned int lineSize, std::string &midLines) {
    if (x.size() > lineSize) {
        long_text_left(x, lineSize, curSize, midLines);
    } else {
        if (curSize + x.size() > lineSize) {
            if (curSize - lineSize == 1) {
                midLines += ("|\n| " + x + ' ');
            } else {
                std::string restSpace(lineSize - curSize, ' ');
                midLines += (restSpace + " |" + "\n" + "| " + x + ' ');
            }
            curSize = (x.size() + 1);
        } else {
            midLines += (x + ' ');
            curSize += (x.size() + 1);
        }
    }
}

/// function of flush_right mode
/// \param x input string
/// \param curSize size of the current line
/// \param lineSize the designated size of each line
/// \param lineTemp temporary store the middle part of the current line
/// \param midLines lines in the middle part
void flush_right(std::string &x, unsigned int &curSize, unsigned int lineSize, std::string &lineTemp,
                 std::string &midLines) {
    if (x.size() > lineSize) {
        long_text_right(x, lineSize, curSize, midLines, lineTemp);
    } else {
        if (curSize + x.size() >= lineSize) {
            if (lineSize - curSize >= 0) {
                std::string restSpace(lineSize - curSize, ' ');
                midLines += (restSpace + lineTemp + " |" + "\n" + "| ");
            } else {
                midLines += (lineTemp + " |\n| ");
            }
            lineTemp = x;
            curSize = x.size();
        } else {
            lineTemp += (' ' + x);
            curSize += (x.size() + 1);
        }
    }

}

/// function of fully_justify mode
/// \param x input string
/// \param lineSize size of the current line
/// \param lineArr words in the current line as a vector
/// \param textLen total text length of the current line
/// \param midLines lines in the middle part
void fully_justify(std::string &x, unsigned int lineSize, std::vector<std::string> &lineArr, unsigned int &textLen, std::string &midLines){
    if (x.size() > lineSize) {
        long_text_full(x, lineArr, lineSize, textLen, midLines);
    } else {
        if (textLen + lineArr.size() + x.size() > lineSize) {
            unsigned int oriSpace = (lineSize - textLen) / (lineArr.size() - 1);
            unsigned int extSpace = (lineSize - textLen) % (lineArr.size() - 1);
            for (unsigned int i = 0; i < lineArr.size() - 1; i++) {
                if (extSpace > 0) {
                    std::string curGap(oriSpace + 1, ' ');
                    midLines += (lineArr[i] + curGap);
                    extSpace--;
                } else {
                    std::string curGap(oriSpace, ' ');
                    midLines += (lineArr[i] + curGap);
                }
            }
            midLines += lineArr[lineArr.size() - 1] + " |\n| ";
            lineArr.clear();
            lineArr.push_back(x);
            textLen = x.size();
        } else {
            lineArr.push_back(x);
            textLen += x.size();
        }
    }
}

int main(int argc, char *argv[]) {
    std::ifstream in_str(argv[1]);
    if (in_str.good()) {
        std::string x;
        unsigned int lineSize = atoi(argv[3]);
        unsigned int curSize = 0;
        std::string start_line(lineSize + 4, '-');      /* first line & last line */
        std::string midLines = "| ";
        std::string flushType(argv[4]);
        if (flushType == "flush_left") {
            while (in_str >> x) {
                flush_left(x, curSize, lineSize, midLines);
            }
            std::string restSpace(lineSize - curSize, ' ');
            midLines += (restSpace + " |");
        } else if (flushType == "flush_right") {
            std::string lineTemp;
            while (in_str >> x) {
                flush_right(x, curSize, lineSize, lineTemp, midLines);
            }
            std::string restSpace(lineSize - curSize, ' ');
            midLines += (restSpace + lineTemp + " |");
        } else if (flushType == "full_justify") {
            std::vector<std::string> lineArr;
            unsigned int textLen = 0;
            while (in_str >> x) {
                fully_justify(x, lineSize, lineArr, textLen, midLines);
            }
            std::string lastSpace(lineSize - textLen - (lineArr.size() - 1), ' ');
            for (unsigned int i = 0; i < lineArr.size(); i++) {
                midLines += (lineArr[i] + ' ');
            }
            midLines += lastSpace + "|";
        }
        std::ofstream out_str(argv[2]);
        if (out_str.good()) {
            out_str << start_line << "\n" << midLines << "\n" << start_line;
        } else {
            std::cerr << "Can't open " << argv[2] << "to read" << std::endl;
            exit(1);
        }
    } else {
        std::cerr << "Can't open " << argv[1] << "to write" << std::endl;
        exit(1);
    }
    return 0;
}
