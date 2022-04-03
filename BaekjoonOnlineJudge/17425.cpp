#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<ll> make_answer_sheet() {
    vector<ll> answer_sheet(1000001, 1);
    
    for (int i = 2; i <= 1'000'000; ++i) {
        for (int j = i; j <= 1'000'000; j += i)
            answer_sheet[j] += i;
        answer_sheet[i] += answer_sheet[i - 1];
    }

    return answer_sheet;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    vector<ll> answer = make_answer_sheet();

    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        cout << answer[n] << "\n";    
    }
    
    return 0;
}