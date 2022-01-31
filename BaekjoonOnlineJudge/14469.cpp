#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<pii> A(n);
    for (auto &a : A) {
        cin >> a.first >> a.second;
    }
    
    sort(A.begin(), A.end());

    int time = 0;
    for (int i = 0 ; i < n; ++i) {
        if (time < A[i].first) {
            time = A[i].first + A[i].second;
        } else {
            time += A[i].second;
        }
    }

    cout << time << "\n";
    return 0;
}