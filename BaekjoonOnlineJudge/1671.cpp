#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct shark {
    int size;
    int speed;
    int intel;
};

vector<shark> sharks;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int sz, sp, it; cin >> sz >> sp >> it;
        sharks.push_back({sz, sp, it});
    }
    return 0;
}