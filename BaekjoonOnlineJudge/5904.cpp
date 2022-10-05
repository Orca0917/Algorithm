#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> moo_len(30, 0);

char find_moo(int k, int n) {
    // 기저사례
    if (k == 0) return "moo"[n];

    // 1. 찾고자 하는 index가 처음 S(k - 1) 에 존재하는 경우
    if (n < moo_len[k - 1])
        return find_moo(k - 1, n);

    // 2. 찾고자 하는 index가 중간에 생성되는 mo..o 에 존재하는 경우
    else if (n < moo_len[k - 1] + (k + 3))
        return (n == moo_len[k - 1]) ? 'm' : 'o';

    // 3. 찾고자 하는 index가 마지막 S(k - 1) 에 존재하는 경우
    else
        return find_moo(k - 1, n - (moo_len[k - 1] + (k + 3)));
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;

    // n 는 0부터 시작하는 것으로 가정
    // 따라서 1 감소
    --n;

    moo_len[0] = 3;

    // moo_len(k) = moo_len(k - 1) + (k + 3) + moo_len(k - 1);
    for (int k = 1; k < 30; ++k)
        moo_len[k] = moo_len[k - 1] * 2 + k + 3;

    cout << find_moo(29, n) << "\n";

    return 0;
}