#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m, k; cin >> n >> m >> k;
    int diff = (k - 3) % n;

    m += diff;

    if (m > n) m = m % n;
    else if (m <= 0) {
        while (m <= 0) {
            m += n;
        }
    }

    cout << m << "\n";

    return 0;
}