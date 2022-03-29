#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MOD 987654321

using namespace std;

bool isPrime[1'000'001];

// make prime number set
void eratosthenes(int n) {

    // initialize prime set
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;

    // check prime numbers
    for (int i = 2; i <= n; ++i) {
        for (int j = 2; i * j <= n && isPrime[i] == true; ++j)
            isPrime[i * j] = false; 
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    eratosthenes(n);

    ll answer = 1;
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i] == false) continue;
        ll number = i;
        while (number * i <= n) number *= i;
        answer *= number;
        answer %= MOD;
    }

    cout << answer << "\n";
    return 0;
}