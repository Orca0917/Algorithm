#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int get_score(char me, char you) {
    if (me == you) return 1;
    else if (me == 'S' && you == 'P') return 2;
    else if (me == 'P' && you == 'R') return 2;
    else if (me == 'R' && you == 'S') return 2;
    else return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int rounds; cin >> rounds;
    string p1; cin >> p1;

    int n; cin >> n;
    vector<string> p2(n);
    for (auto &s : p2) cin >> s;

    int result = 0, max_result = 0;

    int s, r, p;
    for (int round = 0; round < rounds; ++round) {

        s = r = p = 0;
        for (int player = 0; player < n; ++player) {
            if (p2[player][round] == 'S') ++s;
            else if (p2[player][round] == 'P') ++p;
            else ++r;
        }

        int ps = p * 2 + s, sr = s * 2 + r, rp = r * 2 + p;

        if (p1[round] == 'S') result += ps;
        else if (p1[round] == 'R') result += sr;
        else result += rp;

        max_result += max({ps, sr, rp});
    }

    cout << result << "\n" << max_result << "\n";

    return 0;
}