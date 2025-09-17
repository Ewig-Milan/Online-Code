#include <bits/stdc++.h>
#define int __int128
using namespace std;

const int N = 100100;

int n;
int d[N], s[N], f[N], dep[N], arr[N], m, top;
int A[N], _B[N], _C[N], B, C, lim;

int h[N], ne[N << 1], e[N << 1], idx;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ne[idx] = h[b], h[b] = idx++;
}

void dfs(int x, int l) {
    dep[x] = dep[l] + 1;
    f[x] = l;
    for(int i = h[x]; i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        dfs(j, x);
    }
    arr[++m] = x;
}

bool calc(int x) {
    if(C * top + B >= 1) return B * (top - x + 1) + C * (x + top) * (top - x + 1) / 2 >= lim;
    if(C * x + B >= 1)
    {
        int t =(B - 1) / (-C);
        return B * (t - x + 1) + C * (x + t) * (t - x + 1) / 2 + (top - t) >= lim;
    }
    return top - x + 1 >= lim;
}

bool check(int x) {
    for(int i = 1; i <= n; i++) {
        if(!_C[i]) {
            d[i] = x - (A[i] - 1) / max(_B[i], (int)1);
            d[i] = min(d[i], n);
            if(d[i] < dep[i]) return 0;
            continue;
        }
        top = x, B = _B[i], C = _C[i], lim = A[i];

        if(!calc(dep[i])) return 0;
        if(calc(n)) {d[i] = n; continue;}

        int l = dep[i], r = n;
        while(l < r) {
            int mid = l + r + 1 >> 1;
            if(calc(mid)) l = mid;
            else r = mid - 1;
        }
        d[i] = l;
    }
    for(int i = 1; i <= n; i++) if(f[arr[i]])
        d[f[arr[i]]] = min(d[f[arr[i]]], d[arr[i]] - 1);

    if(d[1] < 1) return 0;

    memset(s, 0, sizeof s);
    for(int i = 1; i <= n; i++) s[d[i]]++;
    for(int i = 1; i <= n; i++) {
        s[i] += s[i - 1];
        if(s[i] > i) return 0;
    }
    return 1;
}

signed main() {
    long long nn; scanf("%lld", &nn);
    n = nn;
    for(int i = 1; i <= n; i++) {
        long long a, b, c; scanf("%lld%lld%lld", &a, &b, &c);
        A[i] = a, _B[i] = b, _C[i] = c;
    }
    for(int i = 1; i < n; i++) {
        long long a, b; scanf("%lld%lld", &a, &b);
        add((int)a, (int)b);
    }
    dfs(1, 0);
    int l = n, r = 1e9;
    while(l < r)
    {
        int mid = l + r >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    printf("%lld", (long long)l);
    return 0;
}