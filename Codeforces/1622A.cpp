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
        vector<int> A(3);
        for (int i = 0; i < 3; ++i) cin >> A[i];

        sort(A.begin(), A.end());

        if (A[2] == A[1] + A[0] || (A[1] == A[2] && A[0] % 2 == 0) || (A[0] == A[1] && A[2] % 2 == 0))
            cout << "YES\n";
        else
            cout << "NO\n";    
    }
    
    return 0;
}