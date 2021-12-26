/*
 * author: 0917jong
 * date: 2021-12-05
 */

#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int testcase; cin >> testcase;
    while (testcase--) {
        int n, m; cin >> n >> m;
        deque<int> pl, mi;
        for (int i = 0; i < n; ++i) {
            int k; cin >> k;
            if (k < 0) mi.push_back(k);
            else pl.push_back(k);
        }

        if (!mi.empty()) sort(mi.begin(), mi.end());
        if (!pl.empty()) sort(pl.begin(), pl.end());

        ll answer = 0;
        // 마지막은 오른쪽으로 가서 끝나야 한다.
        if ((mi.empty() && !pl.empty()) || (mi.size() * pl.size() != 0 && abs(mi.front()) < pl.back())) {
            while (!mi.empty()) {
                answer += abs(mi.front()) * 2;
                for (int i = 0; i < m && !mi.empty(); ++i)
                    mi.pop_front();
            }
            answer -= pl.back();
            while (!pl.empty()) {
                answer += pl.back() * 2;
                for (int i = 0; i < m && !pl.empty(); ++i)
                    pl.pop_back();
            }
        } 
        // 마지막은 왼쪽으로 가서 끝나야 한다.
        else {
            answer -= abs(mi.front());
            while (!mi.empty()) {
                answer += abs(mi.front()) * 2;
                for (int i = 0; i < m && !mi.empty(); ++i)
                    mi.pop_front();
            }
            while (!pl.empty()) {
                answer += pl.back() * 2;
                for (int i = 0; i < m && !pl.empty(); ++i)
                    pl.pop_back();
            }
        }
        cout << answer << "\n";
    }

    return 0;
}
