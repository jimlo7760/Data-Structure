#include <iostream>

int main() {
    int n = 3;
    int *p = new int[n];
    int *temp = new int[2*n];
    int i;
    for (i=0; i < n; ++i){
        temp[i] = p[i];
    }
    delete [] p;
    p = temp;
}
