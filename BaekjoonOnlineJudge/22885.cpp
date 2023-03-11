#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    for (int tc = 1; tc <= testcase; ++tc) {
        int n; cin >> n;
        vector<int> v(n);
        for (int &e : v) cin >> e;

        int answer = 0;
        for (int i = 0; i < n - 1; ++i) {
            int j = min_element(v.begin() + i, v.end()) - v.begin();
            answer += (j - i + 1);
            reverse(v.begin() + i, v.begin() + j + 1);
        }

        cout << "Case #" << tc << ": " << answer << "\n";
    }
    
    return 0;
}