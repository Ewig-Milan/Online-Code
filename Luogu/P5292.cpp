#include <bits/stdc++.h>
using namespace std;

const int N = 5100, M = 1000100;

int n, m, q;
bool ans[N][N];
bool p[N];
struct Edge {int a, b;};
vector<Edge> E, E_es;

int h[N], e[M], ne[M], idx;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ne[idx] = h[b], h[b] = idx++;
}

int col[N];
bool flag;
void dfs(int x, int l) {
    col[x] = (col[l] ^ 1);
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        if(col[j] == -1) E_es.push_back({j, x}), dfs(j, x);
        if(col[j] == col[x] && !flag) E_es.push_back({j, x}), flag = 1;
    }
}
void work() {
    memset(col, -1, sizeof col);
    col[0] = 0;
    for(int i = 1; i <= n; i++) if(col[i] == -1) flag = 0, dfs(i, 0);
}

void bfs() {
    queue<Edge> q;
    for(int i = 1; i <= n; i++) q.push({i, i}), ans[i][i] = 1;
    for(Edge x : E_es) if(p[x.a] == p[x.b]) {
        int a = min(x.a, x.b), b = max(x.a, x.b);
        q.push({a, b}), ans[a][b] = 1;
    }
    while(!q.empty()) {
        Edge x = q.front();
        q.pop();
        int a = x.a, b = x.b;
        for(int i1 = h[a]; ~i1; i1 = ne[i1]) {
            int j1 = e[i1];
            for(int i2 = h[b]; ~i2; i2 = ne[i2]) {
                int j2 = e[i2];
                int A = min(j1, j2), B = max(j1, j2);
                if(!ans[A][B] && p[A] == p[B]) q.push({A, B}), ans[A][B] = 1;
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    char s[N]; scanf("%s", s + 1);
    for(int i = 1; i <= n; i++) p[i] = s[i] - '0';
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        E.push_back({a, b});
    }
    memset(h, -1, sizeof h), idx = 0;
    for(Edge x : E) if(!p[x.a] && !p[x.b]) add(x.a, x.b);
    work();
    memset(h, -1, sizeof h), idx = 0;
    for(Edge x : E) if(p[x.a] && p[x.b]) add(x.a, x.b);
    work();
    memset(h, -1, sizeof h), idx = 0;
    for(Edge x : E) if(p[x.a] ^ p[x.b]) add(x.a, x.b);
    work();
    memset(h, -1, sizeof h), idx = 0;
    for(Edge x : E_es) add(x.a, x.b);
    bfs();
    while(q--) {
        int a, b; scanf("%d%d", &a, &b);
        if(a > b) swap(a, b);
        printf("%s\n", ans[a][b] ? "YES" : "NO");
    }
    return 0;
}