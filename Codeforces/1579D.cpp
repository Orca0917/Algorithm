#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        set<pii, greater<pii>> s;

        for (int i = 1; i <= n; ++i) {
            int k; cin >> k;
            if (k == 0) continue;
            s.insert({k, i});
        }

        vector<pii> answer;
        while (s.size() > 1) {
            pii p1 = *s.begin();
            s.erase(s.begin());

            pii p2 = *s.begin();
            s.erase(s.begin());
            
            answer.push_back({p1.second, p2.second});
            if (p1.first > 1) s.insert({p1.first - 1, p1.second});
            if (p2.first > 1) s.insert({p2.first - 1, p2.second});
        }

        cout << answer.size() << "\n";
        for (auto e : answer) cout << e.first << " " << e.second << "\n";
    }
    return 0;

}