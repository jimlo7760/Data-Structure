#include <iostream>
#include <map>
#include <fstream>

int main(int argc, char* argv[]) {
    std::map<std::string, int> count;
    std::ifstream in_str(argv[1]);
    if (in_str.good()){
        std::string x;
        while (in_str >> x){
            count[x]++;
        }
        int max = 0;
        for (std::map<std::string, int>::iterator it = count.begin(); it != count.end(); ++it){
            if (it -> second > max){
                max = it -> second;
            }
        }
        for (std::map<std::string, int>::iterator it = count.begin(); it != count.end(); ++it){
            if (it -> second == max){
                std::cout << it -> first << std::endl;
            }
        }
    }
}
