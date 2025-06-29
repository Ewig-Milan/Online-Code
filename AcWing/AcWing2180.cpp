#include <bits/stdc++.h>
using namespace std;

const int N = 600, M = 1000100, INF = 1e9;

int n, S, T;
int A[N], f[N], ma;
vector<int> ma_id;

int h[M], e[M], ca[M], ne[M], idx;
void add(int a, int b, int c) {
    if(a == b) a = (a << 1) - 1, b <<= 1;
    else {
        if(a != S) a <<= 1;
        if(b != T) b = (b << 1) - 1;
    }
    e[idx] = b, ca[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ca[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

int dep[M], can[M];
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
    for(int & i = can[x]; ~i && flow < lim; i = ne[i]) {
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
    scanf("%d", &n);
    if(n == 1) {
        printf("1\n1\n1");
        return 0;
    }
    S = 0, T = n << 1 | 1;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &A[i]);
        ma_id.resize(0);
        for(int j = 1; j < i; j++) {
            if(A[j] > A[i]) continue;
            if(f[j] + 1 > f[i]) ma_id.resize(0), ma_id.push_back(j), f[i] = f[j] + 1;
            else if(f[j] + 1 == f[i]) ma_id.push_back(j);
        }
        if(!f[i]) f[i] = 1, add(S, i, 1);
        else for(int x : ma_id) add(x, i, 1);
        ma = max(ma, f[i]);
    }
    for(int i = 1; i <= n; i++) add(i, i, 1);
    for(int i = 1; i <= n; i++) if(f[i] == ma) add(i, T, 1);

    int tmp = dinic();
    printf("%d\n%d\n", ma, tmp);
    add(1, 1, INF), add(n, n, INF), add(S, 1, INF);
    if(f[n] == ma) add(n, T, INF);
    printf("%d", tmp + dinic());
    return 0;
}