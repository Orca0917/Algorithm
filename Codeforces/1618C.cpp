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
#define ll unsigned long long
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        vector<ll> arr(n);
        for (auto &e : arr) cin >> e;

        ll gcdVal[2] = {arr[0], arr[1]};
        for (int i = 2; i < n; ++i)
            gcdVal[i % 2] = __gcd(gcdVal[i % 2], arr[i]);

        bool hasAnswer[2] = {true, true};
        for (int i = 0; i < 2; ++i) {
            ll d = gcdVal[i];

            for (int j = i ^ 1; j < n && hasAnswer[i]; j += 2) {
                if (arr[j] % d == 0) hasAnswer[i] = false;
            }
        }

        if (hasAnswer[0] == false && hasAnswer[1] == false)
            cout << "0\n";
        else
            if (hasAnswer[0]) cout << gcdVal[0] << "\n";
            else cout << gcdVal[1] << "\n";
    }
    return 0;
}