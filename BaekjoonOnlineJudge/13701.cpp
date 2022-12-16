#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int bits[(1 << 25) / 32];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n;
    while (cin >> n) {
        int shift = n % 32;
        if ((bits[n / 32] & (1 << shift)) == 0) cout << n << " ";
        bits[n / 32] |= (1 << shift);
    }
    
    return 0;
}