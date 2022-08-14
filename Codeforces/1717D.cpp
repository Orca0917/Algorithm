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

        vector<pii> sort_arr(n);
        vector<int> arr(n);

        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
            sort_arr[i] = { arr[i], i };
        }

        sort(sort_arr.begin(), sort_arr.end(), [](const pii &a, const pii &b) -> bool {
            return a.first < b.first;
        });

        for (int i = 0; i < k; ++i) {
            int index = sort_arr[i].second;
            arr[index] = 1e9;
        }

        int min_elem = 1e9;
        for (int i = 0; i < n; ++i) min_elem = min(min_elem, arr[i]);

        int answer = min_elem;
        int cur_min = 1e9;
        for (int i = 0; i < n - 1; ++i) {
            cur_min = min(cur_min, arr[i]);
            int dist = min(cur_min, min_elem * 2);
            answer = max(answer, dist);
        }

        cout << answer << "\n";
    }
    
    return 0;
}