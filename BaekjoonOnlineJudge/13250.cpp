#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

double memo[1000001];

double dp(int n) {
    if (n <= 1) return n;

    double &ret = memo[n];
    if (ret >= 0) return ret;

    double sum = 0;
    for (int i = 1; i <= 6 && n - i >= 0; ++i)
        sum += dp(n - i);
    return ret = sum / 6.0 + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    fill(memo, memo + 1000001, -1.0);

    int n; cin >> n;

    cout.precision(15);

    cout << fixed << dp(n) << "\n";


    return 0;
}