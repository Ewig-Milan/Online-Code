#include <bits/stdc++.h>
using namespace std;

const int N = 1600;

struct Node {
    int p, dis;
    friend bool operator < (const Node & a, const Node & b) {
        return a.dis > b.dis;
    }
};

int n, p, c, ans = 1e9;
int cow[N], dis[N], cnt;
bool flag[N];

int h[N], e[N << 1], v[N << 1], ne[N << 1], idx;

void add(int a, int b, int c) {e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;}

void dji(int st) {
    cnt = 0;
    memset(flag, 0, sizeof(flag));
    memset(dis, 127, sizeof(dis));
    priority_queue<Node> q;
    dis[st] = 0;
    q.push({st, 0});
    while(!q.empty()) {
        while(!q.empty() && flag[q.top().p]) q.pop();
        cnt++;
        if(q.empty() || cnt == p) break;
        int x = q.top().p;
        flag[x] = true;
        q.pop();
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
    memset(h, -1, sizeof(h));
    scanf("%d%d%d", &n, &p, &c);
    for(int i = 1; i <= n; i++) {
        int a; scanf("%d", &a);
        cow[a]++;
    }
    for(int i = 1; i <= c; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        add(a, b, c); add(b, a, c);
    }
    for(int i = 1; i <= p; i++) {
        int res = 0;
        dji(i);
        for(int j = 1; j <= p; j++) res += dis[j] * cow[j];
        ans = min(ans, res);
    }
    printf("%d", ans);
    return 0;
}