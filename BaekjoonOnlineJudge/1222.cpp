#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<ll> person_cnt(2'000'001, 0);
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int k; cin >> k;
        person_cnt[k] += 1;
    }

    ll answer = 0;
    for (int team_size = 1; team_size <= 2'000'000; ++team_size) {
        int next_stage = 0;

        for (int j = team_size; j <= 2'000'000; j += team_size) {
            next_stage += person_cnt[j];
        }

        if (next_stage >= 2) answer = max(answer, 1LL * next_stage * team_size);
    }

    cout << answer << "\n";
    return 0;
}