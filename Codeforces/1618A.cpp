/**
 * @file problemSolving.cpp
 * @author 0917jong / dbwhdans / killerWhale0917.github.io
 * @brief 
 * @version 0.1
 * @date 2021-12-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
        vector<int> arr(7), answer(3);
        for (auto &e : arr) cin >> e;
        sort(arr.begin(), arr.end());

        answer[0] = arr[0];
        answer[1] = arr[1];

        if (answer[0] + answer[1] == arr[2]) answer[2] = arr[3];
        else answer[2] = arr[2];

        for (auto e : answer) cout << e << " ";
        cout << "\n";
    }
    return 0;
}