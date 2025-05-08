#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;

const int N = 2000100;
const ull sy = 29;

ull ans, ha[N], P[N];
int n, len, ans_cut;
bool flag;
char c[N];

void tran() {
    P[0] = 1;
    for(int i = 1; i <= n; i++)
        ha[i] = ha[i - 1] * sy + c[i] - 'A' + 1, P[i] = P[i - 1] * sy;
}

ull get(int l, int r) {return ha[r] - ha[l - 1] * P[r - l + 1];}

bool check(ull x, ull y) {return y * P[len] + y == x;}

int main() {
    scanf("%d", &n);
    scanf("%s", c + 1);
    if(n & 1 == 0) {
        puts("NOT POSSIBLE");
        return 0;
    }
    len = n >> 1;
    tran();
    for(int i = 1; i <= n; i++) {
        ull tmp = get(0, i - 1), half = 0;
        tmp *= P[n - i];
        if(i <= len) half = get(0, i - 1) * P[len - i + 1] + get(i + 1, len + 1);
        else half = get(1, len);
        tmp += get(i + 1, n);
        if(check(tmp, half)) {
            if(flag && ans != tmp) {
                puts("NOT UNIQUE");
                return 0;
            }
            ans = tmp, flag = true;
            ans_cut = i;
        }
    }
    if(!flag) puts("NOT POSSIBLE");
    else for(int i = 1; i <= len + (ans_cut <= len); i++) {
        if(i == ans_cut) continue;
        printf("%c", c[i]);
    }
    return 0;
}