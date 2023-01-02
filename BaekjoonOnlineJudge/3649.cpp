#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int x, n;
    while (cin >> x >> n) {
        vector<int> arr(n);
        for (int &e : arr) cin >> e;
        sort(arr.begin(), arr.end());

        for (int i = 0; i < n; ++i) {
            int target = x * 10'000'000 - arr[i];
            if (target < arr[i]) break;
            if (*lower_bound(arr.begin() + i + 1, arr.end(), target) == target) {
                cout << "yes " << arr[i] << " " << target << "\n";
                goto nxt;
            }
        }

        cout << "danger\n";

        nxt:
            ;
    }
    
    return 0;
}