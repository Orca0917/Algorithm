#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    map<string, int> m;

    string name;
    int cnt = 0;
    while (getline(cin, name)) {
        m[name] += 1;
        ++cnt;
    }

    cout << fixed;
    cout.precision(4);

    string prev = "";
    for (auto it = m.begin(); it != m.end(); ++it) {
        cout << it->first << " " << (m[it->first] / (double)cnt) * 100 << "\n";
    }
    return 0;
}