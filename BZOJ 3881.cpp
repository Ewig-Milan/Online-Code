#include <bits/stdc++.h>
#define Lb(x) x & -x
using namespace std;

const int N = 2000100;

int n, m;
int tr[N][26], ne[N], idx, pt[N];
int L[N], R[N], cnt;

struct Bit_T {
    vector<int> sum;
    void cl(int n) {
        sum.resize(0);
        sum.resize(n + 100);
    }
    void modify(int x, int delta) {
        while(x <= cnt) {
            sum[x] += delta;
            x += Lb(x);
        }
    }
    int presum(int x) {
        int ans = 0;
        while(x) {
            ans += sum[x];
            x -= Lb(x);
        }
        return ans;
    }
    int query(int l, int r) {return presum(r) - presum(l - 1);}
}b_t;

struct CFS {
    int h[N], e[N << 1], ne[N << 1], idx;
    int dep[N], fa[N][22];
    void cl() {
        memset(h, -1, sizeof(h));
        idx = 0;
    }
    void add(int a, int b) {
        e[idx] = b, ne[idx] = h[a], h[a] = idx++;
        e[idx] = a, ne[idx] = h[b], h[b] = idx++;
    }
    void dfs(int x, int l) {
        L[x] = ++cnt, dep[x] = dep[l] + 1, fa[x][0] =  l;
        for(int i = 1; i <= 21; i++) fa[x][i] = fa[fa[x][i - 1]][i - 1];
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(j == l) continue;
            dfs(j, x);
        }
        R[x] = cnt;
    }
    int LCA(int x, int y) {
        if(dep[x] < dep[y]) swap(x, y);
        for(int i = 21; i >= 0; i--)
            if(dep[fa[x][i]] >= dep[y]) x = fa[x][i];
        if(x == y) return y;
        for(int i = 21; i >= 0; i--)
            if(fa[x][i] != fa[y][i])
                x = fa[x][i], y = fa[y][i];
        return fa[y][0];
    }
}mp;

void insert(char s[], int x) {
    int s_n = strlen(s + 1), j = 0;
    for(int i = 1; i <= s_n; i++) {
        if(!tr[j][s[i] - 'a']) tr[j][s[i] - 'a'] = ++idx;
        j = tr[j][s[i] - 'a'];
    }
    pt[x] = j;
}

void build() {
    queue<int> q;
    for(int i = 0; i < 26; i++)
        if(tr[0][i]) q.push(tr[0][i]), mp.add(0, tr[0][i]);
    while(!q.empty()) {
        int j = q.front();
        q.pop();
        for(int i = 0; i < 26; i++) {
            int k = tr[j][i];
            if(!k) tr[j][i] = tr[ne[j]][i];
            else ne[k] = tr[ne[j]][i], mp.add(k, ne[k]), q.push(k);
        }
    }
}

bool cmp(int a, int b) {return L[a] < L[b];}

int main() {
    mp.cl();
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        char c[N]; scanf("%s", c + 1);
        insert(c, i);
    }
    build();
    mp.dfs(0, 0);
    b_t.cl(cnt);
    scanf("%d", &m);
    while(m--) {
        int mode; scanf("%d", &mode);
        if(mode == 1) {
            char p[N]; scanf("%s", p + 1);
            int p_n = strlen(p + 1);
            vector<int> chg;
            for(int i = 1, j = 0; i <= p_n; i++) {
                j = tr[j][p[i] - 'a'];
                chg.push_back(j);
            }
            sort(chg.begin(), chg.end(), cmp);
            for(int i = 0; i < chg.size(); i++) {
                if(i) {
                    int lca = mp.LCA(chg[i], chg[i - 1]);
                    b_t.modify(L[lca], -1);
                }
                b_t.modify(L[chg[i]], 1);
            }
        } else {
            int x; scanf("%d", &x);
            printf("%d\n", b_t.query(L[pt[x]], R[pt[x]]));
        }
    }
    return 0;
}