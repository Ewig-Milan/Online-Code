#include <bits/stdc++.h>
using namespace std;

const int N = 200100;

int n, m, ans;
int l[N], r[N];
int f[N], back[N];
int method[N];

vector<int> P[N];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        P[b].push_back(a);
    }
    for(int i = 1, ma = 0; i < n; i++) {
        for(int x : P[i]) ma = max(ma, x);
        l[i + 1] = ma;
    }
    for(int i = n, mi = 1e9; i >= 1; i--) {
        for(int x : P[i]) mi = min(mi, x);
        r[i] = min(mi - 1, i - 1);
    }
    deque<int> q;
    for(int i = 1, x = 0; i <= n; i++, x = max(x, l[i])) {
        if(l[i] > r[i]) continue;
        while(!q.empty() && q.front() < l[i]) q.pop_front();
        while(x <= r[i]) {
            while(!q.empty() && f[x] >= f[q.back()]) q.pop_back();
            q.push_back(x);
            x++;
        }
        f[i] = f[q.front()] + 1, back[i] = q.front();
        if(f[i] >= f[ans]) ans = i;
    }
    int x = ans;
    while(x) method[x]++, x = back[x];
    for(int i = 2; i <= n; i++) method[i] += method[i - 1];
    for(int i = 1; i <= n; i++) for(int x : P[i])
        if(method[i] - method[x - 1] != 1) {puts("-1"); return 0;}
    printf("%d", f[ans]);
    return 0;
}