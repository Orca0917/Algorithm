#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

ll N; // 밀키트에 포함된 재료의 수
vector<ll> L; // 재료의 유통기한
vector<ll> S; // 재료의 부패속도
vector<ll> O; // 재료의 중요도
ll G; // 세균의 최대 수
ll K; // 제거할 수 있는 재료의 수

bool canDo(ll x) {
    vector<ll> bug(N, 0);
    vector<ll> bugs;
    ll count = 0;

    for (int i = 0; i < N; ++i) {
        bug[i] = S[i] * max(1LL, x - L[i]);
        if (O[i] == 1)
            bugs.push_back(bug[i]);
        else // 반드시 필요한 재료.
            count += bug[i];
    }

    sort(bugs.begin(), bugs.end());

    int pcnt = K;
    while (!bugs.empty() && pcnt--) {
        bugs.pop_back();
    }

    ll res = count + accumulate(bugs.begin(), bugs.end(), 0LL);
    // cout << ", res = " << res << "\n";

    return res <= G;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> G >> K;

    L.resize(N);
    S.resize(N);
    O.resize(N);

    for (int i = 0; i < N; ++i) {
        cin >> S[i] >> L[i] >> O[i];
    }

    ll down = 0, up = 2 * 1e9;
    ll answer = 0;
    while (down <= up) {
        ll mid = (down + up) / 2;
        // cout << "mid = " << mid << " ";
        if (canDo(mid)) {
            answer = mid;
            down = mid + 1;
        } else 
            up = mid - 1;
    }

    cout << answer << "\n";
    return 0;
}