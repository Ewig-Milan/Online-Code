#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 500100, M = 6000100;

int n, l, r, modu;

int h[N], e[M], v[M], ne[M], idx;
void add(int a, int b, int c) {e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;}

int dis[N];
struct Node {
    int id, dis;
    friend bool operator < (const Node &a, const Node &b) {return a.dis > b.dis;}
};
priority_queue<Node> q;
bool flag[N];
void dji(int s) {
    memset(dis, 63, sizeof dis);
    dis[s] = 0;
    q.push({s, 0});
    while(!q.empty()) {
        int x = q.top().id;
        q.pop();
        if(flag[x]) continue;
        flag[x] = 1;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(dis[j] > dis[x] + v[i]) {
                dis[j] = dis[x] + v[i];
                q.push({j, dis[j]});
            }
        }
    }
}

int calc(int x) {
    int res = 0;
    for(int i = 0; i < modu; i++) if(x >= dis[i]) res += (x - dis[i]) / modu + 1;
    return res;
}

signed main() {
    n = 3;
    memset(h, -1, sizeof h);
    scanf("%lld%lld%lld", &l, &r, &modu);
    for(int i = 1; i < n; i++) {
        int a; scanf("%lld", &a);
        for(int j = 0; j < modu; j++) add(j, (j + a) % modu, a);
    }
    dji(0);
    printf("%lld", calc(r) - calc(l - 1));
    return 0;
}