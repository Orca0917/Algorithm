#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

ll dest_x, dest_y;
ll line, diag;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> dest_x >> dest_y >> line >> diag;

    // 대각선으로 가는 것을 사용하지 않는 경우
    ll result1 = (dest_x + dest_y) * line;

    // 대각선으로 가는 것을 사용하는 경우
    ll diag_move = min(dest_x, dest_y);
    ll line_move = (dest_x + dest_y - 2 * diag_move);
    ll result2 = 0;
    if (line * 2 > diag * 2) 
        result2 = diag_move * diag + (line_move / 2) * (diag * 2) + (line_move % 2) * line;
    else
        result2 = diag_move * diag + line_move * line;

    cout << min(result1, result2);
    
    return 0;
}