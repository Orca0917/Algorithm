#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

vector<int> primes;
vector<bool> is_prime(100001, true);

void eratos() {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= 100000; ++i) {
        for (int j = 2; is_prime[i] && i * j <= 100000; ++j) {
            is_prime[i * j] = false;
        }
        if (is_prime[i]) primes.push_back(i);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int a, b; cin >> a >> b;
    eratos();

    int answer = 0;
    for (int i = a; i <= b; ++i) {
        int cnt = 0, idx = 0;
        int num = i;
        for (int p : primes) {
            while (num % p == 0) {
                num /= p;
                ++cnt;
            }
            if (num == 1) break;
        }

        if (is_prime[cnt]) ++answer;
    }

    cout << answer << "\n";
    
    return 0;
}