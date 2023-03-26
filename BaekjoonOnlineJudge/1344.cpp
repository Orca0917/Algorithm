#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
using namespace std;

bool is_prime[20];
double win[2];
double memo[20][20][20];

double dp(int round, int a_score, int b_score) {
    if (round == 18) {
        if (is_prime[a_score] || is_prime[b_score]) return 1.0;
        else return 0.0;
    }

    double &ret = memo[round][a_score][b_score];
    if (ret != -1) return ret;

    ret = dp(round + 1, a_score, b_score) * (1 - win[0]) * (1 - win[1]);
    ret += dp(round + 1, a_score + 1, b_score) * win[0] * (1 - win[1]);
    ret += dp(round + 1, a_score, b_score + 1) * (1 - win[0]) * win[1];
    ret += dp(round + 1, a_score + 1, b_score + 1) * win[0] * win[1];

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int win_a, win_b;
    cin >> win_a >> win_b;

    win[0] = win_a / 100.0;
    win[1] = win_b / 100.0;

    int primes[7] = {2, 3, 5, 7, 11, 13, 17};
    memset(is_prime, false, sizeof(is_prime));
    for (int prime : primes) is_prime[prime] = true;

    double ret_a = 0, ret_b = 0;
    for (int i = 0; i < 20; ++i)
        for (int j = 0; j < 20; ++j)
            for (int k = 0; k < 20; ++k)
                memo[i][j][k] = -1.0;

    cout << setprecision(10);
    cout << fixed << dp(0, 0, 0) << "\n";

    return 0;
}