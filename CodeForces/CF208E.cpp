#include <bits/stdc++.h>
#define ID first
#define dp second
using namespace std;

const int N = 100100;

int n, m, ans[N];
vector<pair<int, int> > Q[N];

int h[N], e[N], ne[N], idx;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int siz[N], ma_s[N], L[N], R[N];
int cnt, id[N], dep[N], fa[N][18]/*开18用17下取整16(1e5)*/;
void dfs_pre(int x, int l) {
    dep[x] = l >= 0 ? dep[l] + 1 : 0, L[x] = ++cnt, id[cnt] = x;
    siz[x] = 1, fa[x][0] = l >= 0 ? l : 0;
    for(int i = 1; i <= 17; i++) fa[x][i] = fa[fa[x][i - 1]][i - 1];
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        dfs_pre(j, x);
        siz[x] += siz[j];
        if(siz[j] > siz[ma_s[x]]) ma_s[x] = j;
    }
    R[x] = cnt;
}

int get_p(int v, int p/*要达到的dep*/) {
    for(int i = 17; i >= 0; i--)
        if(dep[fa[v][i]] >= p) v = fa[v][i];
    return v;
}

int mp[N];//下标深度 存个数
void dfs(int x, bool keep) {
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == ma_s[x]) continue;
        dfs(j, 0);
    }
    if(ma_s[x]) dfs(ma_s[x], 1);
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == ma_s[x]) continue;
        for(int k = L[j]; k <= R[j]; k++)  mp[dep[id[k]]]++;
    }
    mp[dep[x]]++;
    for(auto i : Q[x]) ans[i.ID] = mp[i.dp] - 1;
    if(!keep) for(int i = dep[x]; mp[i]; i++) mp[i] = 0;
}

int main() {
    scanf("%d", &n);
    memset(h, -1, sizeof(h));
    for(int i = 1; i <= n; i++) {
        int a; scanf("%d", &a);
        add(a, i);
    }
    dfs_pre(0, -1);
    scanf("%d", &m);
    for(int i = 1; i <= m; i++) {
        int v, p; scanf("%d%d", &v, &p);
        if(dep[v] - p <= 0) {
            ans[i] = 0;
            continue;
        }
        int P = get_p(v, dep[v] - p);
        Q[P].push_back({i, p + dep[P]});
    }
    dfs(0, 1);
    for(int i = 1; i <= m; i++) printf("%d ", ans[i]);
    return 0;
}