#include <bits/stdc++.h>
#define db double
using namespace std;
const int N = 5100;
db f[N];
int n, m;
db DP(int r, int b) {
    for(int i = 1; i <= r; i++) for(int j = 0; j <= b; j++)
        f[j] = max((f[j] + 1) * i / (j + i) + ((j ? f[j - 1] : 0.0) - 1) * j / (j + i), 0.0);
    return f[b];
}
int main() {
    scanf("%d%d", &n, &m);
    printf("%.6lf", floor(DP(n, m) * 1e6) / 1e6);
    return 0;
}