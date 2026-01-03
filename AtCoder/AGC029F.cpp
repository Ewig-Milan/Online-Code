#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 200100, M = 800100, INF = 1e8;

int n, s = 0, t = N - 1;
pair<int, int> ans[100100];
int ans_cnt;
bool vis[100100];

int h[N], e[M], ne[M], ca[M], idx;
void add(int a, int b, int c) {
    e[idx] = b, ca[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ca[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

int can[N], dep[N];
bool bfs() {
    queue<int> q;
    memset(dep, -1, sizeof dep);
    dep[s] = 0, q.push(s);
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        can[x] = h[x];
        if(x == t) return 1;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(dep[j] == -1 && ca[i]) dep[j] = dep[x] + 1, q.push(j);
        }
    }
    return 0;
}

int dfs(int x, int lim) {
    if(x == t) return lim;
    int flow = 0;
    for(int &i = can[x]; ~i && flow < lim; i = ne[i]) {
        int j = e[i];
        if(dep[j] == dep[x] + 1 && ca[i]) {
            int tmp = dfs(j, min(ca[i], lim - flow));
            if(!tmp) dep[j] = -1;
            else flow += tmp, ca[i] -= tmp, ca[i ^ 1] += tmp;
        }
    }
    return flow;
}

int dinic() {
    int mf = 0, tmp;
    while(bfs()) while(tmp = dfs(s, INF)) mf += tmp;
    return mf;
}

int get_ch(int x) {
    for(int i = h[x]; ~i; i = ne[i]) if(e[i] != t && ca[i]) return e[i];
    return 0;
}

void dfs_ans(int x) {
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == s || vis[j - n]) continue;
        vis[j - n] = 1;
        int tmp = get_ch(j);
        ans[j - n] = {x, tmp}, ans_cnt++;
        dfs_ans(tmp);
    }
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) add(s, i, 1);
    for(int i = 1; i < n; i++) {
        add(i + n, t, 1);
        int m; scanf("%d", &m);
        while(m--) {
            int a; scanf("%d", &a);
            add(a, i + n, 1);
        }
    }
    if(dinic() != n - 1) {puts("-1"); return 0;}
    int rt = 0;
    for(int i = h[s]; ~i; i = ne[i]) {
        int j = e[i];
        if(ca[i]) rt = j;
    }
    dfs_ans(rt);
    if(ans_cnt != n - 1) {puts("-1"); return 0;}
    for(int i = 1; i < n; i++)
        printf("%d %d\n", min(ans[i].fi, ans[i].se), max(ans[i].fi, ans[i].se));
    return 0;
}