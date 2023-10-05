#include <iostream>
#include <cstdlib>

int main() {
    int seed;
    std::cin >> seed;
    srand(seed);
    for (int i = 0; i < 6; i++){
        int num = rand() % 200;

    }
    return 0;
}
