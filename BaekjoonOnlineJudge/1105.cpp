#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string n1, n2; cin >> n1 >> n2;

    while (n1.length() != n2.length()) {
        n1 = "0" + n1;
    }

    string common = "";
    for (int i = 0; i < n1.length(); ++i) {
        if (n1[i] == n2[i]) common += n1[i];
        else break;
    }

    int answer = 0;
    for (char c : common) {
        if (c == '8') ++answer;
    }
    cout << answer << "\n";
    return 0;
}