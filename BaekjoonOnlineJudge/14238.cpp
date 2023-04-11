#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

string s;
int memo[51][51][51][2][3];
char trace[51][51][51][2][3];
int cnt[3];

int dp(int a, int b, int c, int b_cool, int c_cool) {
    if (a + b + c == 0) return 1;

    int &ret = memo[a][b][c][b_cool][c_cool];
    if (ret != -1) return ret;

    ret = 0;

    if (a > 0) {
        int a_result = dp(a - 1, b, c, max(0, b_cool - 1), max(0, c_cool - 1));
        if (a_result != 0) trace[a][b][c][b_cool][c_cool] = 'A';
        ret = max(ret, a_result);
    }

    if (ret == 0 && b > 0 && b_cool == 0) {
        int b_result = dp(a, b - 1, c, 1, max(0, c_cool - 1));
        if (b_result != 0) trace[a][b][c][b_cool][c_cool] = 'B';
        ret = max(ret, b_result);
    }

    if (ret == 0 && c > 0 && c_cool == 0) {
        int c_result = dp(a, b, c - 1, max(0, b_cool - 1), 2);
        if (c_result != 0) trace[a][b][c][b_cool][c_cool] = 'C';

        ret = max(ret, c_result);
    }

    return ret > 0 ? 1 : 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> s;

    memset(cnt, 0, sizeof(cnt));
    memset(memo, -1, sizeof(memo));

    for (char c : s) cnt[c - 'A'] += 1;
    
    int ret = dp(cnt[0], cnt[1], cnt[2], 0, 0);
    if (ret == 0) cout << "-1\n";
    else {
        int ac = cnt[0], bc = cnt[1], cc = cnt[2];
        int bt = 0, ct = 0;
        while (ac + bc + cc > 0) {
            char now = trace[ac][bc][cc][bt][ct];
            cout << now;

            if (bt) --bt;
            if (ct) --ct;

            if (now == 'A') {
                ac -= 1;
            } else if (now == 'B') {
                bc -= 1;
                bt = 1;
            } else if (now == 'C') {
                cc -= 1;
                ct = 2;
            }
        }
    }
    
    return 0;
}