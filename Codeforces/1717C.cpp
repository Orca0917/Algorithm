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
        int n; cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) cin >> arr[i];
        
        vector<int> last_index(n + 1, -1);
        
        for (int i = 0; i < n; ++i) {
            last_index[arr[i]] = i;
        }

        int number = -1;
        for (int i = 0; i < n - 1; ++i) {
            if (arr[i] > arr[i + 1]) {
                number = i;
            }
        }

        int lid = -1;
        for (int i = 0; i <= number; ++i) lid = max(lid, last_index[arr[i]]);

        int answer = 0;
        for (int i = 1; i <= n; ++i) {
            if (last_index[i] == -1) continue;
            if (last_index[i] <= lid) ++answer;
        }

        if (n == 1) answer = 0;

        cout << answer << "\n";
    }
    
    return 0;
}