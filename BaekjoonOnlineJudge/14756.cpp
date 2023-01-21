#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define cpx complex<double>

using namespace std;

void FFT(vector<cpx> &f, bool do_inv) {
    int n = (int)f.size();

    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        while (!((j ^= bit) & bit)) bit >>= 1;
        if (i < j) swap(f[i], f[j]);
    }

    for (int i = 1; i < n; i <<= 1) {
        double x = (do_inv ? M_PI / i : -M_PI / i);
        cpx w = cpx(cos(x), sin(x));
        for (int j = 0; j < n; j += i << 1) {
            cpx p = cpx(1, 0);
            for (int k = 0; k < i; ++k) {
                cpx temp = f[i + j + k] * p;
                f[i + j + k] = f[j + k] - temp;
                f[j + k] += temp;
                p *= w;
            }
        }
    }

    if (do_inv)
        for (int i = 0; i < n; ++i)
            f[i] /= n;
}

vector<cpx> multiply(vector<int> v1, vector<int> v2) {
    int n = 1;
    while (n <= v1.size() || n <= v2.size()) n <<= 1;
    n <<= 1;

    vector<cpx> a(v1.begin(), v1.end());
    vector<cpx> b(v2.begin(), v2.end());
    a.resize(n);
    b.resize(n);
    vector<cpx> ret(n);

    FFT(a, false);
    FFT(b, false);

    for (int i = 0; i < n; ++i) ret[i] = a[i] * b[i];

    FFT(ret, true);

    for (int i = 0; i < n; ++i)
        ret[i] = cpx(round(ret[i].real()), round(ret[i].imag()));

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, l, m;
    ll w;
    cin >> n >> l >> m >> w;

    vector<int> lines[101];
    vector<int> kernels[101];

    // 지도
    for (int i = 0; i < m; ++i) {
        lines[i].resize(n, 0);
        for (int &e : lines[i]) cin >> e;
    }

    // 커널
    for (int i = 0; i < m; ++i) {
        kernels[i].resize(l, 0);
        for (int j = l - 1; j >= 0; --j) cin >> kernels[i][j];
    }

    // 지도와 각 커널에 대해서 FFT
    vector<cpx> ret[101];
    for (int i = 0; i < m; ++i) {
        ret[i] = multiply(lines[i], kernels[i]);
    }

    int answer = 0;
    for (int i = l - 1; i < n; ++i) {
        ll sum = 0;
        for (int j = 0; j < m; ++j) {
            sum += (int)round(ret[j][i].real());
        }
        if (sum > w) ++answer;
    }

    cout << answer << "\n";

    
    return 0;
}