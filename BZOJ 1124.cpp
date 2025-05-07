//
// 贱死了
//
#include <bits/stdc++.h>
using namespace std;

const int N = 1000100;

int n;

struct CFS {
    int h[N], e[N << 1], ne[N << 1], idx;
    void cl() {idx = 0; memset(h, -1, sizeof h);}
    void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++;}
}mp, r_mp;

int rd[N];
bool vis[N], die[N];

int find_cir(int x) {
    int res = 1;
    for(int i = mp.h[x], j = mp.e[i]; j != x; i = mp.h[j], j = mp.e[i]) res++, vis[j] = true;
    return res;
}
int find_mi() {
    memset(vis, 0, sizeof vis);
    int liv = 0;
    queue<int> q;
    for(int i = 1; i <= n; i++) if(!rd[i]) q.push(i);
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        liv++;
        if(die[mp.e[mp.h[x]]]) continue;
        die[mp.e[mp.h[x]]] = true;
        if(!--rd[mp.e[mp.h[mp.e[mp.h[x]]]]]) q.push(mp.e[mp.h[mp.e[mp.h[x]]]]); // 抽象 
    }
    for(int i = 1; i <= n; i++) if(rd[i] && !die[i] && !vis[i]) liv += find_cir(i) >> 1;
    return n - liv;
}

int dfs(int x) {
    if(vis[x]) return 0;
    vis[x] = true;
    int res = !rd[x];
    for(int i = r_mp.h[x]; ~i; i = r_mp.ne[i]) res += dfs(r_mp.e[i]);
    return res;
}
int find_ma() {
    memset(vis, 0, sizeof vis);
    int liv = 0;
    for(int i = 1; i <= n; i++) if(!vis[i] && !die[i]) liv += max(1, dfs(i));
    return n - liv;
}

int main() {
    mp.cl(); r_mp.cl();
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        int a; scanf("%d", &a);
        if(a == i) {die[i] = true; rd[a]++; continue;}
        mp.add(i, a); r_mp.add(a, i); r_mp.add(i, a); rd[a]++;
    }
    printf("%d %d", find_mi(), find_ma()/*会先跑*/);
    return 0;
}