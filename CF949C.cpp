#include <bits/stdc++.h>
using namespace std;

const int N = 100100;

int n, m, h, w[N];

vector<int> bl[N];
int bl_id[N], bl_cd[N], bl_cnt;
int dfn[N], low[N], cnt;
int mi_id;

struct CFS {
    int h[N], e[N << 1], ne[N << 1], idx;
    void cl() {memset(h, -1, sizeof h); idx = 0;}
    void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++;}

    stack<int> S;
    bool flag[N];
    void tarjan(int x) {
        S.push(x);
        flag[x] = true;
        dfn[x] = low[x] = ++cnt;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(!dfn[j]) {
                tarjan(j);
                low[x] = min(low[x], low[j]);
            } else if(flag[j]) low[x] = min(low[x], low[j]);
        }
        if(dfn[x] == low[x]) {
            bl_id[x] = ++bl_cnt, flag[x] = false;
            bl[bl_cnt].push_back(x);
            while(S.top() != x) {
                int t = S.top();
                S.pop();
                flag[t] = false;
                bl_id[t] = bl_cnt;
                bl[bl_cnt].push_back(t);
            }
            S.pop();

            for(int p : bl[bl_cnt])     
                for(int i = h[p]; ~i; i = ne[i]) {
                    int j = e[i];
                    if(bl_id[j] == bl_cnt) continue;
                    bl_cd[bl_cnt]++;
                }
        }
    }
}mp;

int main() {
    mp.cl();
    scanf("%d%d%d", &n, &m, &h);
    for(int i = 1; i <= n; i++) scanf("%d", &w[i]);
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        if((w[a] + 1) % h == w[b]) mp.add(a, b);
        swap(a, b);
        if((w[a] + 1) % h == w[b]) mp.add(a, b);
    }
    for(int i = 1; i <= n; i++) if(!dfn[i]) mp.tarjan(i);
    for(int i = 1; i <= bl_cnt; i++) if(!bl_cd[i])
        if(!mi_id || bl[i].size() < bl[mi_id].size()) mi_id = i;
    sort(bl[mi_id].begin(), bl[mi_id].end());
    printf("%d\n", bl[mi_id].size());
    for(int i : bl[mi_id]) printf("%d ", i);
    return 0;
}