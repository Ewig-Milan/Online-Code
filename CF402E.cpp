#include <bits/stdc++.h>
using namespace std;

const int N = 2100;

int n;

int bl_cnt;
int dfn[N], low[N], cnt;
struct CFS {
    int h[N], e[N * N], ne[N * N], idx;
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
            bl_cnt++;
            flag[x] = false;
            while(S.top() != x) {
                flag[S.top()] = false;
                S.pop();
            }
            S.pop();
        }
    }
}mp;

int main() {
    mp.cl();
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++) {
            int a; scanf("%d", &a);
            if(a && i != j) mp.add(i, j);
        }
    for(int i = 1; i <= n; i++) if(!dfn[i]) mp.tarjan(i);
    printf("%s", bl_cnt == 1 ? "YES" : "NO");
    return 0;
} 