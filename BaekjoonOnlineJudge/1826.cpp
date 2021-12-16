#include <bits/stdc++.h>
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n; // 주유소의 개수
    vector<pii> oilBank(n);
    for (int i = 0; i < n; ++i) cin >> oilBank[i].first >> oilBank[i].second;
    sort(oilBank.begin(), oilBank.end());

    int dest, oil; cin >> dest >> oil; // 도착지점과 처음 기름의 양

    priority_queue<int> pq;
    
    int bankIdx = 0, answer = 0;
    while (bankIdx < n && oil < dest) {
        // 주유소 찾기
        while (bankIdx < n && oilBank[bankIdx].first <= oil) {
            pq.push(oilBank[bankIdx++].second);
        }

        // 해당 주유소에서 주유 시작
        if (!pq.empty()) {
            ++answer;
            oil += pq.top();
            pq.pop();
        } else
            break;
    }

    if (oil < dest) cout << "-1\n";
    else cout << answer << "\n";

    return 0;
}