// program for implementing the error detection technique for data transfer in unreliable network code using CRC (16-bits) Technique.
#include <iostream>
#include <string.h>

using namespace std;
int main() {
    int i, j ;
    char data[100], div[100], temp[100], quot[100], rem[100], key[30];
    cout << "Enter Data: ";
    cin >> data;
    cout << "Enter Key: ";
    cin >> key;
    int keylen = strlen(key);
    int datalen = strlen(data);
    strcpy(div, key);
    for (i = 0; i < keylen - 1; i++) {
        data[datalen + i] = '0';
    }
    for (i = 0; i < keylen; i++)
        temp[i] = data[i];
    for (i = 0; i < datalen; i++) {
        quot[i] = temp[0];
        if (quot[i] == '0')
            for (j = 0; j < keylen; j++)
                div[j] = '0';
        else
            for (j = 0; j < keylen; j++)
                div[j] = key[j];
        for (j = keylen - 1; j > 0; j--) {
            if (temp[j] == div[j])
                rem[j - 1] = '0';
            else
                rem[j - 1] = '1';
        }
        rem[keylen - 1] = data[i + keylen];
        strcpy(temp, rem);

    }
    strcpy(rem, temp);
    cout << "Remainder is: " << rem << endl;
    for (i = 0; i < keylen - 1; i++)
        data[datalen + i] = rem[i];
    cout << "Final codeword is: " << data << endl;
    cout << "Enter data received: ";
    cin >> data;
    for (i = 0; i < keylen; i++)
        temp[i] = data[i];
    for (i = 0; i < datalen; i++) {
        quot[i] = temp[0];
        if (quot[i] == '0')
            for (j = 0; j < keylen; j++)
                div[j] = '0';
        else
            for (j = 0; j < keylen; j++)
                div[j] = key[j];
        for (j = keylen - 1; j > 0; j--) {
            if (temp[j] == div[j])
                rem[j - 1] = '0';
            else
                rem[j - 1] = '1';
        }
        rem[keylen - 1] = data[i + keylen];
        strcpy(temp, rem);

    }
    strcpy(rem, temp);
    cout << "Remainder is: " << rem << endl;
    for (i = 0; i < keylen - 1; i++)
        if (rem[i] != '0') {
            cout << "Error detected" << endl;
            break;
        }
    if (i == keylen - 1)
        cout << "No error detected" << endl;
    return 0;
}