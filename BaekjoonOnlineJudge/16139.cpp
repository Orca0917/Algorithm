#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> psum[200'001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s; cin >> s;
    int q; cin >> q;

    psum[0].resize('z' - 'a' + 1, 0);
    psum[0][s[0] - 'a'] += 1;

    for (int i = 1; i < s.length(); ++i) {
        psum[i].resize('z' - 'a' + 1, 0);
        for (int j = 0; j < 'z' - 'a' + 1; ++j)
            psum[i][j] = psum[i - 1][j];
        psum[i][s[i] - 'a'] += 1;
    }

    char c;
    int l, r;
    
    for (int i = 0; i < q; ++i) {
        cin >> c >> l >> r;
        cout << psum[r][c - 'a'] - (l == 0 ? 0 : psum[l - 1][c - 'a']) << "\n";
    }
    
    return 0;
}