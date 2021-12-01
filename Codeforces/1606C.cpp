#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

using ll = long long;
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
        ll n, k; cin >> n >> k;
        ++k;
        vector<ll> currency;
        for (int i = 0; i < n; ++i) {
            int exp; cin >> exp;
            currency.push_back(ceil(pow(10, exp)));
        }

        ll answer = 0;
        for (int i = 0; i < n - 1 && k; ++i) {
            ll M = (currency[i + 1] / currency[i]) - 1;
            ll canDo = min(M, k);
            answer += canDo * currency[i];
            k -= canDo;
        }
        answer += currency[n - 1] * k;
        cout << answer << "\n";
    }
    return 0;
}