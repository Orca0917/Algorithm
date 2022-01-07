#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    string s;
    getline(cin, s);
    
    while (testcase--) {
        string s; getline(cin, s);
        istringstream ss(s);
        string stringBuff;
        vector<int> A;

        while (getline(ss, stringBuff, ' ')) {
            A.push_back(stoi(stringBuff));
        }

        int answer = 0;
        for (int i = 0; i < A.size(); ++i)
            for (int j = i + 1; j < A.size(); ++j)
                answer = max(answer, __gcd(A[i], A[j]));

        cout << answer << "\n";
    }
    
    return 0;
}