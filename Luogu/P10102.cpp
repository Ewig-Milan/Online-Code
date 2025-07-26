#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll N = 3100,  mod = 998244353;

ll T, n;

struct mat {
    ll x, y, a[N][N];
    mat(const ll X = 0, const ll Y = 0) : x(X), y(Y) {
        for(int i = 1; i <= x; i++)
        for(int j = 1; j <= y; j++)
            a[i][j] = 0;
    }
    void operator = (const mat &A) {
        x = A.x, y = A.y;
        for(int i = 1; i <= x; i++)
        {
            for(int j = 1; j <= y; j++)
                a[i][j] = A.a[i][j];
        }
    }
    mat operator * (const mat &A) const {
        mat ans(x, A.y);
        for(int i = 1; i <= x; i++)
        for(int j = 1; j <= A.y; j++)
        for(int k = 1; k <= y; k++)
            ans.a[i][j] =(ans.a[i][j] + a[i][k] * A.a[k][j] % mod) % mod;
        return ans;
    }
} a, b, c, H, L;
int main() {
    srand(time(0));
    scanf("%lld", &T);
    while(T--) {
        scanf("%lld", &n);
        a.x = n, a.y = n, b.x = n, b.y = n, c.x = n, c.y = n, H.x = 1, H.y = n, L.x = n, L.y = 1;
        for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            scanf("%lld", &a.a[i][j]);
        for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            scanf("%lld", &b.a[i][j]);
        for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            scanf("%lld", &c.a[i][j]);
        bool flag = 1;
        for(int T = 1; T <= 10; T++) {
            for(int i = 1; i <= n; i++)
                H.a[1][i] = rand() % mod;
            for(int i = 1; i <= n; i++)
                L.a[i][1] = rand() % mod;
            mat res = H * a;
            res = res * b, res = res * L;
            mat res2 = H * c;
            res2 = res2 * L;
            if(res.a[1][1] != res2.a[1][1])
            {
                flag = 0;
                break;
            }
        }
        if(flag) puts("Yes");
        else puts("No");
    }
}