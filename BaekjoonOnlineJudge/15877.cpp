#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int memo[1001][1001][2];

int dp(int apple, int banana, int turn) {
    if (apple == 0 && banana == 0) return (turn + 1) % 2;

    int &ret = memo[apple][banana][turn];
    if (ret != -1) return ret;

    int res[4] = {-1, -1, -1, -1};

    // 사과 1개
    if (apple >= 1)
        res[0] = dp(apple - 1, banana, (turn + 1) % 2);

    // 바나나 1개
    if (banana >= 1)
        res[1] = dp(apple, banana - 1, (turn + 1) % 2);
    
    // 사과3개, 바나나 1개
    if (apple >= 3 && banana >= 1)
        res[2] = dp(apple - 3, banana - 1, (turn + 1) % 2);

    // 사과1개, 바나나 3개
    if (apple >= 1 && banana >= 3)
        res[3] = dp(apple - 1, banana - 3, (turn + 1) % 2);

    for (int result : res) {
        if (result == turn)
            return ret = turn;
    }

    return ret = (turn + 1) % 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int a, b; cin >> a >> b;
 
    memset(memo, -1, sizeof(memo));
 
    // 0: alice, 1 : bob
    int answer = dp(a, b, 0);

    if (answer == 1) cout << "Bob\n";
    else cout << "Alice\n";
    
    return 0;
}