/*
 * author: 0917jong / 유종문
 * date: 2021-12-02
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    int n; cin >> n;
    vector<int> weightLimit(n);
    for (int i =0; i < n; ++i) cin >> weightLimit[i];
    
    int m; cin >> m;
    int M = 0;
    multiset<int> weight;
    for (int i = 0; i < m; ++i) {
        int k; cin >> k;
        M = max(M, k);
        weight.insert(k);
    }

    sort(weightLimit.begin(), weightLimit.end());

    int answer = 0;
    if(M > weightLimit[n - 1]) {
        cout << -1 << "\n";
        return 0;
    }

    while (!weight.empty()) {
        ++answer;

        for (int i = 0; i < weightLimit.size(); ++i) {
            int lim = weightLimit[i];
            auto up = weight.upper_bound(lim);
            
            if (up == weight.begin()) continue;
            --up;
            weight.erase(up);
        }
    }

    cout << answer << "\n";

    return 0;
}