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
        int n, m, mx, my, dx, dy;
        cin >> n >> m >> mx >> my >> dx >> dy;
        
        int answer = 0;
        int mv1 = 1, mv2 = 1;
        while (dx != mx && dy != my) {

            if (mx + mv1 == 0 || mx + mv1 == n + 1) mv1 = -mv1;
            if (my + mv2 == 0 || my + mv2 == m + 1) mv2 = -mv2;

            mx += mv1;
            my += mv2;

            ++answer;
        }

        cout << answer << "\n";
    }
       
    return 0;
}