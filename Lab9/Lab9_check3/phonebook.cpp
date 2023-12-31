// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// add a number, name pair to the phonebook
void add(vector<string> &phonebook, int number, string const& name) {
  phonebook[number] = name;     // O(1)
}

// given a phone number, determine who is calling
void identify(const vector<string> & phonebook, int number) {
  if (phonebook[number] == "UNASSIGNED") 
    cout << "unknown caller!" << endl;
  else 
    cout << phonebook[number] << " is calling!" << endl;
}

void add(map<int, string> &phonebook, int number, string const& name){
    phonebook[number] = name;   // O(log(n))
}

void identify(const map<int, string> &phonebook, int number){
    map<int, string>::const_iterator it = phonebook.find(number);
    if (it == phonebook.end()){
        cout << "unknown caller!" << endl;
    }else{
        cout << it -> second << " is calling!" << endl;
    }
}


int main() {
  // create the phonebook; initially all numbers are unassigned
  vector<string> phonebook(10000, "UNASSIGNED");    // O(N) construction

  // add several names to the phonebook
  add(phonebook, 1111, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333, "george");

  // test the phonebook
  identify(phonebook, 2222);
  identify(phonebook, 4444);

  map<int, string> newPhoneBook;
  add(newPhoneBook, 1111111, "ffff");
  add(newPhoneBook, 2222222, "eeeee");
  identify(newPhoneBook, 2222222);
    identify(newPhoneBook, 4444444);
}
