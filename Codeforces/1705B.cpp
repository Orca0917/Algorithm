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

        queue<int> zero_idx;
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
            if (arr[i] == 0) zero_idx.push(i);
        }

        int non_zero_start = 0;
        for (int i = 0; i < n; ++i) {
            if (arr[i] != 0) {
                non_zero_start = i;
                break;
            }
        }

        for (int i = non_zero_start; i < n - 1 && !zero_idx.empty(); ++i) {
            while (arr[i] > 0 && !zero_idx.empty()) {
                int x = zero_idx.front(); zero_idx.pop();
                arr[x] += 1;
            }
        }

        ll answer = 0;
        for (int i = non_zero_start; i < n - 1; ++i) {
            answer += arr[i];
        }

        cout << answer << "\n";
    }
    return 0;
}