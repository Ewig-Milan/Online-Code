//
// 注意两个问题：不可达 和 重边
//
#include <bits/stdc++.h>
#define int long long
#define fi first
#define se second
using namespace std;

const int N = 200100, inf = 1e18;

int n, m, Q;

int pre[N], suf[N];
int p_sht[N], s_sht[N];

int sht, sht_cnt[N], Nn;//0开头
//以上存的全是点
bool sht_flag[N << 1];

struct CFS {
    int h[N], e[N << 1], v[N << 1], ne[N << 1], idx;
    void cl() {memset(h, -1, sizeof h); idx = 0;}
    void add(int a, int b, int c) {e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;}

    pair<int, int> back[N];
    vector<int> rev_back[N];
    struct Node {
        int p, dis;
        friend bool operator < (const Node & a, const Node & b) {return a.dis > b.dis;}
    };
    int dji(int st, int (&dis)[N], int (&p_s)[N]) { //跑 p/s_sht st=1时跑sht_cnt
        for(int i = 0; i < N; i++) rev_back[i].resize(0), dis[i] = inf;
        bool flag[N]; memset(flag, 0, sizeof flag);
        int cnt = 0;
        priority_queue<Node> q;
        dis[st] = 0, back[st].fi = 0;
        q.push({st, 0});
        while(!q.empty()) {
            while(!q.empty() && flag[q.top().p]) q.pop();
            cnt++;
            if(cnt == n || q.empty()) break;
            int x = q.top().p;
            q.pop();
            flag[x] = true;
            for(int i = h[x]; ~i; i = ne[i]) {
                int j = e[i];
                if(flag[j]) continue;
                if(dis[j] > dis[x] + v[i]) {
                    dis[j] = dis[x] + v[i];
                    q.push({j, dis[j]});
                    back[j].fi = x;
                    back[j].se = i; //解决重边
                }
            }
        }
        for(int i = 1; i <= n; i++) rev_back[back[i].fi].push_back(i);
        if(st == 1) {
            int tmp_cnt = 0;
            for(int i = n; i; i = back[i].fi) {
                tmp_cnt++;
                if(back[i].fi) sht_flag[back[i].se] = true; //解决重边
            }
            Nn = tmp_cnt - 1;
            for(int i = n; i; i = back[i].fi) sht_cnt[i] = tmp_cnt--;
        }
        queue<pair<int, int> > bfs;
        bfs.push({st, sht_cnt[st]});
        while(!bfs.empty()) {
            int x = bfs.front().fi, tmp = bfs.front().se;
            bfs.pop();
            p_s[x] = tmp;
            for(int i : rev_back[x]) bfs.push({i, sht_cnt[i] ? sht_cnt[i] : tmp});
        }
        return dis[n];
    }
}mp;

struct Edge {int a, b, v, sht, pre, suf; bool flag;}edg[N];

struct TR {
//注意 ql < qr要判
    vector<int> mi, ly;
    void cl(int n) {
        mi.resize(n << 2); ly.resize(n << 2);
        for(int i = 0; i < n << 2; i++) mi[i] = inf, ly[i] = -1;
    }
    void push_up(int rt) {mi[rt] = min(mi[rt << 1], mi[rt << 1 | 1]);}
    void push_down(int rt) {
        if(ly[rt] == -1) return;
        if(ly[rt << 1] == -1) ly[rt << 1] = ly[rt];
        else ly[rt << 1] = min(ly[rt << 1], ly[rt]);
        if(ly[rt << 1 | 1] == -1) ly[rt << 1 | 1] = ly[rt];
        else ly[rt << 1 | 1] = min(ly[rt << 1 | 1], ly[rt]);
        mi[rt << 1] = min(mi[rt << 1], ly[rt]);
        mi[rt << 1 | 1] = min(mi[rt << 1 | 1], ly[rt]);
    }
    void modify(int rt, int l, int r, int ql, int qr, int x) {
        if(ql > qr) return;
        if(ql <= l && qr >= r) {
            mi[rt] = min(mi[rt], x);
            if(ly[rt] == -1) ly[rt] = x;
            else ly[rt] = min(ly[rt], x);
            return;
        }
        push_down(rt);
        int mid = l + r >> 1;
        if(ql <= mid) modify(rt << 1, l, mid, ql, qr, x);
        if(qr > mid) modify(rt << 1 | 1, mid + 1, r, ql, qr, x);
        push_up(rt);
    }
    int query(int rt, int l, int r, int n) {
        if(l == r) return mi[rt];
        push_down(rt);
        int mid = l + r >> 1;
        if(n <= mid) return query(rt << 1, l, mid, n);
        else return query(rt << 1 | 1, mid + 1, r, n);
    }
}tr;//存边 1开头

signed main() {
    mp.cl();
    scanf("%lld%lld%lld", &n, &m, &Q);
    for(int i = 1; i <= m; i++) {
        int a, b, c; scanf("%lld%lld%lld", &a, &b, &c);
        mp.add(a, b, c); mp.add(b, a, c);
        edg[i] = {a, b, c, inf, 0, 0, 0}; //第四项初始化为inf 解决不可达
    }
    sht = mp.dji(1, p_sht, pre);
    mp.dji(n, s_sht, suf);

    tr.cl(Nn);
    for(int i = 1; i <= m; i++) {
        edg[i].flag = sht_flag[(i - 1) << 1] | sht_flag[(i - 1) << 1 | 1]; //解决重边
        int a = edg[i].a, b = edg[i].b;
        if(edg[i].flag || s_sht[a] == inf) continue; //解决不可达
        if(p_sht[a] + s_sht[b] > p_sht[b] + s_sht[a]) {
            edg[i].sht = p_sht[b] + s_sht[a] + edg[i].v;
            edg[i].pre = pre[b], edg[i].suf = suf[a];
        } else {
            edg[i].sht = p_sht[a] + s_sht[b] + edg[i].v;
            edg[i].pre = pre[a], edg[i].suf = suf[b];
        }
        tr.modify(1, 1, Nn, edg[i].pre, edg[i].suf - 1, edg[i].sht);
    }
    
    while(Q--) {
        int a, b; scanf("%lld%lld", &a, &b);
        Edge tmp = edg[a];
        if(tmp.flag) {
            int tmp_sht = sht + b - tmp.v;
            if(b > tmp.v) printf("%lld\n", min(tmp_sht, tr.query(1, 1, Nn, min(sht_cnt[tmp.a], sht_cnt[tmp.b]))));
            else printf("%lld\n", tmp_sht);
        } else printf("%lld\n", min(sht, tmp.sht + b - tmp.v));
    }
    return 0;
}