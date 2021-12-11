#include <bits/stdc++.h>
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k; cin >> n >> k;

    vector<int> a(n);
    for (auto &e: a) cin >> e;

    sort(a.begin(), a.end());

    priority_queue<pii> pq;
    for (int i = 1; i < n; ++i) {
        int diff = a[i] - a[i - 1];
        pq.push({diff, i - 1});
    }

    int cnt = 0;
    vector<int> div;
    while (!pq.empty() && cnt < k - 1) {
        div.push_back(pq.top().second);
        pq.pop(); ++cnt;
    }
    div.push_back(n - 1);

    sort(div.rbegin(), div.rend());

    int prev = a[0], answer = 0;

    a.push_back(a.back());
    for (int i = 0; i < n; ++i) {
        if (i == div.back()) {
            int diff = a[i] - prev;
            answer += diff;
            div.pop_back();
            prev = a[i + 1];
        }
    }

    cout << answer << "\n";

    return 0;
}