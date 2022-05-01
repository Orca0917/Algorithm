#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int memo[100001][2], k;

int dp(int acc, int turn) {

    // 현재 사람 : turn
    // 지금까지의 합 : acc

    int opp = (turn + 1) % 2; // 상대방
    if (acc > k) return opp; // 상대방이 이김

    int &ret = memo[acc][turn];
    if (ret != -1) return ret;

    
    for (int div = 1; div <= sqrt(acc); ++div) {
        if (acc % div == 0) {
            int res = dp(acc + div, opp); // 상대방이 이기는 결과가 있을 때
            if (res == opp) return ret = opp;

            res = dp(acc + acc / div, opp);
            if (res == opp) return ret = opp;
        }
    }

    return ret = turn;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(memo, -1, sizeof(memo));
    cin >> k;

    int result = dp(2, 0);
    if (result == 0) cout << "Kali\n";
    else cout << "Ringo\n";

    return 0;
}