//
// D into L 即 Div into Level 分层写法
//
#include <bits/stdc++.h>
using namespace std;

const int N = 100100, M = 500100;

int n, m, w[N];
int dis[N * 3];
bool flag[N * 3];
int h[N * 3], e[M << 3], ne[M << 3], v[M << 3], idx;
void add(int a, int b, int c) {e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;}

void SPFA(int st) {
    queue<int> q;
    memset(dis, 128, sizeof(dis));
    q.push(st);
    flag[st] = true, dis[st] = 0;
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        flag[x] = false;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(dis[j] < dis[x] + v[i]) {
                dis[j] = dis[x] + v[i];
                if(!flag[j]) q.push(j), flag[j] = true;
            }
        }
    }
}

int main() {
    memset(h, -1, sizeof(h));
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
        add(i, i + n, -w[i]), add(i + n, i + n + n, w[i]);
    }
    for(int i = 1; i <= m; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        add(a, b, 0), add(a + n, b + n, 0), add(a + n + n, b + n + n, 0);
        if(c == 2) add(b, a, 0), add(b + n, a + n, 0), add(b + n + n, a + n + n, 0);
    }
    SPFA(1);
    printf("%d", max(dis[n * 3], 0));
    return 0;
}