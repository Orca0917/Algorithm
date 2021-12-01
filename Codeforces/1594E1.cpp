#include <iostream>
#define MOD 1000000007

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int treeHeight; cin >> treeHeight;

    long long answer = 1;

    for (int i = 1; i < treeHeight; ++i) {
        answer = (answer * answer * 4) % MOD;
    }

    cout << (6 * answer * answer) % MOD << "\n";

    return 0;
}