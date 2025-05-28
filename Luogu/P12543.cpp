#include <vector>
#include <algorithm>
#define Lb(x) (x & -x)
using namespace std;

void rotate(std::vector<int> t, int x);

void energy(int n, std::vector<int> v) {
    std::vector<std::pair<int, int> > V;
    int id = 0;
    for(int i : v) V.push_back({i, id++});
    std::sort(V.begin(), V.end());
    int l = 0, r = n >> 1;
    while(l < (n >> 1)) {
        int d = V[r].first - V[l].first + 25000;
        vector<int> tmp;
        tmp.push_back(V[l].second);
        rotate(tmp, d);
        l++, r++;
    }
}