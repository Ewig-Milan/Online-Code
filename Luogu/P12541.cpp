#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll collisions(std::vector<ll> x);

int hack() {
    int l = 1, r = 500000000;
    std::vector<ll> Q;
    while(l < r) {
        int mid = l + r >> 1;
        Q.resize(0);
        int tmp = max((int)sqrt(mid - l + 1), 1);
        for(int i = 1; i <= tmp; i++) Q.push_back((ll)i << 30);
        for(int i = l + tmp; i <= mid; i += tmp) Q.push_back(((ll)i * 2 - 1) << 29);
        Q.push_back(((ll)mid * 2 + 1) << 29);
        if(collisions(Q)) r = mid;
        else l = mid + 1;
    }
    l = l * 2 - 1;
    while(!collisions({1, l + 1})) l <<= 1;
    return l;
}