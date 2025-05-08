//
// https://www.luogu.com.cn/article/4052agln
//
#include <bits/stdc++.h>
using namespace std;

const int N = 500100, M = 2000100;

int n, m;

vector<int> ebl[N];
int ebl_cnt;
int dfn[N], low[N], cnt;

vector<int> ecut; // 或者写成bool变成表    都行
// 这里ecut存的是桥边的idx(边号) 正反均存

int h[N], e[M << 1], ne[M << 1], idx;
void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++;}

stack<int> S;
void tarjan(int x, int l) {
    S.push(x);
    dfn[x] = low[x] = ++cnt;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if((i ^ 1) == l) continue;
        if(!dfn[j]) tarjan(j, i), low[x] = min(low[x], low[j]);
        else low[x] = min(low[x], dfn[j]); // 注意 双连通要改过来了！
    }
    if(dfn[x] == low[x]) {
        ebl_cnt++;
        if(l >= 0) ecut.push_back(l), ecut.push_back(l ^ 1);
        ebl[ebl_cnt].push_back(x);
        while(S.top() != x) {
            ebl[ebl_cnt].push_back(S.top());
            S.pop();
        }
        S.pop();
    }
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        add(a, b); add(b, a);
    }
    for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i, -1);
    printf("%d\n", ebl_cnt);
    for(int i = 1; i <= ebl_cnt; i++) {
        printf("%d ", ebl[i].size());
        for(int j : ebl[i]) printf("%d ", j);
        putchar('\n');
    }
    //for(int i : ecut) printf("%d ", i); // 题目不要求输出
    return 0;
}