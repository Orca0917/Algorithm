#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        string n; cin >> n;
        int digit = n.length();
        int answer = (digit - 1) * 9;
        answer += (n[0] - '0');
        
        cout << answer << "\n";
    }
    
    return 0;
}