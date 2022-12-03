#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;
vector<bool> check(100001, false);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    
    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        vector<ll> A;
        fill(check.begin(), check.end(), false);

        for (int i = 0; i < n; ++i) {
            int x; cin >> x;
            if (x <= n && check[x] == false) check[x] = true;
            else A.push_back(x);
        }

        sort(A.begin(), A.end());

        bool canMake = true;
        int result = 0;
        int matched = 0;

        for (int i = n; i >= 1; --i) {
           if (check[i]) continue;

           if (A.back() < 2 * i + 1) {
               canMake = false;
               break;
           }

           A.pop_back();
           ++result;
        }
        
        if (!canMake) cout << "-1\n";
        else cout << result << "\n";
    }
       
    return 0;
}