#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

bool isPrime[500001];

void eratosthenes(int n) {
    memset(isPrime, true, sizeof(isPrime));
    for (int i = 2; i <= n; ++i) {
        if (!isPrime[i]) continue;
        for (int j = 2; i * j <= n; ++j) {
            isPrime[i * j] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    eratosthenes(n);

    if (n == 1) cout << "1\n";
    else cout << n / 2 << "\n";

    for (int i = 1; i <= n; ++i) {
        if (isPrime[i]) cout << 1 << " ";
        else cout << i / 2 << " ";
    }

    return 0;
}