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
        vector<int> arr(n), arr2(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
            arr2[i] = arr[i];
        }
        sort(arr.begin(), arr.end());

        vector<bool> is_target(n + 1, false);
        for (int i = 0; i < k; ++i) is_target[arr[i]] = true;

        int answer = 0;
        for (int i = n - 1; i >= k; --i) {
            if (is_target[arr2[i]]) ++answer;
        }

        cout << answer << "\n";
    }
    
    return 0;
}