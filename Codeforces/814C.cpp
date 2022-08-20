#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int n, q; cin >> n >> q;
        
        int strongest = 0;
        deque<int> dq(n);
        vector<int> orig(n);
        for (int i = 0; i < n; ++i) {
            cin >> dq[i];
            orig[i] = dq[i];
            if (orig[i] == n) strongest = i;
        }

        // 각자 최대 몇 라운드 살아남을 수 있는가
        int maximum_round[200001];
        int win_start_round[200001];
        memset(maximum_round, 0, sizeof(maximum_round));
        memset(win_start_round, -1, sizeof(win_start_round));

        int cur_rnd = 0;
        while (true) {
            ++cur_rnd;
            int p1 = dq[0]; dq.pop_front();
            int p2 = dq[0]; dq.pop_front();

            if (p1 < p2) {
                if (win_start_round[p2] == -1) win_start_round[p2] = cur_rnd;
                ++maximum_round[p2];
                dq.push_front(p2);
                dq.push_back(p1);
            } else {
                ++maximum_round[p1];
                dq.push_front(p1);
                dq.push_back(p2);
            }

            if (dq[0] == n) break;
        }

        while (q--) {
            int who, round; cin >> who >> round;
            who = orig[who - 1];
            if (who == n) {
                if (round < strongest) cout << "0\n";
                else cout << round - max(strongest - 1, 0) << "\n";
            } else {
                if (round < win_start_round[who]) cout << "0\n";
                else cout << min(maximum_round[who], round - max(win_start_round[who] - 1, 0)) << "\n";
            }
        }


    }
    
    return 0;
}