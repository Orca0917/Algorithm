#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s; cin >> s;
    string result =  "";
    result += s[0];

    for (int i = 1; i < s.length(); ++i) {
        if (result[i - 1] < s[i]) result = s[i] + result;
        else result += s[i];
    }

    reverse(result.begin(), result.end());

    cout << result << "\n";
    
    return 0;
}