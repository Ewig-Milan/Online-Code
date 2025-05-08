#include <bits/stdc++.h>
using namespace std;

const int mod = 2007;

int n, T;

int quick_p(int x, int a) {
    int ans = 1;
    while(a) {
        if(a & 1) ans *= x, ans %= mod;
        x *= x, x %= mod, a >>= 1;
    }
    return ans;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        printf("%d\n", (long long)(quick_p(5, n - 1) * 4 * n) % mod);
    }
    return 0;
}