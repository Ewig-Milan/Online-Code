#include <bits/stdc++.h>
#define db double
#define fi first
#define se second
using namespace std;

const int N = 100100, M = 5000100;
const db INF = 1e16, eps = 1e-8;

int n, s = 0, t = N - 1, cnt;
db sum;
pair<int, int> p[N];
db C[N];
map<pair<int, int>, int> mp;

int h[N], e[M], ne[M], idx;
db ca[M];
void add(int a, int b, db c) {
    e[idx] = b, ca[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ca[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

void link(int a, int b, int c) {
    if(((p[b].fi + p[b].se) % 3 + 3) % 3 == 1) swap(a, b);
    if(((p[c].fi + p[c].se) % 3 + 3) % 3 == 1) swap(a, c);
    if(((p[b].fi + p[b].se) % 3 + 3) % 3 == 2) swap(c, b);
    add(a + cnt, b, INF), add(b + cnt, c, INF);
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
            if(dep[j] == -1 && ca[i] > eps) dep[j] = dep[x] + 1, q.push(j);
        }
    }
    return 0;
}

db dfs(int x, db lim) {
    if(x == t) return lim;
    db flow = 0;
    for(int &i = can[x]; ~i && flow < lim; i = ne[i]) {
        int j = e[i];
        if(dep[j] == dep[x] + 1 && ca[i] > eps) {
            db tmp = dfs(j, min(ca[i], lim - flow));
            if(tmp <= eps) dep[j] = -1;
            else flow += tmp, ca[i] -= tmp, ca[i ^ 1] += tmp;
        }
    }
    return flow;
}

db dinic() {
    db tmp, mf = 0;
    while(bfs()) while((tmp = dfs(s, INF)) > eps) mf += tmp;
    return mf;
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        int x, y, z; db c; scanf("%d%d%d%lf", &x, &y, &z, &c);
        x -= z, y -= z;
        if(((x + y) % 3 + 3) % 3 == 0) c *= 1.1;
        if(mp[{x, y}]) C[mp[{x, y}]] += c;
        else cnt++, mp[{x, y}] = cnt, C[cnt] = c, p[cnt] = {x, y};
    }
    for(int i = 1; i <= cnt; i++) {
        int x = p[i].fi, y = p[i].se;
        db c = C[i];
        add(i, i + cnt, c);
        if(((x + y) % 3 + 3) % 3 == 1) add(s, i, INF);
        if(((x + y) % 3 + 3) % 3 == 2) add(i + cnt, t, INF);
        sum += c;
    }
    for(int i = 1; i <= cnt; i++) {
        auto x = p[i];
        if(mp[{x.fi + 1, x.se}] && mp[{x.fi + 1, x.se + 1}]) link(i, mp[{x.fi + 1, x.se}], mp[{x.fi + 1, x.se + 1}]);
        if(mp[{x.fi, x.se + 1}] && mp[{x.fi + 1, x.se + 1}]) link(i, mp[{x.fi, x.se + 1}], mp[{x.fi + 1, x.se + 1}]);
        if(((x.fi + x.se) % 3 + 3) % 3 == 0) {
            if(mp[{x.fi - 1, x.se - 1}] && mp[{x.fi + 1, x.se + 1}]) link(i, mp[{x.fi - 1, x.se - 1}], mp[{x.fi + 1, x.se + 1}]);
            if(mp[{x.fi, x.se - 1}] && mp[{x.fi, x.se + 1}]) link(i, mp[{x.fi, x.se - 1}], mp[{x.fi, x.se + 1}]);
            if(mp[{x.fi - 1, x.se}] && mp[{x.fi + 1, x.se}]) link(i, mp[{x.fi - 1, x.se}], mp[{x.fi + 1, x.se}]);
        }
    }
    printf("%.1lf\n", sum - dinic());
    return 0;
}