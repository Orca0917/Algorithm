#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> v;
vector<bool> memo(800001, false);
int w, n; 


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> w >> n;
    
    v.resize(n);
    for (int &e : v) cin >> e;

    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < i; ++j) {
            int target = w - v[i] - v[j];
            if (target >= 0 && memo[target]) goto Answer;
        }
        for (int j = i + 1; j < n; ++j)
            memo[v[i] + v[j]] = true;
    }
    cout << "NO\n";
    return 0;

Answer:
    cout << "YES\n";
    return 0;
}