#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int count_bits(int value) {
    int bit = 0, ret = 0;
    while ((1 << bit) <= value) {
        if (value & (1 << bit++)) ++ret;
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, k; cin >> n >> k;

    int bit = 0;
    int base = count_bits(n);

    int answer = 0;
    while (count_bits(n + answer) > k) {
        answer++;
    }

    cout << answer << "\n";

    
    return 0;
}