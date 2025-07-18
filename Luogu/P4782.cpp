#include <bits/stdc++.h>
using namespace std;

const int N = 2000100;

int n, m;

int topo[N], topo_cnt;

vector<int> bl[N];
int bl_cnt, bl_id[N];
int dfn[N], low[N], cnt;

bool flag[N];
stack<int> S;

struct CFS {
    int h[N], e[N], ne[N], idx, rd[N];
    void cl() {memset(h, -1, sizeof h), idx = 0;}

    void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++, rd[b]++;}

    void bfs() {
        queue<int> q;
        for(int i = 1; i <= (n << 1); i++) if(!rd[i]){
            q.push(i);
            ++topo_cnt;
            for(int x : bl[i]) topo[x] = topo_cnt;
        }
        while(!q.empty()) {
            int x = q.front();
            q.pop();
            for(int i = h[x]; ~i; i = ne[i]) {
                int j = e[i];
                if(!--rd[j]) {
                    q.push(j);
                    ++topo_cnt;
                    for(int y : bl[j]) topo[y] = topo_cnt;
                }
            }
        }
    }
}mp, bl_mp;

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
        while(S.top() != x) {
            bl_id[S.top()] = bl_cnt;
            bl[bl_cnt].push_back(S.top());
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

bool check() {
    for(int i = 1; i <= n; i++) if(bl_id[i] == bl_id[i + n]) return false;
    return true;
}

// 真点原下标 假点下标 + n
int main() {
    mp.cl(), bl_mp.cl();
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);
        mp.add(a + n * b, c + n * (!d));
        mp.add(c + n * d, a + n * (!b));
    }
    for(int i = 1; i <= (n << 1); i++) if(!dfn[i]) tarjan(i);
    if(!check()) {
        puts("IMPOSSIBLE");
        return 0;
    } else puts("POSSIBLE");
    bl_mp.bfs();
    for(int i = 1; i <= n; i++) if(topo[i] > topo[i + n]) printf("1 ");
    else printf("0 ");
    return 0;
}