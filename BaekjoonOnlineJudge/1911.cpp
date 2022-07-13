#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int N, L; cin >> N >> L;
    vector<pii> ponds;

    for (int i = 0; i < N; ++i) {
        int L, R; cin >> L >> R;
        ponds.push_back({L, R});
    }

    sort(ponds.begin(), ponds.end(), [](const pii a, const pii b) -> bool {
        return a.first < b.first;
    });

    // cover 까지는 잘 덮어져있음
    int answer = 0, cover = -1;
    for (int i = 0; i < N; ++i) {
        cover = max(cover, ponds[i].first);

        while (cover < ponds[i].second) {
            cover += L;
            ++answer;
        }
    }

    cout << answer << "\n";

    return 0;
}