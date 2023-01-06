#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n; cin >> n;
    vector<string> v(n);
    for (string &name : v) cin >> name;

    if (is_sorted(v.begin(), v.end())) cout << "INCREASING\n";
    else if (is_sorted(v.rbegin(), v.rend())) cout << "DECREASING\n";
    else cout << "NEITHER\n";

    return 0;
}
