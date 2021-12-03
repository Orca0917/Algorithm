/*
 * author: 0917jong
 * date: 2021-12-04
 */

#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;
struct dt {
    int from, to, cost;
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, c, m; cin >> n >> c >> m; // 마을의 수, 트럭 용량, 보내는 박스 정보의 수
    vector<dt> a(m);
    vector<int> capacity(n + 1);
    for (auto &e : a) cin >> e.from >> e.to >> e.cost;
    sort(a.begin(), a.end(), [](const dt &a, const dt &b) {
        return a.to < b.to;
    });
    fill(capacity.begin(), capacity.end(), c);
    int answer = 0, current = 0;
    for (int i = 0; i < m; ++i) {
        int here = a[i].from;
        int mVal = capacity[here];
        
        // 가야하는 길 중 최소.
        for (int j = here; j < a[i].to; ++j) {
            mVal = min(mVal, capacity[j]);
        }
        mVal = min(mVal, a[i].cost);
        for (int j = here; j < a[i].to; ++j) capacity[j] -= mVal;
        answer += mVal;
    }
    cout << answer << "\n";
    return 0;
}