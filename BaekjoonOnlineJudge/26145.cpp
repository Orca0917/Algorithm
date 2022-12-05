#include <bits/stdc++.h>
#define ll long long

using namespace std;

int N, M;
ll t[1001][2001];
ll s[2001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> M;

    for (int i = 0; i < N; ++i)
        cin >> s[i];

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N + M; ++j) {
            cin >> t[i][j];
            s[i] -= t[i][j];
            s[j] += t[i][j];
        }
    }    

    for (int i = 0; i < N + M; ++i) 
        cout << s[i] << " ";

    return 0;
}