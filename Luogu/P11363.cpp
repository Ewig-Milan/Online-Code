#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 100100, mod = 1e9 + 7;

int nothing, T;
int n, k;
int inv[N];

vector<pair<int, int> > E;
bool edg[N];
int f[N], ans;

// 有点权、边标号
int d[N], w[N];
int h[N], e[N << 1], v[N << 1], ne[N << 1], idx;
void add(int a, int b, int c) {
    d[a]++, e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
    d[b]++, e[idx] = a, v[idx] = c, ne[idx] = h[b], h[b] = idx++;
}

void DP(int x, int l) {
    for(int i = h[x]; ~i; i = ne[i]) {
        if((i ^ 1) == l) continue;
        int j = e[i];
        DP(j, i);
        f[x] += f[j], f[x] %= mod;
    }
    int pre = 0;
    if(l != -1 && v[l]) f[x] = pre = 1, ans++;
    else f[x] *= w[x], f[x] %= mod;
    for(int i = h[x]; ~i; i = ne[i]) {
        if((i ^ 1) == l) continue;
        int j = e[i];
        ans -= pre * f[j] % mod * w[x] % mod;
        ans %= mod, ans += mod, ans %= mod;
        pre += f[j], pre %= mod;
    }
}

int fact(int x) {
    int res = 1;
    for(int i = 1; i <= x; i++) res *= i, res %= mod;
    return res;
}
void prepare() {
    inv[1] = inv[0] = 1;
    for(int i = 2; i < N; i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
}
void cl() {
    ans = idx = 0;
    E.resize(0);
    memset(h, -1, sizeof h);
    memset(f, 0, sizeof f);
    memset(edg, 0, sizeof edg);
    memset(d, 0, sizeof d);
}

signed main() {
    prepare();
    scanf("%lld%lld", &nothing, &T);
    while(T--) {
        cl();
        scanf("%lld%lld", &n, &k);
        for(int i = 1; i < n; i++) {
            int a, b; scanf("%lld%lld", &a, &b);
            E.push_back({a, b});
        }
        for(int i = 1; i <= k; i++) {
            int a; scanf("%lld", &a);
            edg[a] = 1;
        }
        for(int i = 1; i < n; i++)
            if(edg[i]) add(E[i - 1].first, E[i - 1].second, 1);
            else add(E[i - 1].first, E[i - 1].second, 0);
        
        int ANS = 1;
        for(int i = 1; i <= n; i++) w[i] = inv[d[i] - 1], ANS *= fact(d[i] - 1), ANS %= mod;

        DP(1, -1); // 后面传的是父亲边
        
        printf("%lld\n", ans * ANS % mod);
    }
    return 0;
}