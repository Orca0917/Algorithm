#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n; // 사탕의 개수
int w; // 무게의 제한
int t; // 사탕의 종류 (3g, 5g)
int s; // 사탕의 당도

vector<int> candy3, candy5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> w;

    for (int i = 0; i < n; ++i) {
        cin >> t >> s;
        if (t == 3) candy3.push_back(s);
        else candy5.push_back(s);
    }

    if (!candy3.empty()) sort(candy3.rbegin(), candy3.rend());
    if (!candy5.empty()) sort(candy5.rbegin(), candy5.rend());

    vector<ll> psum3, psum5;
    psum3.push_back(0);
    psum5.push_back(0);

    for (int i = 0; i < candy3.size(); ++i) psum3.push_back(psum3.back() + candy3[i]);
    for (int i = 0; i < candy5.size(); ++i) psum5.push_back(psum5.back() + candy5[i]);

    ll answer = 0;
    for (int get3 = 0, get5 = 0; get3 * 3 <= w; ++get3) {
        get5 = (w - 3 * get3) / 5;

        int g3 = min(get3, (int)candy3.size());
        int g5 = min(get5, (int)candy5.size());
        
        answer = max(answer, psum3[g3] + psum5[g5]);
    }

    cout << answer << "\n";

    return 0;
}