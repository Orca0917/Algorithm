#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n;  // 세로
int m;  // 가로
int k;  // 색상의 수

vector<int> a;
vector<int> result;

int check_possible(int val, ll targ) {
    ll possible = 0;
    bool over2 = false;

    // 같은 색으로 몇 줄 칠할 수 있는지?
    for (int i = 0; i < k; ++i) result[i] = a[i] / val;

    // 전체를 색칠할 수 있는지 확인
    for (int i = 0; i < k; ++i) {
        if (result[i] >= 2) possible += result[i];
        if (result[i] > 2) over2 = true;
    }

    // over2 : 마지막 1줄이 남는 경우를 채우기 위함
    // targ가 2로 나누어 떨어지는 경우, over2가 필요x
    return (possible >= targ) && (over2 || targ % 2 == 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        cin >> n >> m >> k;

        a.resize(k, 0);
        result.resize(k, 0);

        for (int i = 0; i < k; ++i) cin >> a[i];

        bool pos1 = check_possible(n, m);
        bool pos2 = check_possible(m, n);

        if (pos1 || pos2) cout << "Yes\n";
        else cout << "No\n";
        
    }
    
    return 0;
}