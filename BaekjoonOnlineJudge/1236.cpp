#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

bool row[51], col[51];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m; cin >> n >> m;
    int answer = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c; cin >> c;
            if (c == 'X') {
                row[i] = true;
                col[j] = true;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (row[i] == false && col[j] == false) {
                ++answer;
                row[i] = true;
                col[j] = true;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (row[i] == false || col[j] == false) {
                ++answer;
                row[i] = true;
                col[j] = true;
            }
        }
    }

    cout << answer << "\n";
    
    return 0;
}