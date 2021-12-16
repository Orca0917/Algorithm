#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s; cin >> s;
    int N = s.length();

    int pCnt = 0;
    for (int i = 0; i < N; ++i) {
        if (s[i] == 'P') {
            ++pCnt;
            continue;
        }

        if (pCnt >= 2 && s[i + 1] == 'P') {
            --pCnt;
            ++i;
        }
        else {
            cout << "NP\n";
            return 0;
        }
    }

    if (pCnt == 1) cout << "PPAP\n";
    else cout << "NP\n";

    return 0;
}