#include<iostream>

using namespace std;

int main() {
	short a = 0;
	while (true) {
		cout << a << endl;
		a++;
		if (a == 0) {
			cin >> a;
		}
	}
}