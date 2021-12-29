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

        int ansx = 0, ansy = 0;

        if (mx <= dx) {
            ansx = dx - mx;
        } else {
            ansx = dx - mx;
            ansx += (n - dx) * 2;
        }

        if (my <= dy) {
            ansy = dy - my;
        } else {
            ansy = dy - my;
            ansy += (m - dy) * 2;
        }

        cout << min(ansx, ansy) << "\n";
    }
       
    return 0;
}