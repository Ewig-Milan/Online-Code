#include <iostream>
#include <random>
using namespace std;

int main() {
    freopen("#data.in", "w", stdout);
    int n = 1000; // 你可以修改 n 的值
    cout << n << endl;

    random_device rd;
    mt19937 gen(rd());

    for (int i = 1; i <= n; ++i) {
        uniform_int_distribution<> dis(1, n);
        int s = dis(gen);
        cout << s << (i == n ? '\n' : ' ');
    }
    return 0;
}