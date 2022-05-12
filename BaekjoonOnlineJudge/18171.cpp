#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int range[800008];

int answer = 1e9;

void manacher(string &s) {
    int s_len = s.length();
    int r = 0, p = 0;
    memset(range, 0, sizeof(range));

    for (int i = 0; i < s_len; ++i) {

        if (r < i) range[i] = 0;
        else range[i] = min(r - i, range[p * 2 - i]);

        while (i - range[i] - 1 >= 0 && i + range[i] + 1 < s_len && s[i - range[i] - 1] == s[i + range[i] + 1]) ++range[i];

        if (i + range[i] + 1 == s_len)
            answer = min(answer, (s_len - (range[i] * 2 + 1)) / 2);

        if (r < range[i] + i) {
            r = range[i] + i;
            p = i;
        }

        // cout << range[i] << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    string raw_s; cin >> raw_s;
    string s = "";
    for (char c : raw_s) {
        s += '.';
        s += c;
    } s+= '.';

    manacher(s);

    cout << answer << "\n";
    return 0;
}