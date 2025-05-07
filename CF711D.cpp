#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 200100, mod = 1e9 + 7;

ll quick_p(ll x, int a) {
    ll ans = 1;
    while(a) {
        if(a & 1) ans *= x, ans %= mod;
        x *= x, x %= mod;
        a >>= 1;
    }
    return ans;
}

int n;
ll ans = 1;
int ring[N]/*len - 1*/, siz[N], cnt;

int h[N], e[N << 1], ne[N << 1], idx;
void add(int a, int b) {e[idx] = b; ne[idx] = h[a], h[a] = idx++;}

bool flag[N];
int dfn[N], low[N], tj_cnt;
stack<int> S;
void tarjan(int x, int l) {
    dfn[x] = low[x] = ++tj_cnt, siz[cnt]++;
    S.push(x);
    flag[x] = true;
    bool tmp = true;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l && tmp) {
            tmp = false;
            continue;
        }
        if(!dfn[j]) {
            tarjan(j, x);
            low[x] = min(low[x], low[j]);
        } else if(flag[j]) low[x] = min(low[x], low[j]);
    }
    if(dfn[x] == low[x]) {
        while(S.top() != x) {
            flag[S.top()] = false;
            S.pop();
            ring[cnt]++;
        }
        S.pop();
    }
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        int a; scanf("%d", &a);
        add(a, i); add(i, a);
    }
    for(int i = 1; i <= n; i++) if(!dfn[i]) {
        cnt++;
        tarjan(i, 0);
    }
    for(int i = 1; i <= cnt; i++) {
        ans *= (quick_p(2, siz[i]) - quick_p(2, siz[i] - ring[i]) + mod) % mod;
        ans %= mod;
    }
    printf("%lld", ans);
    return 0;
}