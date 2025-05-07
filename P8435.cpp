//
// https://www.luogu.com.cn/article/4052agln
//
#include <bits/stdc++.h>
using namespace std;

const int N = 500100, M = 2000100;

int n, m;

vector<int> pbl[N];
int pbl_cnt;
int dfn[N], low[N], cnt;

vector<int> pcut;

int h[N], e[M << 1], ne[M << 1], idx;
void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++;}

stack<int> S;
void tarjan(int x, int l) {
    S.push(x);
    dfn[x] = low[x] = ++cnt;
    int son = 0;
    bool cut = false;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(i == l) continue;
        if(!dfn[j]) {
			son++;
			tarjan(j, i);
            low[x] = min(low[x], low[j]);
	        if(dfn[x] <= low[j]) {
	            pbl_cnt++, cut = true;
	            pbl[pbl_cnt].push_back(x);
	            pbl[pbl_cnt].push_back(j);
	            while(S.top() != j) {
	                pbl[pbl_cnt].push_back(S.top());
	                S.pop();
	            }
                S.pop();
	        }
		} else low[x] = min(low[x], dfn[j]);
    }
    if(l == -1 && !son) pbl[++pbl_cnt].push_back(x);//特判孤立点
    if(cut && (l >= 0 || son > 1)) pcut.push_back(x);
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        add(a, b); add(b, a);
    }
    for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i, -1);
    printf("%d\n", pbl_cnt);
    for(int i = 1; i <= pbl_cnt; i++) {
        printf("%d ", pbl[i].size());
        for(int j : pbl[i]) printf("%d ", j);
        putchar('\n');
    }
    //for(int i : pcut) printf("%d ", i); // 题目不要求输出
    return 0;
}