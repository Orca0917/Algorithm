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
        int n; cin >> n;
        
        vector<pii> A(n);
        for (int i = 0; i < n; ++i) {
            cin >> A[i].first;
            A[i].second = i;
        }

        sort(A.begin(), A.end());

        bool hasDup = false;
        for (int i = 0; i < n - 1; ++i) if (A[i].first == A[i + 1].first) hasDup = true;

        int marks = 0;
        vector<int> marked(n, 0);

        for (int i = 0; i < n; ++i) {
            if (A[i].second != i && marked[i] == 0) {
                int cluster_size = 1;
                marked[i] = 1;
                for (int j = A[i].second; j != i; j = A[j].second) {
                    cluster_size += 1;
                    marked[j] = 1;
                }
                if (cluster_size % 2 == 0) ++marks;
            }           
        }

        if (hasDup) cout << "YES\n";
        else if (marks % 2) cout << "NO\n";
        else cout << "YES\n";
    }
    
    return 0;
}