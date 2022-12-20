#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    ll a, b; cin >> a >> b;
    pair<ll, ll> answer;

    ll mul = a * b;
    ll prev_sum = 1e10;
    for (ll i = 1; i <= (ll)sqrt(mul); ++i) {
        if (mul % i == 0 && __gcd(1LL * i, mul / i) == a) {
            if (prev_sum > i + (mul / i)) {
                prev_sum = i + mul / i;
                answer = {i, mul / i};
            }
        }
    }
    cout << answer.first << " " << answer.second << "\n";

    
    return 0;
}