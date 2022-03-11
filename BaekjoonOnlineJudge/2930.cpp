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
    
    int r; cin >> r;
    string p1; cin >> p1;

    int n; cin >> n;
    vector<string> p2(n);
    for (auto &s : p2) cin >> s;

    int result = 0, max_result = 0;

    // 상근이의 일반 점수
    for (int you = 0; you < n; ++you)
        for (int round = 0; round < r; ++round)
            result += get_score(p1[round], p2[you][round]);

    // 상근이의 최대 점수
    int max_val = 0, round_score = 0;
    for (int round = 0; round < r; ++round, max_val = 0) {
        for (int j = 0; j < 3; ++j, round_score = 0) {
            char me = "RSP"[j];
            for (int you = 0; you < n; ++you)
                round_score += get_score(me, p2[you][round]);
            max_val = max(max_val, round_score);
        }
        max_result += max_val;
    }

    cout << result << "\n" << max_result << "\n";

    return 0;
}