#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int change_mask = '1' ^ '0';
int n;

int doOnOFF(string bulb, string result) {
    int ret = 0;

    for (int i = 1; i < n; ++i) {
        if (bulb[i - 1] != result[i - 1]) {
            ++ret;
            bulb[i - 1] ^= change_mask;
            bulb[i] ^= change_mask;
            if (i + 1 < n) bulb[i + 1] ^= change_mask;
        }
    }

    if (bulb != result) return -1;
    else return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;

    string bulb, result;
    cin >> bulb >> result;
    
    int answer1 = doOnOFF(bulb, result);

    bulb[0] ^= change_mask;
    bulb[1] ^= change_mask;
    int answer2 = doOnOFF(bulb, result);

    // answer2 != -1 : answer2 += 1  because, flip on index 0
    if (answer1 == -1 && answer2 == -1) cout << "-1\n";
    else if (answer1 == -1) cout << answer2 + 1 << "\n";
    else if (answer2 == -1) cout << answer1 << "\n";
    else cout << min(answer1, answer2 + 1) << "\n";
    
    return 0;
}