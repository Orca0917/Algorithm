/**
 * @file problemSolving.cpp
 * @author 0917jong / dbwhdans / killerWhale0917.github.io
 * @brief 
 * @version 0.1
 * @date 2021-12-24
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
        int n, m; cin >> n >> m;
        vector<int> arr(n);
        for (auto &e : arr) cin >> e;

        sort(arr.begin(), arr.end());

        int answer = 0;
        for (int i = 1; i <= m; ++i) {
            answer += arr[n - i - m] / arr[n - i];
        }

        for (int i = 0; i < n - 2 * m; ++i) {
            answer += arr[i];
        }

        cout << answer << "\n";
    }
    return 0;
}