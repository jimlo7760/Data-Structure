#include <iostream>

int calPath(int &x, int &y, int &pathNum){
    if (x == 0 && y == 0){
        return ++pathNum;
    }
    if (x == 0){
        int reducedY = y - 1;
        return calPath(x, reducedY, pathNum);
    }
    if (y == 0){
        int reducedX = x - 1;
        return calPath(reducedX, y, pathNum);
    }
    int reducedX = x - 1;
    int reducedY = y - 1;
    calPath(x, reducedY, pathNum);
    calPath(reducedX, y, pathNum);
    return pathNum;
}
// O(2^x + 2^u)

int main() {
    int x = 2;
    int y = 1;
    int path = 0;
    int ret = calPath(x, y, path);
    std::cout << ret << std::endl;
    return 0;
}
