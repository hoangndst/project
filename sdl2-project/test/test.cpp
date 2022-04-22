#include <bits/stdc++.h>
#include <fstream>
using namespace std;
int main() {
    
    fstream file;
    file.open("../test/map.dat");

    int arr[29][50];

    for (int i = 0; i < 29; i++) {
        for (int j = 0; j < 50; j++) {
            int tmp; file >> tmp;
            arr[i][j] = tmp;
        }
    }
    for (int i = 0; i < 29; i++) {
        for (int j = 0; j < 50; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
