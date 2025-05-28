#include <bits/stdc++.h>
using namespace std;

const int N = 100100;

int n, a[N], last[2], cnt0, cnt1;
double A, B, C;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 0; i <= 30; i++) {
        last[0] = last[1] = 0;
        cnt0 = cnt1 = 0;
        for (int j = 1; j <= n; j++) {
            bool now = (a[j] >> i) & 1;
            double ret = (double)(1 << i) / n / n;
            if (now) {
                B += ret + 2.0 * ret * (j - (last[0] + 1));
                C += ret + 2.0 * ret * (j - 1);
                A += ret + 2.0 * ret * cnt0;
            } else {
                C += 2.0 * ret * last[1];
                A += 2.0 * ret * cnt1;
            }
            last[now] = j, cnt0++;
            if (now) swap(cnt0, cnt1);
        }
    }
    printf("%.3lf %.3lf %.3lf", A, B, C);
    return 0;
}