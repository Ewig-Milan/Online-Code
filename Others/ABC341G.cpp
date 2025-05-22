#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 200100;

bool cmp_k(ll a, ll b, ll c, ll d) { // b / a >= d / c
    return (double)b / a >= (double)d / c;
}

int n;
ll s[N];
double ans[N];
vector<int> cvh;
int r = -1;

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%lld", &s[i]);
    reverse(s + 1, s + n + 1);
    cvh.push_back(0), r++;
    for(int i = 1; i <= n; i++) {
        s[i] += s[i - 1];
        while(r && cmp_k(i - cvh[r - 1], s[i] - s[cvh[r - 1]], i - cvh[r], s[i] - s[cvh[r]])) r--;
        ans[i] = (double)(s[i] - s[cvh[r]]) / (i - cvh[r]);
        cvh.resize(++r); cvh.push_back(i);
    }
    for(int i = n; i; i--) printf("%.15lf\n", ans[i]);
    return 0;
}