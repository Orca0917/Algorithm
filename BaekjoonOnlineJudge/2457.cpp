/*
 * author: 0917jong
 * date: 2021-12-06
 */

#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

struct Flower {
    int openM, openD, closeM, closeD;
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<pii> a;
    for (int i = 0; i < n; ++i) {
        int m1, d1, m2, d2; cin >> m1 >> d1 >> m2 >> d2;
        a.push_back({m1 * 100 + d1, m2 * 100 + d2});
    }

    // 시작날을 기준으로 정렬
    // 시작날이 동일하다면, 더 일찍 죽는 꽃을 앞으로 배열.
    sort(a.begin(), a.end(), [&](const pii a, const pii b) {
        if (a.first == b.first) return a.second < b.second;
        return a.first < b.first; 
    });

    int lim = 301, answer = 0, idx = -1;
    while (lim < 1201) {
        int nextlim = 0;
        for (int i = idx + 1; i < n && a[i].first <= lim; ++i) {
            nextlim = max(nextlim, a[i].second);
            idx = i;
        }

        if (nextlim == 0) {
            cout << "0\n";
            return 0;
        }

        lim = nextlim;
        ++answer;
    }
    cout << answer << "\n";

    return 0;
}

