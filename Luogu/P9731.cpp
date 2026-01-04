#include <bits/stdc++.h>
#define PII pair<int, int>
#define fi first
#define se second
using namespace std;

const int N = 100100, M = 1000100;

int n, s, t;
vector<int> C[N];

bool vis[M];
int h[N], d[N], e[M], ne[M], id[M], idx;
void add(int a, int b, int c) {
    vis[idx] = vis[idx + 1] = 0;
    id[idx] = c, e[idx] = b, ne[idx] = h[a], h[a] = idx++, d[a]++;
    id[idx] = c, e[idx] = a, ne[idx] = h[b], h[b] = idx++, d[b]++;
}

vector<PII> C_;
unordered_set<int> P;
void dfs(int x) {
    d[x] = 0;
    for(int i = h[x]; ~i; i = h[x]) {
        h[x] = ne[i];
        if(vis[i] || vis[i ^ 1]) continue;
        vis[i] = 1;
        if(id[i] != -1) C_[id[i]] = {x, e[i]};
        dfs(e[i]);
    }
}
void work() {
    P.clear();
    for(int i = 0; i < (int)C_.size(); i++) {
        PII x = C_[i];
        add(x.fi, x.se, i), P.insert(x.fi), P.insert(x.se);
    }
    for(int x : P) if(d[x] & 1) add(0, x, -1);
    for(int x : P) if(d[x]) dfs(x);
    for(int x : P) h[x] = -1;
    h[0] = -1, idx = 0;
}
void divc(int l, int r) {
    if(l == r) return;
    int mid = l + r >> 1;
    for(int i = 1; i <= n; i++) for(int j = l; j <= mid; j++)
        C_.push_back({C[i][j], C[i][j + mid - l + 1]});
    work();
    for(int i = n; i; i--) for(int j = mid; j >= l; j--) {
        C[i][j] = C_.back().fi, C[i][j + mid - l + 1] = C_.back().se;
        C_.pop_back();
    }
    divc(l, mid), divc(mid + 1, r);
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d%d", &n, &s, &t);
    for(int i = 1; i <= n; i++)
    for(int j = 1; j <= s; j++) {
        int a; scanf("%d", &a);
        C[i].push_back(a);
    }
    divc(0, s - 1);
    for(int i = 1; i <= n; i++) {
        for(int x : C[i]) printf("%d ", x);
        puts("");
    }
    return 0;
}