#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace  std;

//#define path "test.txt"

string decToHex(int high, int low) {
	const std::string hex = "0123456789ABCDEF";
	stringstream ss;
	ss << hex[high >> 4] << hex[high & 0xf];
	ss << hex[low >> 4] << hex[low & 0xf];
	return ss.str();
}

int main(int argc, char* argv[]) {
	string str, tmp = "";
	//path = argv[1];
	ifstream file1(argv[1], ios::in);
	vector<int> l, r;
	while (getline(file1, tmp)) {
		str += tmp;
	}
	cout << str << endl;

	int size = str.size();
	int len = 0;
	cout << "\nconvert to hexadecimal";
	for (int i = 0; i < size - 1; i += 2) {
		l.push_back((int)str[i]);
		r.push_back((int)str[i + 1]);
		cout << "0x" << decToHex(l[len], r[len]) << " ";
		len++;
	}
	if (size % 2 == 1) {
		l.push_back((int)str[size - 1]);
		r.push_back(0);
		cout << "0x" << decToHex(l[len], r[len]) << " ";
		len++;
	}
	cout << endl;
	int low = 0, t = 0; 
	for (int i = 0; i < len; i++) {
		low += r[i];
		if (low > 255) {
			t += (low / 256);
			low %= 256;
		}
	}

	int high = t, t2 = 0;  
	for (int i = 0; i < len; i++) {
		high += l[i];
		if (high > 255) {
			t2 += (high / 256);
			high %= 256;
		}
	}
	while (t2 != 0) {
		low += t2;
		t = 0;
		t2 = 0;
		if (low > 255) {
			t = low / 256;
			low %= 256;
		}
		high += t;
		if (high > 255) {
			t2 = high / 256;
			high %= 256;
		}
	}

	cout << "check_sum: " << decToHex(high, low) << endl<<endl;

	file1.close();
}
