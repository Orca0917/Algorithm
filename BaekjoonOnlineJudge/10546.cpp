#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    multiset<string> s;
    for (int i = 0; i < n; ++i) {
        string name; cin >> name;
        s.insert(name);
    }

    for (int i = 0; i < n - 1; ++i) {
        string name; cin >> name;
        s.erase(s.find(name));
    }

    cout << *s.begin() << "\n";
    return 0;
}