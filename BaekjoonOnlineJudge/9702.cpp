#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    for (int tc = 1; tc <= testcase; ++tc) {
        ll answer = 0;
        int n; cin >> n;

        vector<int> arr(n);
        for (int &e : arr) cin >> e;

        for (int i = 0; i < n; ++i) {
            vector<int> LIS;
            LIS.push_back(-1);
            for (int j = 0; i + j < n; ++j) {
                int k = arr[i + j];
                if (LIS.back() < k) LIS.push_back(k);
                else *lower_bound(LIS.begin(), LIS.end(), k) = k;

                answer += LIS.size() - 1;
            }
        }

        cout << "Case #" << tc << ": " << answer << "\n"; 
    }
    
    return 0;
}