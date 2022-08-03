#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    vector<int> lis;
    lis.push_back(-1);

    int n; cin >> n;
    while (n--) {
        int k; cin >> k;
        if (lis.back() < k) lis.push_back(k);
        else *lower_bound(lis.begin(), lis.end(), k) = k;
    }

    cout << lis.size() - 1 << "\n";
    
    return 0;
}