#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

bool is_prime[100001];

void eratos() {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= 100000; ++i) {
        for (int j = 2; i * j <= 100000 && is_prime[i]; ++j) {
            is_prime[i * j] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(is_prime, true, sizeof(is_prime));
    eratos();

    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        map<int, int> m;
        int cur = 2;

        while (n != 1) {
            
            if (n % cur == 0) {
                m[cur] += 1;
                n /= cur;
            }

            else {
                ++cur;
                while (!is_prime[cur]) cur++;
            }
        }

        for (auto it = m.begin(); it != m.end(); ++it) {
            cout << it->first << " " << it->second << "\n";
        }
    }
    
    return 0;
}