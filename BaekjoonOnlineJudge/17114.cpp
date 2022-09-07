#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct Q {
    vector<int> pos;
    int day;
};

int dim[11];
queue<Q> que;

int d_m[22] = {1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int d_n[22] = {0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int d_o[22] = {0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int d_p[22] = {0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int d_q[22] = {0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int d_r[22] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int d_s[22] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0};
int d_t[22] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0};
int d_u[22] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0};
int d_v[22] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0};
int d_w[22] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int total_tomato = 1;
    for (int i = 0; i < 11; ++i) {
        cin >> dim[i];
        total_tomato *= dim[i];
    }
    
    int board[dim[10]][dim[9]][dim[8]][dim[7]][dim[6]][dim[5]][dim[4]][dim[3]][dim[2]][dim[1]][dim[0]];
    bool vis[dim[10]][dim[9]][dim[8]][dim[7]][dim[6]][dim[5]][dim[4]][dim[3]][dim[2]][dim[1]][dim[0]];

    int answer = 0;
    int riped = 0;
    memset(vis, false, sizeof(vis));
    
    for (int w = 0; w < dim[10]; ++w) for (int v = 0; v < dim[9]; ++v) for (int u = 0; u < dim[8]; ++u)
    for (int t = 0; t < dim[7]; ++t) for (int s = 0; s < dim[6]; ++s) for (int r = 0; r < dim[5]; ++r)
    for (int q = 0; q < dim[4]; ++q) for (int p = 0; p < dim[3]; ++p) for (int o = 0; o < dim[2]; ++o)
    for (int n = 0; n < dim[1]; ++n) for (int m = 0; m < dim[0]; ++m) {
        int &val = board[w][v][u][t][s][r][q][p][o][n][m];
        cin >> val;

        if (val == 1) {
            que.push({{w, v, u, t, s, r, q, p, o, n, m}, 0});
            vis[w][v][u][t][s][r][q][p][o][n][m] = true;
            riped += 1;
        }
        else if (val == -1) total_tomato -= 1;
    }


    auto is_outbound = [](int w, int v, int u, int t, int s, int r, int q, int p, int o, int n, int m) -> bool {
        if (w < 0 || dim[10] <= w) return false;
        if (v < 0 || dim[9] <= v) return false;
        if (u < 0 || dim[8] <= u) return false;
        if (t < 0 || dim[7] <= t) return false;
        if (s < 0 || dim[6] <= s) return false;
        if (r < 0 || dim[5] <= r) return false;
        if (q < 0 || dim[4] <= q) return false;
        if (p < 0 || dim[3] <= p) return false;
        if (o < 0 || dim[2] <= o) return false;
        if (n < 0 || dim[1] <= n) return false;
        if (m < 0 || dim[0] <= m) return false;

        return true;
    };

   

    while (!que.empty()) {
        vector<int> pos = que.front().pos;
        int day = que.front().day;
        que.pop();

        answer = day;
        
        for (int i = 0; i < 22; ++i) {
            int nw = pos[0] + d_w[i];
            int nv = pos[1] + d_v[i];
            int nu = pos[2] + d_u[i];
            int nt = pos[3] + d_t[i];
            int ns = pos[4] + d_s[i];
            int nr = pos[5] + d_r[i];
            int nq = pos[6] + d_q[i];
            int np = pos[7] + d_p[i];
            int no = pos[8] + d_o[i];
            int nn = pos[9] + d_n[i];
            int nm = pos[10] + d_m[i];

            if (!is_outbound(nw, nv, nu, nt, ns, nr, nq, np, no, nn, nm)) continue;
            if (board[nw][nv][nu][nt][ns][nr][nq][np][no][nn][nm] == -1) continue;
            if (vis[nw][nv][nu][nt][ns][nr][nq][np][no][nn][nm]) continue;

            vis[nw][nv][nu][nt][ns][nr][nq][np][no][nn][nm] = true;
            que.push({{nw, nv, nu, nt, ns, nr, nq, np, no, nn, nm}, day + 1});
            riped += 1;
        }
    }

    if (total_tomato == riped) cout << answer << "\n";
    else cout << "-1\n";

    return 0;
}