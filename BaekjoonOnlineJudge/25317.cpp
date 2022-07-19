#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>

using namespace std;

int n; // 쿼리의 개수
int pos_set_size = 0;
int a_zero_b_neg = 0; // a == 0, b < 0
ll option, a, b, c;

bool always_zero = false;

multiset<ld> pos_set; // a > 0
multiset<ld> neg_set; // a < 0
set<ll> exact_value; // b % a == 0

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;

    for (int i = 0; i < n; ++i) {   // n

        cin >> option;

        if (option == 1) {

            cin >> a >> b;

            if (a == 0) {
                if (b < 0) a_zero_b_neg += 1;
                else if (b == 0) always_zero = true;
                continue;
            }

            if (b % a == 0) exact_value.insert(-b / a);

            if (a < 0) neg_set.insert(-b / (ld)a);
            else if (a > 0) pos_set.insert(-b / (ld)a);

        } 
        
        else if (option == 2) {

            cin >> c;

            if (always_zero) {
                cout << "0\n";
                continue;
            }

            // 1. 0이 되는 값을 찾음
            auto exact_it = exact_value.find(c); // O(lg N)
            if (exact_it != exact_value.end()) {
                cout << "0\n";
                continue;
            }

            int under_cnt = 0, under_cnt2 = 0;

            auto neg_it = neg_set.lower_bound((ld)c); // O(lg N)
            if (neg_it == neg_set.end()) under_cnt = neg_set.size();
            else under_cnt = distance(neg_set.begin(), neg_it);

            auto pos_it = pos_set.lower_bound((ld)c); // O(lg N)
            if (pos_it == pos_set.end()) under_cnt2 = 0;
            else under_cnt2 = pos_set.size() - distance(pos_set.begin(), pos_it);

            // cout << under_cnt << ", " << under_cnt2 << "\n";

            if ((under_cnt + under_cnt2) % 2) {
                if (a_zero_b_neg % 2) cout << "+\n";
                else cout << "-\n";
            } else {
                if (a_zero_b_neg % 2) cout << "-\n";
                else cout << "+\n";
            }
        }
    }
    
    
    return 0;
}