#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s;
    int k;


    while (cin >> s >> k) {
        cout << s << " " << k << " = ";
        int iter = 0;

        vector<char> v;
        for (char c : s) v.push_back(c);

        do {
            if (++iter == k) break;
        } while (next_permutation(v.begin(), v.end()));

        if (iter == k) for (char c : v) cout << c;
        else cout << "No permutation";
        cout << "\n";
    }
    
    return 0;
}