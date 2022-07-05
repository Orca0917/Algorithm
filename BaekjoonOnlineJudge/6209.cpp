#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int d, n, m; // 탈출구 위치, 돌섬의 수, 제거 횟수
vector<int> islands;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // input
    cin >> d >> n >> m;
    islands.resize(n);
    for (int &e : islands) cin >> e;

    // sorting -> parametric search
    islands.push_back(d);
    sort(islands.begin(), islands.end());

    // calc func.
    auto get_jumps = [&](const int val) -> int {
        int jump_cnt = 0, current = 0;

        for (int e : islands) {
            if (e - current < val) ++jump_cnt;
            else current = e;
        }

        return jump_cnt;
    };

    // parametric search
    int lo = 0, hi = 1e9, answer = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int jump_cnt = get_jumps(mid);

        if (jump_cnt <= m) {
            answer = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }   
    }   

    cout << answer << "\n";

    return 0;
}