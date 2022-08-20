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

        if (k == 0) {
            cout << "NO\n";
            continue;
        }

        if (k % 2) {
            cout << "YES\n";
            for (int i = 1; i <= n; i += 2) cout << i << " " << i + 1 << "\n";
        }
        
        else {

            vector<pii> answer;

            int odd = 1;
            int even = n;

            for (int i = 2; i <= even; i += 2) {
                if ((k + i) % 4 == 0 && odd < n) {
                    answer.push_back({i, odd});
                    odd += 2;
                }
                else if (i % 4 == 0 && odd < n) {
                    answer.push_back({odd, i});
                    odd += 2;
                } else if (i < even) {
                    even -= 2;
                    answer.push_back({i, even});
                }
            }

            if (answer.size() == n / 2) {
                cout << "YES\n";
                for (pii t : answer) {
                    cout << t.first << " " << t.second << "\n";
                }
            } else {
                cout << "NO\n";
            }
        }
    }
    
    return 0;
}