#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 100100, M = 600100;

int n, m, X;
int H[N];

int h[N], e[M], v[M], ne[M], idx;
void add(int a, int b, int c) {
    e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

struct Node {
    int id, dis;
    friend bool operator < (const Node &a, const Node &b) {return a.dis > b.dis;}
};
int dis[N];
bool vis[N];
void dij(int s) {
    memset(dis, 63, sizeof dis);
    memset(vis, 0, sizeof vis);
    priority_queue<Node> q;
    dis[s] = 0, q.push({s, 0});
    while(!q.empty()) {
        int x = q.top().id;
        q.pop();
        if(vis[x]) continue;
        vis[x] = 1;
        if(dis[x] < X - H[x]) dis[x] = X - H[x];
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(dis[j] > dis[x] + v[i]) {
                dis[j] = dis[x] + v[i];
                q.push({j, dis[j]});
            }
        }
    }
}

signed main() {
    memset(h, -1, sizeof h);
    scanf("%lld%lld%lld", &n, &m, &X);
    for(int i = 1; i <= n; i++) scanf("%lld", &H[i]);
    for(int i = 1; i <= m; i++) {
        int a, b, c; scanf("%lld%lld%lld", &a, &b, &c);
        if(H[a] >= c) add(a, b, c);
        if(H[b] >= c) add(b, a, c);
    }
    dij(1);
    int ans = dis[n] + abs(H[n] + dis[n] - X);
    printf("%lld", (ans > 1e18) ? -1 : ans);
    return 0;
}