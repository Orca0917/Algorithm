#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

string s = "dehlorw";
unordered_map<char, int> m;

string s1 = "hello";
string s2 = "world";

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    vector<int> nums;
    for (int i = 0; i < 10; ++i) nums.push_back(i);

    int target; cin >> target;
    bool flag = false;
    do {
        for (int i = 0; i < 7; ++i) m[s[i]] = nums[i];

        if (m['h'] * m['w'] == 0) continue;

        int num1 = 0, num2 = 0;
        for (char c : s1) {num1 *= 10; num1 += m[c]; }
        for (char c : s2) {num2 *= 10; num2 += m[c]; }

        if (num1 + num2 == target) {
            cout << "  " << num1 << "\n";
            cout << "+ " << num2 << "\n";
            cout << "-------\n";
            cout << (to_string(target).length() == 5 ? "  " : " ") << target << "\n";
            flag = true;
            break;
        }

    } while (next_permutation(nums.begin(), nums.end()));
    
    if (!flag) cout << "No Answer\n";
    
    return 0;
}