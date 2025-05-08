#include <bits/stdc++.h>
using namespace std;
const int N = 50100, M = 100100;

int n, m, w, need;
struct Edge {int a, b, c, col, tc;};
bool cmp(const Edge & a, const Edge & b) {
    return a.tc == b.tc ? a.col < b.col : a.tc < b.tc;
}
vector<Edge> E;

int fa[N];
int find(int x) {
    if(x != fa[x]) fa[x] = find(fa[x]);
    return fa[x];
}
bool merge(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) return false;
    fa[b] = a;
    return true;
}
int krus() {
    int cnt = 0, ans = 0;
    for(int i = 0; i < N; i++) fa[i] = i;
    sort(E.begin(), E.end(), cmp);
    for(int i = 0; cnt < n - 1; i++) {
        if(merge(E[i].a, E[i].b)) {
            cnt++, w += (E[i].col ^ 1);
            ans += E[i].tc;
        }
    }
    return ans;
}

bool check() {
    w = 0, krus();
    return w >= need;
}

int main() {
    scanf("%d%d%d", &n, &m, &need);
    for(int i = 1; i <= m; i++) {
        int a, b, c, col; scanf("%d%d%d%d", &a, &b, &c, &col);
        E.push_back({a, b, c, col, 0});
    }
    int l = -100, r = 100;
    while(l < r) {
        int mid = l + r + 1 >> 1;
        for(auto & i : E) i.tc = i.c + (i.col ^ 1) * mid;
        if(check()) l = mid;
        else r = mid - 1;
    }
    for(auto & i : E) i.tc = i.c + (i.col ^ 1) * l;
    printf("%d", krus() - need * l);
    return 0;
}