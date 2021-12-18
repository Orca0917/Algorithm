/**
 * @file problemSolving.cpp
 * @author 0917jong (killerwhale0917.github.io)
 * @brief 
 * @version 0.1
 * @date 2021-12-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    queue<int> q;
    for (int i = 1; i <= n; ++i) q.push(i);

    vector<int> garbage;

    while (q.size() > 1) {
        int x = q.front(); q.pop();
        garbage.push_back(x);

        x = q.front(); q.pop();
        q.push(x);
    }

    for (auto e : garbage) cout << e << " ";
    cout << q.front() << "\n";

    return 0;
}