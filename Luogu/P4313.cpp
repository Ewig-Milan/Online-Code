#include <bits/stdc++.h>
using namespace std;

const int N = 30100, M = 320100, INF = 1e9;

int n, m, s = 0, t = N - 1;
int id[110][110];
int I(int x, int y) {return x + 10000 * y;}
int sum;

int h[N], e[M], ca[M], ne[M], idx;
void add(int a, int b, int c) {
    e[idx] = b, ca[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ca[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

int dep[N], can[N];
bool bfs() {
    memset(dep, -1, sizeof dep);
    queue<int> q;
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

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    int tmp = 0;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) id[i][j] = ++tmp;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
        int a; scanf("%d", &a);
        sum += a, add(id[i][j], t, a);
    }
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
        int a; scanf("%d", &a);
        sum += a, add(s, id[i][j], a);
    }
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
        int a; scanf("%d", &a);
        sum += a, add(I(id[i][j], 2), t, a);
    }
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
        int a; scanf("%d", &a);
        sum += a, add(s, I(id[i][j], 1), a);
    }
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
        vector<int> ADD;
        ADD.push_back(id[i][j]); if(i > 1) ADD.push_back(id[i - 1][j]); if(i < n) ADD.push_back(id[i + 1][j]);
        if(j > 1) ADD.push_back(id[i][j - 1]); if(j < m) ADD.push_back(id[i][j + 1]);
        for(int x : ADD) add(I(id[i][j], 1), x, INF), add(x, I(id[i][j], 2), INF);
    }
    printf("%d", sum - dinic());
    return 0;
}