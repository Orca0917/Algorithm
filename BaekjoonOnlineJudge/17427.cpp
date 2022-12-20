#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

bool is_prime[1'000'001];

void eratos() {
    for (int i = 2; i <= 1'000'000; ++i) {
        for (int j = 2; i * j <= 1'000'000 && is_prime[i]; ++j)
            is_prime[i * j] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(is_prime, true, sizeof(is_prime));
    int n; cin >> n;

    ll answer = n;
    for (int i = 2; i <= n; ++i) {
        if (!is_prime[i]) continue;
        answer += 1LL * (n / i) * i;
    }    

    cout << answer << "\n";
    
    return 0;
}