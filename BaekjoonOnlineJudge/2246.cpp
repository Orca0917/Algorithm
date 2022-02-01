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
    for (auto &a : A) cin >> a.first >> a.second;

    int answer = 0;
    for (int i = 0; i < n; ++i) {
        bool flag = false;
        for (int j = 0; j < n && !flag; ++j) {
            if (i == j) continue;
            if (A[i].first > A[j].first && A[i].second >= A[j].second) flag = true;
            else if (A[i].second > A[j].second && A[i].first >= A[j].first) flag = true;
        }
        if (!flag) ++answer;
    }

    cout << answer << "\n";

    return 0;
}