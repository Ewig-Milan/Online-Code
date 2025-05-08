#include <bits/stdc++.h>
#define f(x1, x2, x3, x4, x5, x6) p_d[x1][x2]+p_d[x2][x3]+p_d[x3][x4]+p_d[x4][x5]+p_d[x5][x6]
using namespace std;

const int N = 50100, M = 100100;

int n, m, pa[6], ans = 1e9;
int dis[N], p_d[6][6];

int h[N], e[M << 1], ne[M << 1], v[M << 1], idx;
void add(int a, int b, int c) {
    e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

struct Node {
    int p, dis;
    friend bool operator < (const Node & a, const Node & b) {return a.dis > b.dis;}
};
int cnt;
bool flag[N];
void dji(int st) {
    memset(dis, 127, sizeof dis);
    memset(flag, 0, sizeof flag);
    cnt = 0;
    priority_queue<Node> q;
    q.push({st, 0});
    dis[st] = 0;
    while(!q.empty()) {
        while(!q.empty() && flag[q.top().p]) q.pop();
        cnt++;
        if(cnt == n || q.empty()) break;
        int x = q.top().p;
        flag[x] = true;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(flag[j]) continue;
            if(dis[j] > dis[x] + v[i]) {
                dis[j] = dis[x] + v[i];
                q.push({j, dis[j]});
            }
        }
    }
}
int main() {
    pa[0] = 1;
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= 5; i++) scanf("%d", &pa[i]);
    for(int i = 1; i <= m; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        add(a, b, c); add(b, a, c);
    }
    for(int i = 0; i <= 5; i++) {
        dji(pa[i]);
        for(int j = 0; j <= 5; j++) if(j != i) p_d[i][j] = dis[pa[j]];
    }
    for(int i1 = 1; i1 <= 5; i1++)
    for(int i2 = 1; i2 <= 5; i2++) {
    if(i2==i1)continue;
    for(int i3 = 1; i3 <= 5; i3++) {
    if(i3==i2||i3==i1)continue;
    for(int i4 = 1; i4 <= 5; i4++) {
    if(i4==i3||i4==i2||i4==i1)continue;
    for(int i5 = 1; i5 <= 5; i5++) {
        if(i5==i4||i5==i3||i5==i2||i5==i1)continue;
        ans=min(ans,f(0,i1,i2,i3,i4,i5));
    }}}}
    printf("%d", ans);
    return 0;
}