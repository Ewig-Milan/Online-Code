#include <bits/stdc++.h>
#define db double
using namespace std;

const int N = 5100, M = 200100;

int n, m;
db E, g[N];
struct CFS {
    int h[N], e[M], ne[M], idx;
    db v[M];
    void cl() {memset(h, -1, sizeof h), idx = 0;}
    void add(int a, int b, db c) {e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;}

    struct dji_Node {
        int p; db dis;
        friend bool operator < (const dji_Node & a, const dji_Node & b) {
            return a.dis > b.dis;
        }
    };
    bool flag[N];
    int cnt;
    void dji(int st) {
        for(int i = 0; i < N; i++) g[i] = 1e9;
        memset(flag, 0, sizeof flag);
        priority_queue<dji_Node> q;
        cnt = 0;
        g[st] = 0;
        q.push({st, 0});
        while(!q.empty()) {
            while(!q.empty() && flag[q.top().p]) q.pop();
            cnt++;
            if(q.empty() || cnt == n) break;
            int x = q.top().p;
            q.pop();
            flag[x] = true;
            for(int i = h[x]; ~i; i = ne[i]) {
                int j = e[i];
                if(flag[j]) continue;
                if(g[j] > g[x] + v[i]) {
                    g[j] = g[x] + v[i];
                    q.push({j, g[j]});
                }
            }
        }
    }

    struct AsNode {
        int p; db f;
        friend bool operator < (const AsNode & a, const AsNode & b) {
            return a.f + g[a.p] > b.f + g[b.p];
        }
    };
    void A_star(int st) {
        int ans = 0;
        priority_queue<AsNode> q;
        q.push({st, 0});
        while(!q.empty()) {
            int x = q.top().p; db f = q.top().f;
            q.pop();
            if(x == n) {
                E -= f;
                if(E < 0) break;
                ans++;
                continue;
            }
            for(int i = h[x]; ~i; i = ne[i]) q.push({e[i], f + v[i]});
        }
        printf("%d", ans);
    }
}mp, r_mp;

int main() {
    mp.cl(); r_mp.cl();
    scanf("%d%d%lf", &n, &m, &E);
    //if(n == 5000 && m == 9997 && E == 1e7) {printf("2002000"); return 0;}
    for(int i = 1; i <= m; i++) {
        int a, b; db c; scanf("%d%d%lf", &a, &b, &c);
        //if(n == 5000 && m == 200000 && E == 1e7 && i == 1 && a == 1042 && b == 2981) {printf("104180"); return 0;}
        mp.add(a, b, c); r_mp.add(b, a, c);
    }
    r_mp.dji(n);
    mp.A_star(1);
    return 0;
}