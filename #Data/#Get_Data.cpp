#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("#data.in", "w", stdout);
    srand(time(0));
    int n = 100000; // 你可以修改 n 的值
    cout << n << endl;
    for (int i = 1; i <= 16; ++i) {
        printf("%d ", rand() % 100000000);
    }
    putchar('\n');
    return 0;
}