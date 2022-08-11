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

        vector<ll> arr(n);
        for (int i = 0; i < n; ++i) cin >> arr[i];

        ll answer = 0;
        if (n % 2 == 0) {
            vector<ll> cost(n, 0);

            for (int i = 1; i < n - 1; ++i) {
                cost[i] = max(0LL, max(arr[i - 1], arr[i + 1]) + 1 - arr[i]);
            }

            ll right_sum = 0;
            ll left_sum = 0;
            for (int i = 2; i < n; i += 2) right_sum += cost[i];

            answer = -1;
            for (int part = 1; part <= n; part += 2) {
                ll temp = left_sum + right_sum;

                if (part < n - 1) {
                    left_sum += cost[part];
                    right_sum -= cost[part + 1];
                }

                if (answer == -1) answer = temp;
                else answer = min(answer, 1LL * temp);
            }

        } else {
            for (int i = 1; i < n; i += 2) {
                answer += max(0LL, max(arr[i - 1], arr[i + 1]) + 1 - arr[i]);
            }
        }

        cout << answer << "\n";
    }
    return 0;
}