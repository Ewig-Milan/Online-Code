#include <bits/stdc++.h>
using namespace std;

const int N = 100100;

int n, k, a[N], ans[N];
long long ANS;
int tmp_a[N], tmp_cnt;

void CDQ(int l, int r) {
    if(l == r) return;
    int mid = l + r >> 1;
    CDQ(l, mid); CDQ(mid + 1, r);
    tmp_cnt = 0;
    int i = l, j = mid + 1;
    while(i <= mid && j <= r)
        if(a[i] <= a[j]) tmp_a[++tmp_cnt] = a[i++];
        else tmp_a[++tmp_cnt] = a[j], ans[j++] += i - l;
    while(i <= mid) tmp_a[++tmp_cnt] = a[i++];
    while(j <= r) ans[j++] += i - l;
    for(int i = 1; i <= tmp_cnt; i++) a[i + l - 1] = tmp_a[i];
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]), a[i] -= k;
    for(int i = 1; i <= n; i++) a[i] += a[i - 1], ANS += a[i] >= 0;
    CDQ(1, n);
    for(int i = 1; i <= n; i++) ANS += ans[i];
    printf("%lld", ANS);
    return 0;
}