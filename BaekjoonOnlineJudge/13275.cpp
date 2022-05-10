#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> range;
void manacher(string &s) {
    int s_len = (int)s.length();
    int r = 0, p = 0;

    for (int i = 0; i < s_len; ++i) {

        if (r < i) range[i] = 0;
        else range[i] = min(r - i, range[2 * p - i]);

        while (i - range[i] - 1 >= 0 && i + range[i] + 1 < s_len && s[i - range[i] - 1] == s[i + range[i] + 1]) ++range[i];

        if (r < range[i] + i) {
            r = range[i] + i;
            p = i;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s; cin >> s;
    string ns = "";

    for (char c : s) {
        ns += '.';
        ns += c;
    } ns += '.';

    range.resize(ns.length(), 0);
    manacher(ns);

    cout << *max_element(range.begin(), range.end()) << "\n";
    return 0;
}