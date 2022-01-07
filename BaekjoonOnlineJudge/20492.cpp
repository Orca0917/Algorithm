#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    cout << (int)(n * 0.78) << " " << (int)(n * 0.8) + (int)((n * 0.2) * 0.78) << "\n";
    return 0;
}