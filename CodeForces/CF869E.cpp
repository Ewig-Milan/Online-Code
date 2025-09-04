#include <bits/stdc++.h>
#define Lb(x) ((x) & -(x))
using namespace std;

const int N = 2600, M = 100100;

int n, m, q;

int RAND = 1;
int Rand() {
    int x = rand();
    x ^= (x >> RAND) ^ (x << 2);
    RAND++, RAND *= RAND, RAND %= 6;
    return x;
}

map<tuple<int, int, int, int>, int> mp;

struct Bit_T {
    int sum[N][N];
    void modify(int x, int y, int delta) {
        for(int i = x; i <= n + 1; i += Lb(i))
        for(int j = y; j <= m + 1; j += Lb(j))
            sum[i][j] ^= delta;
    }
    int query(int x, int y) {
        int res = 0;
        for(int i = x; i; i -= Lb(i))
        for(int j = y; j; j -= Lb(j))
            res ^= sum[i][j];
        return res;
    }
}t;

int main() {
    srand(time(0));
    scanf("%d%d%d", &n, &m, &q);
    while(q--) {
        int mode; scanf("%d", &mode);
        int x, y, X, Y; scanf("%d%d%d%d", &x, &y, &X, &Y);
        if(mode == 1) {
            int tmp = Rand();
            mp[{x, y, X, Y}] = tmp;
            t.modify(X + 1, Y + 1, tmp), t.modify(X + 1, y, tmp);
            t.modify(x, Y + 1, tmp), t.modify(x, y, tmp);
        } else if(mode == 2) {
            int tmp = mp[{x, y, X, Y}];
            t.modify(X + 1, Y + 1, tmp), t.modify(X + 1, y, tmp);
            t.modify(x, Y + 1, tmp), t.modify(x, y, tmp);
        } else puts(t.query(x, y) == t.query(X, Y) ? "Yes" : "No");
    }
    return 0;
}