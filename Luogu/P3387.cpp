#include <bits/stdc++.h>
using namespace std;

const int N = 10100, M = 100100;

int n, m;

struct CFS {
    int h[N], e[M], ne[M], idx, w[N];
    int rd[N], dis[N];
    void cl() {memset(h, -1, sizeof h), idx = 0;}

    void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++, rd[b]++;}

    int bfs() {
        int res = 0;
        queue<int> q;
        for(int i = 1; i <= n; i++) if(!rd[i]) q.push(i), dis[i] = w[i];
        while(!q.empty()) {
            int x = q.front();
            q.pop();
            for(int i = h[x]; ~i; i = ne[i]) {
                int j = e[i];
                dis[j] = max(dis[j], dis[x] + w[j]);
                if(!--rd[j]) q.push(j);
            }
        }
        for(int i = 1; i <= n; i++) res = max(res, dis[i]);
        return res;
    }
}mp, bl_mp;

int bl_cnt, bl_id[N];
vector<int> bl[N];

int dfn[N], low[N], cnt;
bool flag[N];
stack<int> S;

void tarjan(int x) {
    S.push(x), flag[x] = 1;
    dfn[x] = low[x] = ++cnt;
    for(int i = mp.h[x]; ~i; i = mp.ne[i]) {
        int j = mp.e[i];
        if(!dfn[j]) tarjan(j), low[x] = min(low[x], low[j]);
        else if(flag[j]) low[x] = min(low[x], dfn[j]);
    }
    if(dfn[x] == low[x]) {
        bl_id[x] = ++bl_cnt;
        bl[bl_cnt].push_back(x);
        bl_mp.w[bl_cnt] = mp.w[x];
        while(S.top() != x) {
            bl_id[S.top()] = bl_cnt;
            bl[bl_cnt].push_back(S.top());
            bl_mp.w[bl_cnt] += mp.w[S.top()];
            flag[S.top()] = 0, S.pop();
        }
        S.pop(), flag[x] = 0;
        for(int x : bl[bl_cnt])
        for(int i = mp.h[x]; ~i; i = mp.ne[i]) {
            int j = mp.e[i];
            if(bl_id[j] != bl_cnt) bl_mp.add(bl_cnt, bl_id[j]);
        }
    }
}

int main() {
    mp.cl(), bl_mp.cl();
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &mp.w[i]);
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        mp.add(a, b);
    }
    for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i);
    printf("%d", bl_mp.bfs());
    return 0;
}