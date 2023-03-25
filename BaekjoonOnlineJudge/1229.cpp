#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define MAX 1'000'001

using namespace std;

int n;
vector<int> h;
int memo[MAX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;
    h.push_back(1);
    h.push_back(6);

    memset(memo, -1, sizeof(memo));
    memo[0] = 0;
    memo[1] = 1;
    
    for (int i = 3; h.back() < n; ++i) {
        h.push_back((int)h.back() + 4 * i - 3);
    }

    for (int i = 2; i <= n; ++i) {
        memo[i] = 1e9;
        for (int &hx : h) {
            if (hx > i) break;
            memo[i] = min(memo[i], memo[i - hx] + 1);
        }
    }

    assert(memo[n] <= 6);
    cout << memo[n] << "\n";

    return 0;
}