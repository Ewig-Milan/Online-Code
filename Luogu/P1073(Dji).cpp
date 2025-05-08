//
// 巧 + 偷懒Dji方法
//
#include <bits/stdc++.h>
using namespace std;

const int N = 100100, M = 500100;

int n, m, ans;
int w[N], mi[N], ma[N], cnt;
int flag[N];

struct CFS {
    int h[N], e[M << 1], ne[M << 1], idx;
    void cl() {memset(h, -1, sizeof(h)); idx = 0;}
    void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++;}
}mp, r_mp;

struct Node_mi {
    int p, mi;
    friend bool operator < (const Node_mi & a, const Node_mi & b) {return a.mi > b.mi;}
};
struct Node_ma {
    int p, ma;
    friend bool operator < (const Node_ma & a, const Node_ma & b) {return a.ma < b.ma;}
};

void dji(int st) {
    priority_queue<Node_mi> q;
    memset(mi, 127, sizeof(mi));
    memset(flag, 0, sizeof(flag));
    cnt = 0;
    mi[st] = w[st];
    q.push({st, mi[st]});
    while(!q.empty()) {
        while(!q.empty() && flag[q.top().p] == 2) q.pop();
        cnt++;
        if(q.empty() || cnt == n << 1) break;
        int x = q.top().p;
        flag[x]++;
        for(int i = mp.h[x]; ~i; i = mp.ne[i]) {
            int j = mp.e[i];
            if(flag[j] == 2) continue;
            if(mi[j] > min(w[j], mi[x])) {
                mi[j] = min(w[j], mi[x]);
                q.push({j, mi[j]});
            }
        }
    }
}

void r_dji(int st) {
    priority_queue<Node_ma> q;
    memset(ma, 0, sizeof(ma));
    memset(flag, 0, sizeof(flag));
    cnt = 0;
    ma[st] = w[st];
    q.push({st, ma[st]});
    while(!q.empty()) {
        while(!q.empty() && flag[q.top().p] == 2) q.pop();
        cnt++;
        if(q.empty() || cnt == n << 1) break;
        int x = q.top().p;
        flag[x]++;
        for(int i = r_mp.h[x]; ~i; i = r_mp.ne[i]) {
            int j = r_mp.e[i];
            if(flag[j] == 2) continue;
            if(ma[j] < max(w[j], ma[x])) {
                ma[j] = max(w[j], ma[x]);
                q.push({j, ma[j]});
            }
        }
    }
}

int main() {
    mp.cl(); r_mp.cl();
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &w[i]);
    for(int i = 1; i <= m; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        mp.add(a, b); r_mp.add(b, a);
        if(c == 2) {mp.add(b, a); r_mp.add(a, b);}
    }
    dji(1);
    r_dji(n);
    for(int i = 1; i <= n; i++) ans = max(ans, ma[i] - mi[i]);
    printf("%d", ans);
    return 0;
}