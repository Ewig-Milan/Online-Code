#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 10100, M = 1000100;

int n, m, k, Nn;
ll ans, tmp;

int h[N], e[N << 1], ne[N << 1], v[N << 1], idx;
void add(int a, int b, int c) {
    e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, v[idx] = c, ne[idx] = h[b], h[b] = idx++;
}

struct edge {
    int a, b, v;
    friend bool operator < (const edge &a, const edge &b) {return a.v < b.v;}
};
vector<edge> ori;

int cns[13][N];
vector<int> cc;

int fa[N];
void cl() {for(int i = 1; i <= n + 10; i++) fa[i] = i;}
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
bool merge(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) return false;
    fa[a] = b;
    return true;
}

struct EDGE {
    int to, v;
    friend bool operator < (const EDGE &a, const EDGE &b) {return a.v > b.v;}
};
priority_queue<EDGE> q;
int best[N];
bool vis[N];
ll prim() {
    memset(vis, 0, sizeof vis);
    memset(best, 127, sizeof best);
    while(!q.empty()) q.pop();
    int cnt = 1;
    vis[1] = 1;
    for(int i = h[1]; ~i; i = ne[i]) q.push({e[i], v[i]});
    for(int x : cc) q.push({n + x, cns[x][1]});
    while(cnt < Nn) {
        EDGE x = q.top();
        q.pop();
        if(vis[x.to]) continue;
        vis[x.to] = 1, tmp += x.v, cnt++;
        if(tmp >= ans) break;
        if(x.to <= n) {
            for(int i = h[x.to]; ~i; i = ne[i]) if(!vis[e[i]] && best[e[i]] > v[i]) q.push({e[i], v[i]}), best[e[i]] = v[i];
            for(int i : cc) if(!vis[i + n] && best[i + n] > cns[i][x.to]) q.push({i + n, cns[i][x.to]}), best[i + n] = cns[i][x.to];
        } else for(int i = 1; i <= n; i++) if(!vis[i] && best[i] > cns[x.to - n][i]) q.push({i, cns[x.to - n][i]}), best[i] = cns[x.to - n][i];
    }
    return tmp;
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= m; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        ori.push_back({a, b, c});
    }
    for(int i = 1; i <= k; i++) for(int j = 0; j <= n; j++) scanf("%d", &cns[i][j]);

    cl();
    int cnt = 0;
    sort(ori.begin(), ori.end());
    for(edge &x : ori) if(merge(x.a, x.b)) {
        ans += x.v, add(x.a, x.b, x.v), cnt++;
        if(cnt == n - 1) break;
    }

    for(int stat = 1; stat < (1 << k); stat++) {
        cc.resize(0); Nn = n, tmp = 0;
        for(int i = 1; i <= k; i++) if(stat & (1 << (i - 1))) cc.push_back(i), Nn++, tmp += cns[i][0];
        ans = min(ans, prim());
    }
    printf("%lld", ans);
    return 0;
}