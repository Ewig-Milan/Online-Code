#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;

const int N = 500100, M = 2000100;

int n, m;
ull ans[N];

int dfn[N], low[N], cnt;
int siz[N];

vector<int> pcut;

int h[N], e[M << 1], ne[M << 1], idx;
void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++;}

stack<int> S;
void tarjan(int x, int l) {
    S.push(x);
    dfn[x] = low[x] = ++cnt;
    int rem = n - 1;
    ans[x] = n - 1, siz[x] = 1;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if((i ^ 1) == l) continue;
        if(!dfn[j]) {
			tarjan(j, i);
			siz[x] += siz[j];
            low[x] = min(low[x], low[j]);
	        if(dfn[x] <= low[j]) {
	        	rem -= siz[j];
	        	ans[x] += (ull)siz[j] * (n - siz[j]);
	            while(S.top() != j) S.pop();
                S.pop();
	        }
		} else low[x] = min(low[x], dfn[j]);
    }
    ans[x] += (ull)rem * (n - rem);
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        add(a, b); add(b, a);
    }
    for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i, -1);
    for(int i = 1; i <= n; i++) printf("%llu\n", ans[i]); 
    return 0;
}