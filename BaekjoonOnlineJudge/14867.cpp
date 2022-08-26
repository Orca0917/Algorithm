#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int A, B;
int final_A, final_B;

set<pii> s;

struct Q {
    int a;
    int b;
    int cnt;
};

int bfs() {
    s.clear();

    queue<Q> q;
    q.push({0, 0, 0});
    s.insert({0, 0});

    while (!q.empty()) {
        int a = q.front().a;
        int b = q.front().b;
        int cnt = q.front().cnt;
        q.pop();

        // cout << "current status : a(" << a << ") b(" << b << ") cnt(" << cnt << ")\n";

        if (a == final_A && b == final_B) return cnt;


        // 물통 A에 물을 가득 채움
        if (a < A && s.find({A, b}) == s.end()) {
            s.insert({A, b});
            q.push({A, b, cnt + 1});
        }

        // 물통 A에 물을 비움
        if (a > 0 && s.find({0, b}) == s.end()) {
            s.insert({0, b});
            q.push({0, b, cnt + 1});
        }

        // 물통 A에 있는 물을 물통 B로 옮김
        int bb = min(B - b, a);
        if (a > 0 && s.find({a - bb, b + bb}) == s.end()) {
            s.insert({a - bb, b + bb});
            q.push({a - bb, b + bb, cnt + 1});
        }

        // 물통 B에 물을 가득 채움
        if (b < B && s.find({a, B}) == s.end()) {
            s.insert({a, B});
            q.push({a, B, cnt + 1});
        }

        // 물통 B에 물을 비움
        if (b > 0 && s.find({a, 0}) == s.end()) {
            s.insert({a, 0});
            q.push({a, 0, cnt + 1});
        }

        // 물통 B에 있는 물을 물통 A로 옮김
        int aa = min(A - a, b);
        if (b > 0 && s.find({a + aa, b - aa}) == s.end()) {
            s.insert({a + aa, b - aa});
            q.push({a + aa, b - aa, cnt + 1});
        }
    }

    return -1;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> A >> B >> final_A >> final_B;

    cout << bfs() << "\n";
    
    
    return 0;
}