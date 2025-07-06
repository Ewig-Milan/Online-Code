#include <bits/stdc++.h>
#define PII pair<int, int>
#define db double
using namespace std;

const int N = 900, M = 1000100, INF = 1e9;
const db eps = 1e-9;

int n, m, d, tot;
int S, T;

map<PII, int> mp;
int p_cnt;
struct Node {
    int x, y;
    db dist(const Node &o) const {return sqrt((x - o.x) * (x - o.x) + (y - o.y) * (y - o.y));}
}pillar[N];

int h[N], e[M], ca[M], ne[M], idx;
void add(int a, int b, int c) {
    if(a == b) a = (a << 1) - 1, b <<= 1;
    else {
        if(a != S) a <<= 1;
        if(b != T) b = (b << 1) - 1;
    }
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
            int tmp = dfs(j, min(lim - flow, ca[i]));
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
    scanf("%d%d%d", &n, &m, &d);
    S = 0, T = N - 1;
    for(int i = 1; i <= n; i++) {
        char c[30]; scanf("%s", c + 1);
        for(int j = 1; j <= m; j++) {
            int height = c[j] - '0';
            if(height) {
                mp[{i, j}] = ++p_cnt;
                pillar[p_cnt].x = j;
                pillar[p_cnt].y = i;
                add(p_cnt, p_cnt, height);
                if(i <= d || j <= d || n < i + d || m < j + d) add(p_cnt, T, INF);
            }
        }
    }
    for(int i = 1; i <= p_cnt; i++) for(int j = i + 1; j <= p_cnt; j++)
        if(pillar[i].dist(pillar[j]) - d <= eps) add(i, j, INF), add(j, i, INF);
    for(int i = 1; i <= n; i++) {
        char c[30]; scanf("%s", c + 1);
        for(int j = 1; j <= m; j++) if(c[j] == 'L') add(S, mp[{i, j}], 1), tot++;
    }
    printf("%d", tot - dinic());
    return 0;
}