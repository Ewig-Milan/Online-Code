#include <bits/stdc++.h>
#define ll long long
#define F(i, j) f[j] + (C[i] - C[j] + i - j - 1 - L) * (C[i] - C[j] + i - j - 1 - L)
using namespace std;

const int N = 50100;

int n, L;
ll C[N], f[N];

struct P {int l, r, p;};

void work() {
    deque<P> q;
    q.push_back({1, n, 0});
    for(int i = 1; i <= n; i++) {
        while(q.front().r < i) q.pop_front();
        f[i] = F(i, q.front().p);
		if(F(n, q.back().p) < F(n, i)) continue;
        while(q.back().l > i && F(q.back().l, i) <= F(q.back().l, q.back().p)) q.pop_back();
        P & bk = q.back();
        int l = bk.l, r = bk.r;
        while(l < r) {
            int mid = l + r + 1 >> 1;
            if(F(mid, bk.p) < F(mid, i)) l = mid;
            else r = mid - 1;
        }
        bk.r = l;
        q.push_back({l + 1, n, i});
    }
    printf("%lld", f[n]);
}

int main() {
    scanf("%d%d", &n, &L);
    for(int i = 1; i <= n; i++) scanf("%lld", &C[i]), C[i] += C[i - 1];
    work();
    return 0;
}