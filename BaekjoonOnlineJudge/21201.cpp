#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int num_people; cin >> num_people;

    vector<int> value(num_people);
    vector<bool> is_alive(num_people, true);
    list<int> li;
    vector<list<int>::iterator> q_iter;
    set<int> here;

    vector<vector<int>> answer;

    for (int i = 0; i < num_people; ++i) {
        cin >> value[i];
        here.insert(i);
        li.push_back(i);
        q_iter.push_back(prev(li.end()));
    }

    while (!here.empty()) {
        set<int> there;
        vector<int> res;

        for (int index : here) {
            list<int>::iterator it = q_iter[index];
            if (it != li.begin() && value[*it] < value[*prev(it)]) is_alive[index] = false;
            if (next(it) != li.end() && value[*it] < value[*next(it)]) is_alive[index] = false;

            if (!is_alive[index]) {
                res.push_back(index);
                if (it != li.begin()) there.insert(*prev(it));
                if (next(it) != li.end()) there.insert(*next(it));
            }
        }

        for (int index : here) if (!is_alive[index]) li.erase(q_iter[index]);

        sort(res.begin(), res.end());

        if (!res.empty()) answer.push_back(res);
        here.clear();
        for (int nidx : there) if (is_alive[nidx]) here.insert(nidx);
    }

    cout << answer.size() << "\n";
    for (vector<int> v : answer) {
        for (int e : v) cout << value[e] << " ";
        cout << "\n";
    }

    for (int e : li) cout << value[e] << " ";


    
    return 0;
}