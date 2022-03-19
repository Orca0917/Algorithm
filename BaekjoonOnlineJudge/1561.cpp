#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // input
    ll n, m; cin >> n >> m;
    vector<ll> cool_time(m); // cool_time[i] = i 번째 놀이기구 쿨타임
    for (ll &e : cool_time) cin >> e;

    // mid 분 동안 몇 명의 아이가 탑승?
    auto is_possible = [&](const ll mid) -> bool {
        ll cnt = m;
        for (ll e : cool_time) {
            cnt += mid / e;
        }
        return cnt >= n;

    };

    // return last minute
    ll lo = 1, hi = 2e11, answer = 1;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2LL;
        if (is_possible(mid)) {
            answer = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    // last minute - 1 분 까지 탑승한 학생의 수
    ll bef_cnt = m;
    for (ll e : cool_time) {
        bef_cnt += (answer - 1) / e;
    }

    // last minute에 타야하는 학생의 수
    ll left_person = n - bef_cnt;

    // last minute에는 비어있는 놀이기구만 탑승 가능
    ll cnts = 0, result = 1;
    for (int i = 0; i < m; ++i) {
        if (answer % cool_time[i] == 0) {
            ++cnts;
            result = i + 1;
            if (cnts == left_person) break;
        }
    }

    if (n < m) result = n;
    cout << result << "\n";

    return 0;
}