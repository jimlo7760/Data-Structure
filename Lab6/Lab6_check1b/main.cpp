#include <iostream>
#include <string>
#include <list>


template <class T>
void print(std::list<T> &data, const std::string &label) {
    std::cout << label << " ";
    for (typename std::list<T>::iterator i = data.begin(); i != data.end(); i++) {
        std::cout << " " << (*i);
    }
    std::cout << std::endl;
}


template <class T>
void reverse(std::list<T> &data) {
    // FILL IN THIS FUNCTION
    int seqOrder = 0;
    for (typename std::list<T>::iterator i = data.begin(); i != data.end(); i++){
        if (seqOrder >= data.size() / 2){
            return;
        }
        int revOrder = 0;
        for (typename std::list<T>::reverse_iterator ri = data.rbegin(); ri != data.rend(); ri++){
            if (seqOrder == revOrder){
                T temp = (*i);
                (*i) = (*ri);
                (*ri) = temp;
                break;
            }else{
                revOrder++;
            }
        }
        seqOrder++;
    }
}


int main() {
    std::list<int> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(5);
    data.push_back(6);
//    data.push_back(7);

    print(data,"before:");
    reverse(data);
    print(data,"after: ");

    std::list<std::string> data2;
    data2.push_back("apple");
    data2.push_back("banana");
    data2.push_back("carrot");
    data2.push_back("date");

    print(data2,"before:");
    reverse(data2);
    print(data2,"after: ");
}
