#include <bits/stdc++.h>
using namespace std;

const int N = 100100;

int n, q, L;
int X[N];

int st[N][18], st_[N][18];

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &X[i]);
    scanf("%d", &L);
    for(int l = 1, r = 1; l <= n; l++) {
        while(r <= n && X[r] - X[l] <= L) r++;
        st[l][0] = r - 1;
    }
    for(int i = 1; i < 18; i++)
    for(int j = 1; j <= n; j++)
        st[j][i] = st[st[j][i - 1]][i - 1];

    for(int r = n, l = n; r; r--) {
        while(l && X[r] - X[l] <= L) l--;
        st_[r][0] = l + 1;
    }
    for(int i = 1; i < 18; i++)
    for(int j = 1; j <= n; j++)
        st_[j][i] = st_[st_[j][i - 1]][i - 1];
    
    scanf("%d", &q);
    while(q--) {
        int a, b; scanf("%d%d", &a, &b);
        int ans = 0;
        if(a < b) {
            for(int i = 17; i >= 0; i--) if(st[a][i] < b)
                ans += (1 << i), a = st[a][i];
        } else {
            for(int i = 17; i >= 0; i--) if(st_[a][i] > b)
                ans += (1 << i), a = st_[a][i];
        }
        printf("%d\n", ans + 1);
    }
    return 0;
}