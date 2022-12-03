#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;
vector<int> digits[200001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    const int inf = 1234567890;
    
    digits[0].resize(20, 0);
    for (int i = 1; i <= 200000; ++i) {
        digits[i].resize(20, 0);
        int bit = 1, k = 1;
        while (i >= bit) {
            digits[i][k] = digits[i - 1][k];
            if (i & bit) digits[i][k]++;
            bit = bit << 1;
            ++k;
        }
    }

    int testcase; cin >> testcase;

    while (testcase--) {
        int l, r; cin >> l >> r;
        int maxLen = ceil(log2(r)) + 1;
        
        vector<int> sum(20, 0);
        for (int i = 0; i < 20; ++i) {
            sum[i] = digits[r][i] - digits[l - 1][i];
        }
        
        int answer = inf;
        for (int i = 1; i <= maxLen; ++i) {
            answer = min(r - l + 1 - sum[i], answer);
        }
        cout << answer << "\n";

    }
       
    return 0;
}