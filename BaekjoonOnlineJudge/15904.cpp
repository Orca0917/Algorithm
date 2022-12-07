#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s;
    getline(cin, s);

    vector<char> v = {'C', 'P', 'C', 'U'};
    for (char c : s) {
        if (v.empty()) break;

        if (c == v.back()) {
            v.pop_back();
        }
    }

    if (v.empty()) cout << "I love UCPC\n";
    else cout << "I hate UCPC\n";
    
    return 0;
}