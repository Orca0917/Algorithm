#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout.precision(10);
    int testcase; cin >> testcase;
    while (testcase--) {
        int W, H; cin >> W >> H;
        int A, B, C, D; cin >> A >> B >> C >> D;
        int X, Y; cin >> X >> Y;

        const int inf = 1e9;
        int answer = inf;
        if (C - A + X <= W) {
            answer = min(answer, max(0, X - A));
            answer = min(answer, max(0, C - W + X));
        }
        if (D - B + Y <= H) {
            answer = min(answer, max(0, Y - B));
            answer = min(answer, max(0, D - H + Y));
        }
        cout << (answer == inf ? -1 : (double)answer) << "\n";
    }
    return 0;
}