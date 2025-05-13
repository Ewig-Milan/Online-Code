#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
using namespace std;

const int N = 50100, M = 100100;

int n, m, st[N];

bool stay[N];
int rema[N];
vector<pair<int, int> > cent, need;

int h[N], e[M], ne[M], idx;
ll w[M];
void add(int a, int b, ll c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int fa[N][17];
ll sum[N][17];
void dfs_pre(int x, int l, int v) {
    fa[x][0] = l, sum[x][0] = v;
    for(int i = 1; i <= 16; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
        sum[x][i] = sum[x][i - 1] + sum[fa[x][i - 1]][i - 1];
    }
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        dfs_pre(j, x, w[i]);
    }
}

bool dfs_check(int x, int l) {
    if(ne[h[x]] == -1) return false;
    bool flag = true;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l || stay[j]) continue;
        bool temp = dfs_check(j, x);
        flag &= temp;
        if(!temp && x == 1) need.push_back({w[i], j});
        if(temp) stay[j] = true;
    }
    if(x == 1) {
        sort(need.begin(), need.end());
        if(need.size() > cent.size()) return false;
        int i = 0/*need*/, j = 0/*cent*/;
        while(i < need.size() && j < cent.size()) {
            if(!stay[cent[j].se]) stay[cent[j].se] = true;
            else {
                while(i < need.size() && stay[need[i].se]) i++;
                if(j < cent.size() && i < need.size() && cent[j].fi >= need[i].fi) stay[need[i].se] = true, i++;
            }
            while(i < need.size() && stay[need[i].se]) i++;
            j++;
        }
        if(i < need.size()) return false;
        else return true;
    }
    return flag;
}

bool check(ll tim) {
    memset(stay, 0, sizeof(stay));
    memset(rema, 0, sizeof(rema));
    cent.resize(0);
    need.resize(0);
    for(int i = 1; i <= m; i++) {
        int tmp = st[i], t_tim = tim, f = tmp;
        for(int j = 16; j >= 0; j--)
            if(fa[f][j] > 1) f = fa[f][j];
        
        for(int j = 16; j >= 0; j--)
            if(t_tim >= sum[tmp][j])
                t_tim -= sum[tmp][j], tmp = fa[tmp][j];
        if(tmp) stay[tmp] = true;
        else cent.push_back({t_tim, f});
    }
    sort(cent.begin(), cent.end());
    return dfs_check(1, 0);
}

int main() {
    memset(h, -1, sizeof(h));
    scanf("%d", &n);
    ll l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        int a, b; ll c; scanf("%d%d%lld", &a, &b, &c);
        add(a, b, c); add(b, a, c);
        r += c;
    }
    scanf("%d", &m);
    for(int i = 1; i <= m; i++) scanf("%d", &st[i]);
    dfs_pre(1, 0, 0);
    while(l < r) {
        ll mid = l + r >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    printf("%lld", check(l) ? l : -1);
    return 0;
}