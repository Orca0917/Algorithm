#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s; cin >> s;
    int n = s.length();

    regex re("((100+1+)|(01))+");

    cout << (regex_match(s, re) ? "SUBMARINE" : "NOISE") << "\n";
    
    return 0;
}