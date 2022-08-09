#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int k, d, a;
    char slash;

    cin >> k >> slash >> d >> slash >> a;

    if (k + a < d || d == 0) cout << "hasu\n";
    else cout << "gosu\n";
    
    return 0;
}