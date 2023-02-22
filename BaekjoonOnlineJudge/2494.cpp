#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int num_number;
string initial_status;
string target_status;
int memo[10001][10];

int dp(int index, int adder) {
    int &ret = memo[index][adder];
    if (ret != -1) return ret;

    if (index == num_number) return ret = 0;

    int current = (initial_status[index] - '0' + adder) % 10;
    int target = target_status[index] - '0';

    int rotate = 0;
    while (current != target) {
        ++current;
        ++rotate;
        current %= 10;
    }

    ret = min((int)1e9, dp(index + 1, (adder + rotate) % 10) + rotate);
    ret = min(ret, dp(index + 1, adder) + (10 - rotate));

    return ret;
}

void trace(int index, int adder) {
    if (index == num_number) return;

    int current = (initial_status[index] - '0' + adder) % 10;
    int target = target_status[index] - '0';

    int rotate = 0;
    while (current != target) {
        ++current;
        ++rotate;
        current %= 10;
    }

    if (memo[index + 1][adder] != -1 && memo[index][adder] - memo[index + 1][adder] == (10 - rotate)) {
        cout << index + 1 << " " << rotate - 10 << "\n";
        trace(index + 1, adder);
    } else {
        cout << index + 1 << " " << rotate << "\n";
        trace(index + 1, (adder + rotate) % 10);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> num_number >> initial_status >> target_status;

    memset(memo, -1, sizeof(memo));
    cout << dp(0, 0) << "\n";
    trace(0, 0);
    
    return 0;
}