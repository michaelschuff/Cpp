#include<iostream>
#include<bitset>

using namespace std;


int main() {
    string frenchToast = "french toast";
    bitset<8> frenchToastBits[12];
    for (int i = 0; i < frenchToastBits.size(); i++) {
        frenchToastBits[i] = new bitset<8> (frenchToast[i]);
        cout << frenchToast[i];
    }
    cout << endl;
}