#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 3000100;
ll t[N], c[N], f[N];

int main() {
    int n, s;
    scanf("%d%d", &n, &s);
    for(int i = 1; i <= n; i++) {
        scanf("%lld%lld", &t[i], &c[i]);
        t[i] += t[i - 1];
        c[i] += c[i - 1];
    }
    deque<int> q;
    q.push_back(0);
    for(int i = 1; i <= n; i++) {
        while(q.size() >= 2 && f[q[1]] - f[q[0]] <= (t[i] + s) * (c[q[1]] - c[q[0]])) q.pop_front();
        int k = q.front();
        f[i] = f[k] - (t[i] + s) * c[k] + c[i] * t[i] + s * c[n];
        while(q.size() >= 2 && 
            (f[q.back()] - f[q[q.size() - 2]]) * (c[i] - c[q.back()]) >= (f[i] - f[q.back()]) * (c[q.back()] - c[q[q.size() - 2]]))
            q.pop_back();
        q.push_back(i);
    }
    printf("%lld", f[n]);
    return 0;
}
