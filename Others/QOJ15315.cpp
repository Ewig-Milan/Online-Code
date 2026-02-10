#include <bits/stdc++.h>
using namespace std;

const int N = 200100;

int n, m, S;
vector<pair<int, int>> E, add_E;
int dsu[N];
int find(int x) {return dsu[x] == x ? x : dsu[x] = find(dsu[x]);}
bool merge(int a, int b) {a = find(a), b = find(b); if(a != b) return dsu[a] = b; return 0;}

int h[N], e[N * 10], ne[N * 10], idx;
void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++;}

int nd[N];
int fa[N], dep[N];

void pre(int x, int l) {
    fa[x] = l, dep[x] = dep[l] ^ 1;
    for(int i = h[x]; ~i; i = ne[i]) if(e[i] != l) pre(e[i], x);
}

bool oddring() {
    dep[0] = 0, pre(S, 0);
    for(auto x : E) {
        int a = x.first, b = x.second;
        if(dep[a] != dep[b] || find(a) != find(S)) continue;
        add_E.push_back({a, b});
        while(a != S) nd[a] ^= 1, add_E.push_back({fa[a], a}), a = fa[a];
        while(b != S) nd[b] ^= 1, add_E.push_back({b, fa[b]}), b = fa[b];
        nd[S] ^= 1;
        return 1;
    }
    return 0;
}

void work(int x, int l) {
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        work(j, x);
        if(nd[j]) nd[j] ^= 1, nd[x] ^= 1, add_E.push_back({x, j}), add_E.push_back({j, x});
    }
}

vector<int> ans;
void get_ans(int x) {
    for(int i = h[x]; ~i; i = h[x]) h[x] = ne[i], get_ans(e[i]);
    ans.push_back(x);
}

void solve() {
    for(int i = 1; i <= n; i++) scanf("%d", &nd[i]), nd[i] &= 1;
    vector<pair<int, int>> EE;
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        if(merge(a, b)) add(a, b), add(b, a), EE.push_back({a, b});
        else E.push_back({a, b});
    }
    for(auto x : EE) if(find(x.first) == find(S)) nd[x.first] ^= 1, nd[x.second] ^= 1;
    bool cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(find(i) != find(S) && nd[i]) {puts("No"); return;}
        if(find(i) == find(S) && nd[i]) cnt ^= 1;
    }
    if(cnt) if(!oddring()) {puts("No"); return;}
    work(S, 0);
    for(auto x : add_E) add(x.first, x.second);
    get_ans(S);
    int tmp = ans.size() - 1;
    printf("Yes\n%d\n", tmp);
    for(int i = 1; i <= tmp; i++) printf("%d ", ans[i]);
    puts("");
}

void cl() {
    for(int i = 1; i <= n; i++) h[i] = -1, dsu[i] = i;
    E.clear(), add_E.clear(), ans.clear(), idx = 0;
}

int main() {
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &m, &S);
        cl(), solve();
    }
    return 0;
}