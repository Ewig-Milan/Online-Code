#include <bits/stdc++.h>
#define PII pair<int, int>
#define y first
#define n second
using namespace std;

const int N = 6100;

int n;
int r[N], rd[N]; // 0-no 1-yes
PII f[N];
vector<int> son[N];

PII DP(int x) {
    if(f[x].y && f[x].n) return f[x];
    f[x].y += r[x];
    for(int i : son[x]) {
        DP(i);
        f[x].y += f[i].n;
        f[x].n += max(f[i].y, f[i].n);
    }
    return f[x];
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &r[i]);
    for(int i = 1; i < n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        son[b].push_back(a), rd[a]++;
    }
    int rt;
    for(int i = 1; i <= n; i++) if(!rd[i]) rt = i;
    PII ans = DP(rt);
    printf("%d", max(ans.y, ans.n));
    return 0;
}