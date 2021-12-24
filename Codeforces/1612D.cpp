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
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
        ll a, b, x;
        cin >> a >> b >> x;
        bool answer = false;

        while (a && b) {
            if (a > b) swap(a, b);
            if (a == x || b == x) {
                answer = true;
                break;
            }

            if (x <= b && x && x % a == b % a) {
                answer = true;
                break;
            }

            b %= a;
        }

        if (answer) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}