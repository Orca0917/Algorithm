#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<int> A(n), B(n + 1);
    for (int &a : A) cin >> a; // 1, 2
    for (int i = 0; i < n; ++i) {
        int k; cin >> k;
        B[k] = i; // B[2] = 0, B[1] = 1
    }
    
    vector<int> C(n);
    for (int i = 0; i < n; ++i) {
        int target = A[i];
        int position = B[target];
        C[i] = position;
    }

    vector<int> lis;
    for (int i = 0; i < n; ++i) {
        int k = C[i];
        if (lis.empty() || lis.back() < k) lis.emplace_back(k);
        else *lower_bound(lis.begin(), lis.end(), k) = k;
    }

    cout << lis.size() << "\n";
    
    return 0;
}