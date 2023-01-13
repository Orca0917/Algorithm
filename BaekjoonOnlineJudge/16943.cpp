#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int b;
    string a; cin >> a >> b;
    int answer = -1;

    sort(a.begin(), a.end());
    do {
        if (a[0] != '0' && stoi(a) < b) answer = stoi(a);
        else if (stoi(a) >= b) break;
    } while (next_permutation(a.begin(), a.end()));

    cout << answer << "\n";
    
    return 0;
}