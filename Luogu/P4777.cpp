#include <bits/stdc++.h>
#define int __int128
#define ll long long
using namespace std;

const int N = 100100;

int exgcd(int a, int b, int &x, int &y) {
    if(!b) {
        x = 1, y = 0;
        return a;
    }
    int g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

ll n, rmd[N], p[N];

int EXCRT() {
    int RMD = rmd[1], P = p[1];
    for(int i = 2; i <= n; i++) {
        int Y, y;
        int g = exgcd(P, p[i], Y, y);
        if((rmd[i] - RMD) % g) return -1;
        RMD += (rmd[i] - RMD) * P / g * Y;
        P = P / g * p[i];
        RMD = (RMD % P + P) % P;
    }
    return RMD;
}

signed main() {
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++) scanf("%lld%lld", &p[i], &rmd[i]);
    
    printf("%lld", (ll)EXCRT());
    return 0;
}