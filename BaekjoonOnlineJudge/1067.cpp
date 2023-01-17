#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define cpx complex<double>
#define PI acos(-1)
using namespace std;

int n;
deque<int> dq1, dq2;

void FFT(vector<cpx> &f, cpx w) {
    int n = (int)f.size();
    if (n == 1) return;

    vector<cpx> even(n / 2);
    vector<cpx> odd(n / 2);

    for (int i = 0; i < n; ++i) {
        if (i % 2) odd[i / 2] = f[i];
        else even[i / 2] = f[i];
    }

    FFT(even, w * w);
    FFT(odd, w * w);
    cpx wp(1, 0);

    for (int i = 0; i < n / 2; ++i) {
        f[i] = even[i] + wp * odd[i];
        f[i + n / 2] = even[i] - wp * odd[i];
        wp *= w;
    }
}


vector<cpx> mul(vector<cpx> a, vector<cpx> b) {
    int n = 1;
    while (n <= a.size() || n <= b.size()) n *= 2;
    n *= 2;

    a.resize(n);
    b.resize(n);
    vector<cpx> c(n);

    cpx w(cos(2 * PI / n), sin(2 * PI / n));

    FFT(a, w);
    FFT(b, w);

    for (int i = 0; i < n; ++i)
        c[i] = a[i] * b[i];

    FFT(c, cpx(1, 0) / w);
    for (int i = 0; i < n; ++i) {
        c[i] /= cpx(n, 0);
        c[i] = cpx(round(c[i].real()), round(c[i].imag()));
    }
    return c;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;

    vector<int> v1(n);
    vector<int> v2(n);

    for (int &e : v1) cin >> e;   
    for (int &e : v2) cin >> e;   
    
    vector<cpx> a(2 * n), b(n);
    for (int i = 0; i < n; ++i) a[i] = a[i + n] = cpx(v1[i], 0);
    for (int i = 0; i < n; ++i) b[n - i - 1] = cpx(v2[i], 0);

    vector<cpx> c = mul(a, b);

    ll answer = 0;
    for (cpx &e : c) answer = max(answer, (ll)round(e.real()));

    cout << answer << "\n";

    return 0;
}