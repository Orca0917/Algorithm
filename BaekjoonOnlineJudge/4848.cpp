#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

string s1, s2;
map<string, int> str2int;
map<int, string> int2str;

string builder(int n) {
    if (n == 0) return "{}";

    string result = "";
    for (int i = 0; i < n; ++i) {
        result += builder(i);
        if (i < n -1) result += ",";
    }

    return "{" + result + "}"; 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    for (int i = 0; i <= 15; ++i) {
        str2int[builder(i)] = i;
        int2str[i] = builder(i);
    }

    int T; cin >> T;
    while (T--) {
        cin >> s1 >> s2;
        int sum = str2int[s1] + str2int[s2];
        cout << int2str[sum] << "\n";
    }
    
    return 0;
}