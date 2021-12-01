#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n; // number of verticies

        vector<int> parent(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> parent[i]; // parent[i] = node i's parent
        }

        vector<int> sequence(n + 1);
        for (int i = 1; i <= n; ++i) {
            int node; cin >> node;
            sequence[node] = i; // sequence[i] = node i's index.
        }

        for (int i = 1; i <= n; ++i) {
            if (sequence[parent[i]] > sequence[i]) {
                cout << "-1\n";
                goto A;
            }
        }

        for (int i = 1; i <= n; ++i)
            cout << sequence[i] - sequence[parent[i]] << "\n";
        cout << "\n";

        A:;
    }
}