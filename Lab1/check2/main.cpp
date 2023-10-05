#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    int res = atoi(argv[1]);
    for(int i=2; i < argc; i++){
        res = res * atoi(argv[i]);
    }
    std::cout << "product of integers: " << res << std::endl;
}
