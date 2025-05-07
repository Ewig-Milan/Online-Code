#include <bits/stdc++.h>
#define ID first
#define dp second
using namespace std;

const int N = 100100;

int n, m, nam[N], cnt_mp, ans[N];
vector<pair<int, int> > Q[N];//直接存的dep (k->dep)

int h[N], e[N], ne[N], idx;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int siz[N], L[N], R[N], id[N], ma_s[N], cnt, dep[N];
void dfs_pre(int x, int l) {
    L[x] = ++cnt, id[cnt] = x, siz[x] = 1;
    dep[x] = l >= 0 ? dep[l] + 1 : 0/*更正一下 之前能过是没想到的*/;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        dfs_pre(j, x);
        siz[x] += siz[j];
        if(siz[j] > siz[ma_s[x]]) ma_s[x] = j;
    }
    R[x] = cnt;
}

set<int> nm_mp[N];//下标是dep
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
        for(int k = L[j]; k <= R[j]; k++) {
            int t = id[k];
            nm_mp[dep[t]].insert(nam[t]);
        }
    }
    nm_mp[dep[x]].insert(nam[x]);
    for(auto i : Q[x]) ans[i.ID] = nm_mp[i.dp].size();
    if(!keep) for(int i = dep[x]; !nm_mp[i].empty(); i++) nm_mp[i].clear();
}

map<string, int> mp;
int main() {
    memset(h, -1, sizeof(h));
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        char s[30]; int b; scanf("%s %d", s, &b);
        add(b, i);
        if(mp[s]) nam[i] = mp[s];
        else mp[s] = ++cnt_mp, nam[i] = cnt_mp;
    }
    dfs_pre(0, -1);
    scanf("%d", &m);
    for(int i = 1; i <= m; i++) {
        int a, k; scanf("%d%d", &a, &k);
        Q[a].push_back({i, k + dep[a]});
    }
    dfs(0, 1);
    for(int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}