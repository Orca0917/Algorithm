#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 200000

using namespace std;

struct QUERY {
    int option;
    ll val1;
    ll val2;
};      

bool is_always_zero = false;    // 항상 0인 값을 갖는지
bool is_negative = false;       // 식의 부호 시작이 음수인지
int Q;                          // 쿼리의 개수
int option;                     // 쿼리의 종류
ll a, b, c;

set<ll> reindex_set;           // 값 축소를 위한 set
set<ll> exact_value;            // 정확히 x 값이 들어오면 0이 되는 것
map<ll, int> m;                 // 압축된 값의 정보 저장
queue<QUERY> query_q;           // 쿼리의 정보
vector<int> tree_pos, tree_neg; // 세그먼트 트리 (summation)


int init_tree(vector<int> &tree, int node, int start, int end) {
    if (start == end) return tree[node] = 0;
    
    int mid = (start + end) / 2;
    int l = init_tree(tree, node * 2, start, mid);
    int r = init_tree(tree, node * 2 + 1, mid + 1, end);

    return tree[node] = l + r; 
}


int update_tree(vector<int> &tree, int node, int start, int end, int value) {
    if (value < start || end < value) return tree[node];
    else if (start == end && end == value) {
        return tree[node] += 1;
    }

    int mid = (start + end) / 2;
    int l = update_tree(tree, node * 2, start, mid, value);
    int r = update_tree(tree, node * 2 + 1, mid + 1, end, value);

    return tree[node] = l + r;
}


int query_tree(vector<int> &tree, int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    int l = query_tree(tree, node * 2, start, mid, left, right);
    int r = query_tree(tree, node * 2 + 1, mid + 1, end, left, right);

    return l + r;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> Q;
    
    for (int i = 0; i < Q; ++i) {
        cin >> option;
        if (option == 1) {
            cin >> a >> b;
            query_q.push({option, a, b});

            // 0 인것은 해가 없음
            if (a == 0) continue;

            if (b % a == 0) {
                ll value = -b / a;
                if (a < 0) reindex_set.insert(value + 1);
                else reindex_set.insert(value - 1);
            }

            else {
                long double value = -b / (long double) a;
                if (a < 0) reindex_set.insert((ll)ceil(value));
                else reindex_set.insert((ll)floor(value));
            }
        }

        else if (option == 2) {
            cin >> c;
            query_q.push({option, c, 0});
            reindex_set.insert(c);
        }
    }


    // 값 압축 진행
    int new_val = 1;
    for (auto it = reindex_set.begin(); it != reindex_set.end(); ++it) m[*it] = new_val++;

    // 세그먼트 트리 크기 지정
    int tree_height = (int)ceil(log2(MAX + 1));
    int tree_size = (1 << (tree_height + 1));

    tree_pos.resize(tree_size);
    tree_neg.resize(tree_size);

    // 세그먼트 트리 초기화
    init_tree(tree_pos, 1, 1, MAX);
    init_tree(tree_neg, 1, 1, MAX);

   
    // 쿼리 수행
    while (!query_q.empty()) {
        QUERY now = query_q.front(); query_q.pop();
        /**
         * QUERY now
         * now.option : 현재 쿼리의 옵션
         * now.val1 : a 또는 c
         * now.val2 : b
         */

        // Query 1. (ax + b)
        if (now.option == 1) {

            if (now.val1 == 0) {
                if (now.val2 == 0) is_always_zero = true;
                else if (now.val2 < 0) is_negative ^= (true ^ false);
            }

            else {
                
                if (now.val2 % now.val1 == 0) {
                    ll exact_val = -now.val2 / now.val1;
                    exact_value.insert(exact_val);

                    if (now.val1 > 0) update_tree(tree_pos, 1, 1, MAX, m[exact_val - 1]);
                    else update_tree(tree_neg, 1, 1, MAX, m[exact_val + 1]);
                }

                else {
                    long double ans_val = -now.val2 / (long double)now.val1;
                    if (now.val1 > 0) update_tree(tree_pos, 1, 1, MAX, m[floor(ans_val)]);
                    else update_tree(tree_neg, 1, 1, MAX, m[ceil(ans_val)]);
                }
            }
        }

        // Query 2. x에 c를 삽입한 전체 결과
        else if (now.option == 2) {

            // 항상 0인 값을 출력해야 하는 경우    
            if (is_always_zero) { cout << "0\n"; continue; }

            // 현재 값이 들어왔을 때, 정확히 0이 되는 식이 존재하는 경우
            auto it = exact_value.lower_bound(now.val1);
            if (it != exact_value.end() && *it == now.val1) { cout << "0\n"; continue; }

            // 식이 음수인 경우
            int neg_cnt = query_tree(tree_neg, 1, 1, MAX, 1, m[now.val1]);
            int pos_cnt = query_tree(tree_pos, 1, 1, MAX, m[now.val1], MAX);

            if ((neg_cnt + pos_cnt + (int)is_negative) % 2) cout << "-\n";
            else cout << "+\n";
        }
    }
    
    return 0;
}