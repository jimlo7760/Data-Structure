#include <iostream>
#include <vector>


int foobar(const std::vector<std::string>& a, int b){
    int answer = 0;
    for (int i= 0; i < a.size(); i+=b){
        answer++;
    }
    return answer;
}

std::vector<int> bar2 (const std::vector<std::string> &a){
    std::vector<int> answer;
    for (int i = 0; i < a.size(); i++){
        answer.push_back(a[i].size());
    }
    return answer;
}

std::vector<std::string> bar3 (const std::vector<int> &a){
    std::vector<std::string> answer;
    for (int i = 0; i < a.size(); i++){
        answer.push_back(std::string(a[i], '+'));
    }
    return answer;
}

int main() {
    std::vector<std::string> strVec(1000000000, "abcccsadflkjlksdjlfk");
    std::vector<int> intVec(100000000, 1);
    foobar(strVec, 1);
    bar2(strVec);
    bar3(intVec);
    return 0;
}
