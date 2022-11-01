// internet checksum for error correction and detection.
// Created by:  Reehan
#include "iostream"
#include "string"
#include "vector"
#include "algorithm"
#include "cmath"
using namespace std;
int main() {
    string data;
    cout << "Enter the data: ";
    cin >> data;
    int n = data.length();
    int m = ceil(log2(n));
    int r = pow(2, m) - n - 1;
    string data1 = data;
    for (int i = 0; i < r; i++) {
        data1 += '0';
    }
    vector<string> v;
    for (int i = 0; i < m; i++) {
        string s = "";
        for (int j = 0; j < pow(2, i); j++) {
            for (int k = 0; k < pow(2, m - i - 1); k++) {
                s += '0';
            }
            for (int k = 0; k < pow(2, m - i - 1); k++) {
                s += '1';
            }
        }
        v.push_back(s);
    }
    string s = "";
    for (int i = 0; i < n + r; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            sum += (v[j][i] - '0') * (data1[i] - '0');
        }
        s += (sum % 2) + '0';
    }
    reverse(s.begin(), s.end());
    cout << "Checksum: " << s << endl;
    cout << "Enter the received data: ";
    string data2;
    cin >> data2;
    string s1 = "";
    for (int i = 0; i < n + r; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            sum += (v[j][i] - '0') * (data2[i] - '0');
        }
        s1 += (sum % 2) + '0';
    }
    reverse(s1.begin(), s1.end());
    cout << "Checksum: " << s1 << endl;
    if (s1 == s) {
        cout << "No error" << endl;
    } else {
        cout << "Error" << endl;
    }
    return 0;
}
