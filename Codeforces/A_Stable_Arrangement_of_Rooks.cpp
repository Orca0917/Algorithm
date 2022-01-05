#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int n, k; cin >> n >> k;

        if (ceil(n / 2.0) < k) cout << "-1\n";
        else {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (i == j && i % 2 == 0 && k-- > 0)
                        cout << 'R';
                    else 
                        cout << '.';
                }
                cout << "\n";
            }
        }      
    }
    
    return 0;
}