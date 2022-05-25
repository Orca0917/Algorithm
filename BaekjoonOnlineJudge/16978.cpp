#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct query_opt1 {
    int elem_index;
    int new_value;
};

struct query_opt2 {
    int query_index;
    int kth_query;
    int left;
    int right;
};

int n, m;
vector<int> arr;
vector<ll> tree;
vector<query_opt1> update_queries;
vector<query_opt2> question_queries;

void init_tree() {
    int tree_size = n * 4 + 4;
    tree.resize(tree_size);
}

ll make_tree(int node, int left, int right) {
    if (left == right) {
        return tree[node] = 1LL * arr[left];
    }

    int mid = (left + right) / 2;
    return tree[node] = make_tree(node * 2, left, mid) + make_tree(node * 2 + 1, mid + 1, right);
}

void update_tree(int node, int left, int right, int index, int diff) {
    if (index < left || right < index) return;

    tree[node] += 1LL * diff;

    if (left != right) {
        int mid = (left + right) / 2;
        update_tree(node * 2, left, mid, index, diff);
        update_tree(node * 2 + 1, mid + 1, right, index, diff);
    }
}

// current node range : [left, right]
// question range : [start, end]
ll query_tree(int node, int left, int right, int start, int end) {
    if (end < left || right < start) return 0LL;
    if (start <= left && right <= end) return tree[node];

    int mid = (left + right) / 2;
    return query_tree(node * 2, left, mid, start, end) + query_tree(node * 2 + 1, mid + 1, right, start, end);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;
    arr.resize(n);
    for (int &element : arr) cin >> element;

    // init tree size
    init_tree();

    // make tree
    make_tree(1, 0, n - 1);

    cin >> m;
    int query_option;
    for (int idx = 0; idx < m; ++idx) {
        cin >> query_option;
        if (query_option == 1) {
            int elem_index, new_value;
            cin >> elem_index >> new_value;
            update_queries.push_back({elem_index, new_value});
        }

        else if (query_option == 2) {
            int kth, left, right;
            cin >> kth >> left >> right;
            question_queries.push_back({idx, kth, left, right});
        }
    }

    sort(question_queries.begin(), question_queries.end(), [](const query_opt2 &a, const query_opt2 &b) {
        return a.kth_query < b.kth_query;
    });

    // process update + queries
    vector<pair<int, ll>> answers;
    int query_idx = 0;
    for (int idx = 0; idx <= update_queries.size(); ++idx) {

        while (query_idx < question_queries.size() && question_queries[query_idx].kth_query == idx) {
            query_opt2 &query = question_queries[query_idx];
            ll result = query_tree(1, 0, n - 1, query.left - 1, query.right - 1);
            answers.push_back({query.query_index, result});
            ++query_idx;
        }

        if (idx == update_queries.size()) break;
        int change_idx = update_queries[idx].elem_index - 1;
        update_tree(1, 0, n - 1, change_idx, update_queries[idx].new_value - arr[change_idx]);
        arr[change_idx] = update_queries[idx].new_value;
    }

    sort (answers.begin(), answers.end(), [](const pair<int, ll> &a, const pair<int, ll> &b) {
        return a.first < b.first;
    });

    for (pair<int, ll> &elem : answers) {
        cout << elem.second << "\n";
    }

    return 0;
}