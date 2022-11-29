#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<pii> arr;
    for (int i = 0; i < n; ++i) {
        int s, e; cin >> s >> e;
        if (s > e) swap(s, e);
        arr.push_back({s, e});
    }

    int d; cin >> d;
    sort(arr.begin(), arr.end(), [](const pii &a, const pii &b) {
        if (a.second == b.second) return a.first < b.first;
        return a.second < b.second;
    });

    priority_queue<int> pq;
    int answer = 0;

    for (int i = 0; i < n; ++i) {
        if (arr[i].second - arr[i].first > d) continue;
        pq.push(-arr[i].first);
        while (!pq.empty() && -pq.top() < arr[i].second - d) pq.pop();
        answer = max(answer, (int)pq.size());
    }

    cout << answer << "\n";
    return 0;
}