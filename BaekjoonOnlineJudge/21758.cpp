#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<int> honey(n);
    for (int &e : honey) cin >> e;
    
    vector<int> psum(n, 0);
    psum[0] = honey[0];
    for (int i = 1; i < n; ++i) psum[i] = psum[i - 1] + honey[i];

    int answer = 0;

    for (int bee2 = 1; bee2 < n - 1; ++bee2) {
        int bee1 = 0;
        int result = psum[n - 1] * 2 - honey[bee1] - psum[bee2] - honey[bee2];
        answer = max(answer, result);
    }

    for (int bee1 = 1; bee1 < n - 1; ++bee1) {
        int bee2 = n - 1;
        int result = psum[bee2] - honey[bee2] - honey[bee1] + psum[bee1 - 1];
        answer = max(answer, result);
    }

    for (int target = 1; target < n - 1; ++target) {
        int bee1 = 0, bee2 = n - 1;
        int result = (psum[target] - honey[bee1]) + (psum[bee2] - psum[target - 1] - honey[bee2]);
        answer = max(answer, result);
    }

    cout << answer << "\n";

    return 0;
}