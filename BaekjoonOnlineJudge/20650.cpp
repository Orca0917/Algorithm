#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> a(7);
    for (int i = 0; i < 7; ++i) cin >> a[i];
    sort(a.begin(), a.end());

    ll A = a[0], B = a[1], C;
    ll sum = accumulate(a.begin(), a.end(), 0LL);
    C = sum / 4 - A - B;
    cout << A << " " << B << " " << C << "\n";
    return 0;
}