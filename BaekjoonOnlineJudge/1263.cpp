#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n;
vector<pii> tasks;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // # of tasks
    cin >> n;

    // task duration, task deadline
    tasks.resize(n);
    for (pii &e : tasks) cin >> e.first >> e.second;
    
    sort(tasks.begin(), tasks.end(), [](const pii &a, const pii &b) {
        return a.second > b.second;
    });

    int cur_time = 1e9;
    for (pii &e : tasks) cur_time = min(e.second, cur_time) - e.first;

    cout << (cur_time < 0 ? -1 : cur_time) << "\n";

    return 0;
}