#include <bits/stdc++.h>
using namespace std;

int q;
vector<int> fa, fb;

int gcd(int a, int b) {
    int g = 1;
    fa.resize(0), fb.resize(0);
    for(int i = 2; i <= a / i; i++)
        while(a % i == 0) a /= i, fa.push_back(i);
    if(a > 1) fa.push_back(a);
    for(int i = 2; i <= b / i; i++)
        while(b % i == 0) b /= i, fb.push_back(i);
    if(b > 1) fb.push_back(b);
    reverse(fa.begin(), fa.end());
    reverse(fb.begin(), fb.end());
    for(int i = 0; i < min(fa.size(), fb.size()); i++) {
        if(fa[i] != fb[i]) break;
        g *= fa[i];
    }
    return g;
}

int get(int x) {
    int cnt = 0;
    for(int i = 2; i <= x / i; i++)
        while(x % i == 0) cnt++, x /= i;
    if(x > 1) cnt++;
    return cnt;
}

int main() {
    scanf("%d", &q);
    while(q--) {
        int a, b; scanf("%d%d", &a, &b);
        int g = gcd(a, b);
        a /= g, b /= g;
        printf("%d\n", get(a) + get(b));
    }
    return 0;
}