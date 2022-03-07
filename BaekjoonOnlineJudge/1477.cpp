#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m, l; cin >> n >> m >> l;
    vector<int> pos;
    for (int i = 0; i < n; ++i) {
        int k; cin >> k;
        pos.push_back(k);
    }

    pos.push_back(0);
    pos.push_back(l);
    sort(pos.begin(), pos.end());

    int lo = 1, hi = pos.back() - 1;
    int answer = 0;

    // val 구간을 최대 길이로 건설하고자 할 때 필요한 추가 휴게소의 수
    auto get_cnt = [&](const int val) -> int {
        int ret = 0, cur = 0, pos_idx = 0;
        for (int i = 1; i < pos.size(); ++i) {
            int d = pos[i] - pos[i - 1];
            ret += d / val;
            if (d % val ==0) --ret;
        }
        return ret;
    };

    while (lo <= hi) {
        int mid = (lo + hi) / 2;

        // 최대 간격을 mid로 계산했을 때, 필요한 최대 휴게소의 수 <= 지을 수 있는 최대 휴게소의 수
        // => 구간을 더 짧게 해서 휴게소를 건설해볼 수 있다.
        if (get_cnt(mid) <= m) {
            answer = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    cout << answer << "\n";
    return 0;
}