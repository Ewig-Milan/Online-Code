#include <bits/stdc++.h>
#define db double
using namespace std;

const int N = 21000, INF = 1e9;

int t, n, m;
db d;
int S, T;

struct Peng {db x, y;} P[N];
db dis(Peng a, Peng b) {return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));}

int h[N], e[N], ca[N], ne[N], idx;
void add(int a, int b, int c) {
    if(a == b) a = (a << 1) - 1, b <<= 1;
    else {
        if(a != S) a <<= 1;
        b = (b << 1) - 1;
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

int main_() {
    scanf("%d%lf", &n, &d);
    S = 0;
    for(int i = 1; i <= n; i++) {
        db x, y; int a, b; scanf("%lf%lf%d%d", &x, &y, &a, &b);
        add(i, i, b), add(S, i, a), P[i] = {x, y}, m += a;

        for(int j = 1; j < i; j++) if(dis(P[i], P[j]) - d <= 1e-9)
            add(i, j, INF), add(j, i, INF);
    }
    bool solvable = false;
    for(int i = 1; i <= n; i++) {
        T = (i << 1) - 1;
        for(int j = 0; j < idx; j += 2)  ca[j] += ca[j ^ 1], ca[j ^ 1] = 0;
        
        if(dinic() >= m) printf("%d ", i - 1), solvable = true;
    }
    if(!solvable) puts("-1");
    else putchar('\n');
    return 0;
}

void cl() {memset(h, -1, sizeof h), idx = m = 0;}
int main() {
    scanf("%d", &t);
    while(t--) cl(), main_();
    return 0;
}