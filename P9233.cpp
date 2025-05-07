#include <bits/stdc++.h>
using namespace std;

const int N = 200100;

int n, c[N], ans;

int h[N], e[N], ne[N], idx;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int siz[N], ma_s[N], L[N], R[N], id[N], cnt;
int cnt_ma/*存次数*/, cnt_col[N]/*下标颜色*/, cnt_num[N]/*下标次数*/;
void dfs_pre(int x, int l) {
    L[x] = ++cnt, id[cnt] = x, siz[x] = 1;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        dfs_pre(j, x);
        siz[x] += siz[j];
        if(siz[j] > siz[ma_s[x]]) ma_s[x] = j;
    }
    R[x] = cnt;
}

void add_col(int col) {
    if(cnt_col[col] == cnt_ma) cnt_ma++;
    cnt_num[cnt_col[col]]--;
    cnt_col[col]++;
    cnt_num[cnt_col[col]]++;
}

void del_col(int col) {
    if(cnt_col[col] == cnt_ma && cnt_num[cnt_ma] == 1) cnt_ma--;
    cnt_num[cnt_col[col]]--;
    cnt_col[col]--;
    cnt_num[cnt_col[col]]++;
}

void dfs(int x, int l, bool keep) {
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l || j == ma_s[x]) continue;
        dfs(j, x, 0);
    }
    if(ma_s[x]) dfs(ma_s[x], x, 1);
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l || j == ma_s[x]) continue;
        for(int k = L[j]; k <= R[j]; k++) add_col(c[id[k]]);
    }
    add_col(c[x]);
    ans += (cnt_ma != 0) & (cnt_num[cnt_ma] == siz[x] / cnt_ma) & (siz[x] % cnt_ma == 0);
    if(!keep) for(int i = L[x]; i <= R[x]; i++) del_col(c[id[i]]);
}

int main() {
    memset(h, -1, sizeof(h));
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        int a; scanf("%d%d", &c[i], &a);
        if(a) add(a, i);
    }
    dfs_pre(1, 0);
    dfs(1, 0, 1);
    printf("%d", ans);
    return 0;
}