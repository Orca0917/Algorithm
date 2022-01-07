#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    vector<int> a(6);
    for (int &e : a) cin >> e;
    int sum = accumulate(a.begin(), a.end(), 0);
    cout << sum * 5 << "\n";
    return 0;
}