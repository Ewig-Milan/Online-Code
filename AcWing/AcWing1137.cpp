#include <bits/stdc++.h>
using namespace std;

const int N = 1100, M = 20100;

int n, m, st, w, ans;
int dis[N], cnt;
bool flag[N];

int h[N], e[M], v[M], ne[M], idx;
void cl() {memset(h, -1, sizeof(h)); idx = 0;}
void add(int a, int b, int c) {e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;}

struct Node {
    int p, dis;
    friend bool operator < (const Node & a, const Node & b) {return a.dis > b.dis;}
};

void dji(int st) {
    memset(flag, 0, sizeof(flag));
    memset(dis, 127, sizeof(dis));
    cnt = 0, dis[st] = 0;
    priority_queue<Node> q;
    q.push({st, 0});
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
    while(~scanf("%d%d%d", &n, &m, &st)) {
        cl(), ans = 1e9;
        for(int i = 1; i <= m; i++) {
            int a, b, c; scanf("%d%d%d", &a, &b, &c);
            add(b, a, c);
        }
        dji(st);
        scanf("%d", &w);
        while(w--) {
            int a; scanf("%d", &a);
            ans = min(ans, dis[a]);
        }
        printf("%d\n", ans > 1e6 ? -1 : ans);
    }
    return 0;
}