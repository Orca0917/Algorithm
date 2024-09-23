#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

vector<unsigned int> v;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 가로등의 정보 입력받기
    int n; cin >> n;
    v.resize(n);
    for (auto &e : v) cin >> e;

    // 가로등 사이 거리의 최소공배수가 최소 간격임
    unsigned int gcd = __gcd(v[1] - v[0], v[2] - v[1]);
    for (int i = 3; i < v.size(); ++i) gcd = __gcd(v[i] - v[i - 1], gcd);

    // 전체 설치해야하는 가로등의 수 - 이미 설치된 가로등의 수
    cout <<  (v.back() - v.front()) / gcd + 1 - v.size();
    
    return 0;
}