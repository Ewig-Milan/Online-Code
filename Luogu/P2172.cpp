#include <bits/stdc++.h>
using namespace std;

const int N = 5100, M = 35100, INF = 1e9;

int n, m, c, r, S, T;
int id[N][N], inc;

int h[N], e[M], ca[M], ne[M], idx;
void add(int a, int b, int c) {
    if(a != S && b != T) a = (a << 1) - 1, b <<= 1;
    if(a == S) b = (b << 1) - 1;
    if(b == T) a <<= 1;
    e[idx] = b, ca[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ca[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

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
    while(bfs()) while(tmp = dfs(S, INF)) mf += tmp;
    return mf;
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d%d%d", &m, &n, &r, &c);
    S = 0, T = N - 1;
    for(int i = 1; i <= m; i++) {
        char ch[60]; scanf("%s", ch + 1);
        for(int j = 1; j <= n; j++) {
            if(ch[j] == 'x') continue;
            id[i][j] = ++inc;
            if(i - r > 0 && j - c > 0 && id[i - r][j - c])
                add(id[i - r][j - c], inc, 1);
            if(i - r > 0 && j + c > 0 && id[i - r][j + c])
                add(id[i - r][j + c], inc, 1);
            if(i - c > 0 && j - r > 0 && id[i - c][j - r])
                add(id[i - c][j - r], inc, 1);
            if(i - c > 0 && j + r > 0 && id[i - c][j + r])
                add(id[i - c][j + r], inc, 1);
            add(S, inc, 1), add(inc, T, 1);
        }
    }
    printf("%d", inc - dinic());
    return 0;
}