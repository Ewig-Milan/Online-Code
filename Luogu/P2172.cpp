#include <bits/stdc++.h>
using namespace std;

const int N = 5100, M = 35100, INF = 1e9;

int n, m, c, r, S, T;
int id[N][N], inc;
int cost;

int h[N], e[M], v[M], ca[M], ne[M], idx;
void add(int a, int b, int c, int d) {
    if(a == b) a = (a << 1) - 1, b <<= 1;
    else {
        if(a != S) a <<= 1;
        if(b == T) a -= 1;
        else b = (b << 1) - 1;
    }
    e[idx] = b, ca[idx] = c, v[idx] = d, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ca[idx] = 0, v[idx] = -d, ne[idx] = h[b], h[b] = idx++;
}

int pe[N];
bool vis[N];
void SPFA() {
    memset(pe, 63, sizeof pe);
    memset(vis, 0, sizeof vis);
    queue<int> q;
    pe[S] = 0, q.push(S), vis[S] = 1;
    while(!q.empty()) {
        int x = q.front();
        q.pop(), vis[x] = 0;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(ca[i] && pe[j] > pe[x] + v[i]) {
                pe[j] = pe[x] + v[i];
                if(!vis[j]) q.push(j), vis[j] = 1;
            }
        }
    }
}

struct Node {
    int dis, id;
    friend bool operator < (const Node & a, const Node & b) {return a.dis > b.dis;}
};
int dis[N], can[N];
bool dij() {
    for(int i = 0; i < N; i++) dis[i] = INF, vis[i] = 0, can[i] = h[i];
    priority_queue<Node> q;
    dis[S] = 0, q.push({0, S});
    while(!q.empty()) {
        int x = q.top().id;
        q.pop();
        if(vis[x]) continue;
        vis[x] = 1;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(ca[i] && dis[j] > dis[x] + v[i] + pe[x] - pe[j]) {
                dis[j] = dis[x] + v[i] + pe[x] - pe[j];
                q.push({dis[j], j});
            }
        }
    }
    memset(vis, 0, sizeof vis);
    for(int i = 0; i < N; i++) pe[i] += dis[i];
    return dis[T] < INF;
}

int dfs(int x, int lim) {
    if(x == T) return lim;
    vis[x] = 1;
    int flow = 0;
    for(int &i = can[x]; ~i && flow < lim; i = ne[i]) {
        int j = e[i];
        if(v[i] + pe[x] - pe[j] == 0 && !vis[j] && ca[i]) {
            int tmp = dfs(j, min(ca[i], lim - flow));
            if(!tmp) vis[j] = 1; // 此处写法正确性已验证
            else flow += tmp, ca[i] -= tmp, ca[i ^ 1] += tmp, cost += tmp * v[i];
        }
    }
    vis[x] = 0;
    return flow;
}

int PD() {
    cost = 0, SPFA();
    int mf = 0, tmp;
    while(dij()) while(tmp = dfs(S, INF)) mf += tmp;
    return cost;
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
                add(id[i - r][j - c], inc, 1, -1);
            if(i - r > 0 && j + c > 0 && id[i - r][j + c])
                add(id[i - r][j + c], inc, 1, -1);
            if(i - c > 0 && j - r > 0 && id[i - c][j - r])
                add(id[i - c][j - r], inc, 1, -1);
            if(i - c > 0 && j + r > 0 && id[i - c][j + r])
                add(id[i - c][j + r], inc, 1, -1);
            add(S, inc, INF, 0), add(inc, T, 1, 0);
            add(inc, inc, 1, 0);
        }
    }
    printf("%d", inc + PD());
    return 0;
}