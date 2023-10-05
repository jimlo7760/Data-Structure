#include <iostream>

int main() {
    int x = 10, y = 15;
    int *a = &x;
    std::cout << x << " " << y << std::endl;
    int *b = &y;
    *a = x * *b;
    std::cout << x << " " << y << std::endl;
    std::cout << b << std::endl;
    int* c = b;
    // b => y, c => b
    // therefore c => y
    std::cout << c << std::endl;
    *c = 25;
    std::cout << x << " " << y << std::endl;
}
