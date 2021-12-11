#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<pair<int, int>> a;
    
    for (int i = 0; i < n; ++i) {
        int day, cup; cin >> day >> cup;
        a.push_back({day, cup});
    }

    sort(a.begin(), a.end(), [&](const pair<int, int> a, const pair<int, int> b) {
        if (a.first == b.first) {
            return a.second < b.second;
        }
        return a.first < b.first;
    });
    
    int today = a.back().first;

    int answer = 0;
    int index = n - 1;
    
    priority_queue<int> pq;

    while (today > 0) {
        while (index >= 0 && a[index].first >= today) {
            pq.push(a[index].second);
            --index;
        }
        --today;
        if (!pq.empty()) {
            answer += pq.top();
            pq.pop();
        }
    }

    cout << answer << "\n";
    return 0;
}