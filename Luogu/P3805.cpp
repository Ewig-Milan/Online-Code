#include <bits/stdc++.h>
using namespace std;

const int N = 11000100;
char c[N], d[N << 1];
int n, p[N << 1], ans;

int main() {
    scanf("%s", c + 1);
    n = strlen(c + 1);
    d[0] =  '~', d[1] = '|';
    for(int i = 1; i <= n; i++) d[2 * i] = c[i], d[2 * i + 1] = '|';
    n = 2 * n + 1;
    for(int i = 1, mr = 0, mid = 0; i <= n; i++) {
        if(i >= mid && i <= mr) p[i] = min(mr - i + 1, p[mid * 2 - i]);
        while(d[i + p[i]] == d[i - p[i]]) p[i]++;
        if(i + p[i] > mr) mr = i + p[i] - 1, mid = i;
        ans = max(ans, p[i]);
    }
    printf("%d", ans - 1);
    return 0;
}