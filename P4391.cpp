#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;

const int N = 1000100;
const ull sy = 29;

int n;
ull ha[N], P[N];
char c[N];

void tran(char s[]) {
    P[0] = 1;
    for(int i = 1; i <= n; i++)
        ha[i] = ha[i - 1] * sy + s[i] - 'a' + 1, P[i] = P[i - 1] * sy;
}

ull get(int l, int r) {return ha[r] - ha[l - 1] * P[r - l + 1];}

int main() {
    scanf("%d", &n);
    scanf("%s", c + 1);
    tran(c);
    for(int i = 1; i <= n; i++)
        if(get(1, n - i) == get(i + 1, n)) {
            printf("%d", i);
            break;
        }
    return 0;
}