#include <iostream>
#include <vector>

using namespace std;

int triforce(vector<vector<int>> &v, int startR, int endR, int startC, int endC) {
    int topL, topR, bottomL, bottomR;
    if (endR - startR == 1 && endC - startC == 1) {
        topL = v[startR][startC];
        topR = v[startR][endC];
        bottomL = v[endR][startC];
        bottomR = v[endR][endC];
    }
    else {
        int mR = (endR + startR) / 2;
        int mC = (endC + startC) / 2;
        topL = triforce(v, startR, mR, startC, mC);
        topR = triforce(v, startR, mR, mC + 1, endC);
        bottomL = triforce(v, mR + 1, endR, startC, mC);
        bottomR = triforce(v, mR + 1, endR, mC + 1, endC);
    }

    if (topL != 0 && topR != 0 && bottomL != 0 && bottomR == 0) {
        if (topL == topR || topL == bottomL) return topL;
        else if (topR == bottomL) return topR;
    }

    // if bottomR is not 0 or no same number
    return 0;
}

int main() {
    int round = 3;
    while (round--) {
        int n;
        cin >> n;
        vector<vector<int>> v(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> v[i][j];
            }
        }

        // check bottomR are all 0 or not
        bool isAllZero = true;
        for (int i = n/2; i < n; i++) {
            for (int j = n/2; j < n; j++) {
                if (v[i][j] != 0) {
                    isAllZero = false;
                    break;
                }
            }
            if (!isAllZero) break;
        }

        if (isAllZero) cout << triforce(v, 0, n - 1, 0, n - 1) << endl; 
        else cout << 0 << endl;
    }
    
    return 0;
}