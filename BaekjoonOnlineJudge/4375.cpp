#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n;
    while (cin >> n) {
        int val = 0;
        for (int i = 1; i <= n; ++i) {
            val = (val * 10 + 1) % n;

            if (val == 0) {
                cout << i << "\n";
                break;
            }
        }
    }
    return 0;
}