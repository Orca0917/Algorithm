#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

bool equation_available(vector<int> &x, vector<char> &v) {
    for (int i = 0; i < x.size() - 1; ++i) {
        if (v[i] == '>' && x[i] < x[i + 1]) return false;
        if (v[i] == '<' && x[i] > x[i + 1]) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;

    vector<char> v(n);
    for (char &c : v) cin >> c;

    vector<int> asc, desc;
    for (int i = 0; i <= n; ++i) asc.push_back(i);
    for (int i = 9; i >= 9 - n; --i) desc.push_back(i);

    do {
        if (equation_available(desc, v)) {
            for (int e : desc) cout << e; cout << "\n";
            break;
        }
    } while (prev_permutation(desc.begin(), desc.end()));

    do {
        if (equation_available(asc, v)) {
            for (int e : asc) cout << e; cout << "\n";
            break;
        }
    } while (next_permutation(asc.begin(), asc.end()));
    
    
    
    return 0;
}