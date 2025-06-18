#include <bits/stdc++.h>
using namespace std;

const int N = 100100;

int a[N << 1];

int main() {
    freopen("#data.in", "w", stdout);
    
    int n = 200;
    
    printf("%d\n", n);
    for(int i = 1; i <= (n << 1) - 1; i++) a[i] = i;
    random_shuffle(a + 1, a + (n << 1));
    for(int i = 1; i <= (n << 1) - 1; i++) printf("%d ", a[i]);
    putchar('\n');
    return 0;
}