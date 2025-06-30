#include <bits/stdc++.h>
using namespace std;

const int N = 1000100, M = 100, INF = 1e9;

int n, m, k, S, T, D;
struct Bus {int r, sta[M], h;} B[M];

int p, id[M];
void upd_id() {for(int i = 0; i <= n + 1; i++) id[i] = ++p;}

int h[N], e[N], ca[N], ne[N], idx;
void add(int a, int b, int c) {
    e[idx] = b, ca[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ca[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

int fa[M];
int find(int x) {
    if(fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}
void merge(int a, int b) {fa[find(a)] = find(b);}

int dep[N], can[N];
bool bfs() {
    memset(dep, -1, sizeof dep);
    queue<int> q;
    dep[S] = 0, q.push(S);
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        can[x] = h[x];
        if(x == T) return true;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(dep[j] == -1 && ca[i]) dep[j] = dep[x] + 1, q.push(j);
        }
    }
    return false;
}

int dfs(int x, int lim) {
    if(x == T) return lim;
    int flow = 0;
    for(int i = can[x]; ~i && flow < lim; i = ne[i]) {
        can[x] = i;
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
    while(bfs()) while(tmp = dfs(S, INF)) mf += tmp;
    return mf;
}

int main() {
    memset(h, -1, sizeof h);
    for(int i = 0; i < M; i++) fa[i] = i;

    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= m; i++) {
        scanf("%d%d", &B[i].h, &B[i].r);
        for(int j = 0; j < B[i].r; j++) {
            scanf("%d", &B[i].sta[j]);
            if(B[i].sta[j] == -1) B[i].sta[j] = n + 1;
            if(!B[i].sta[j]) B[i].sta[j] = 0;
            merge(B[i].sta[j], B[i].sta[0]);
        }
    }
    if(find(0) != find(n + 1)) {
        puts("0");
        return 0;
    }

    T = 0, S = 1, upd_id();
    while(++D) {
        upd_id();
        for(int i = 0; i <= n + 1; i++) add(id[i] - n - 2, id[i], INF);
        for(int i = 1; i <= m; i++) {
            int la = B[i].sta[(D - 1) % B[i].r], nw = B[i].sta[D % B[i].r];
            add(id[la] - n - 2, id[nw], B[i].h);
        }
        add(id[n + 1], T, INF);
        k -= dinic();
        if(k <= 0) break;
    }
    printf("%d", D);
    return 0;
}