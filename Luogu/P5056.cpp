#include <bits/stdc++.h>
#define ll long long
#define F(x, bit) (x << (bit << 1))
using namespace std;

const int N = 14, Possi = 100100, Pmod = 100007;

int n, m, endx/*行*/, endy/*列*/;
bool mp[N][N], pre, nw;
ll f[2][Possi], ANS;
int sta[2][Possi], idx[2];

int h[Possi], ne[Possi];

void add(int st, ll x) {
    int key = st % Pmod;
    for(int i = h[key]; ~i; i = ne[i]) if(sta[nw][i] == st) {
        f[nw][i] += x;
        return;
    }
    sta[nw][idx[nw]] = st, f[nw][idx[nw]] = x;
    ne[idx[nw]] = h[key], h[key] = idx[nw]++;
}

int get_st(int st, int bit) {return (st >> (bit << 1)) & 3;}

void trans(int i, int j, int st, ll x) {
    int l = get_st(st, j - 1), u = get_st(st, j);
    if(!mp[i][j]) {
        if(!(l | u)) add(st, x);
    } else if(!(l | u)) {
        if(mp[i + 1][j] && mp[i][j + 1]) add(st + F(1, j - 1) + F(2, j), x);
    } else if((!l) && u) {
        if(mp[i][j + 1]) add(st, x);
        if(mp[i + 1][j]) add(st - F(u, j) + F(u, j - 1), x);
    } else if(l && (!u)) {
        if(mp[i][j + 1]) add(st - F(l, j - 1) + F(l, j), x);
        if(mp[i + 1][j]) add(st, x);
    } else if(l == u) {
        if(l == 1) {
            int con = j, tmp = 1;
            while(tmp && ++con <= m)
                tmp += get_st(st, con) ? (get_st(st, con) == 1 ? 1 : -1) : 0;
            add(st - F(l, j - 1) - F(u, j) - F(1, con), x);
        } else {
            int con = j - 1, tmp = 1;
            while(tmp && --con >= 0)
                tmp += get_st(st, con) ? (get_st(st, con) == 1 ? -1 : 1) : 0;
            add(st - F(l, j - 1) - F(u, j) + F(1, con), x);
        }
    } else {
        if(l > u) add(st - F(l, j - 1) - F(u, j), x);
        else if(i == endx && j == endy) {
            add(st - F(l, j - 1) - F(u, j), x);
            ANS += x;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
        char c[15]; scanf("%s", c + 1);
        for(int j = 1; j <= m; j++) if(c[j] == '.') mp[i][j] = true;
    }
    endx = n, endy = m;
    while(!mp[endx][endy]) if(!endy--) endy = m, endx--;
    
    memset(h, -1, sizeof h);
    add(0, 1), nw = 1;
    
    for(int i = 1; i <= n; i++) {
        for(int k = 0; k < idx[pre]; k++) sta[pre][k] <<= 2;
        for(int j = 1; j <= m; j++) {
            idx[nw] = 0;
            memset(h, -1, sizeof h);
            for(int k = 0; k < idx[pre]; k++) trans(i, j, sta[pre][k], f[pre][k]);
            swap(pre, nw);
        }
    }
    printf("%lld", ANS);
    return 0;
}