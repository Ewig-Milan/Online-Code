#include <bits/stdc++.h>
using namespace std;

const int N = 100100;

int a[N << 1];

int main() {
    srand(time(0));
    freopen("#data.in", "w", stdout);
    int T = 1000;
    printf("%d\n", T);
    while(T--) {
        printf("%d %d\n", 
            (long long)rand() * rand() % (long long)1e9, 
            (long long)rand() * rand() * rand() % (long long)1e9);
    }
    return 0;
}