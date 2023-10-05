#include <iostream>

void compute_squares(int* a, int* b, int n){
    int* i;
    for (i = a; i < a + n ; ++i){
        *b = *i * *i;
        ++b;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    int a[10];
    for (int i=0; i<=9; i++){
        a[i] = i;
    }
    int b[10];
    compute_squares(a, b, 10);
    for (int i=0; i<=9; i++){
        std::cout << b[i] << std::endl;
    }
}
