#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string name;
    int age, weight;
    while (cin >> name >> age >> weight) {
        if (name == "#") break;
        if (age > 17 || weight >= 80) cout << name << " Senior\n";
        else cout << name << " Junior\n";
    }
    
    return 0;
}