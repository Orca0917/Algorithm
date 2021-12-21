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
        int n; cin >> n;
        vector<string> arr(n - 2);
        for (auto &e : arr) cin >> e;

        string answer = "";
        answer += arr[0][0];

        for (int i = 1; i < n - 2; ++i) {
            if (arr[i][0] != arr[i - 1][1]) {
                answer += arr[i - 1][1];
                answer += arr[i][0];
            }
            else
                answer += arr[i][0];
        }
        answer += arr[n - 3][1];

        if (answer.length() < n) answer += 'a';
        cout << answer << "\n";
    }
    return 0;
}