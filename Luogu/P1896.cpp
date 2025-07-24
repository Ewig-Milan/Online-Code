#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n, k;
ll cnt[1 << 10], f[15][100][1 << 10];
vector <int> ca, p[1 << 10];
void get_() {
	for(int i = 0, j = 0; i < (1 << n); j = ++i) while(j) {if(j & 1) cnt[i]++; j >>= 1;} 
	for(int i = 0; i < (1 << n); i++) if((i & (i >> 1)) == 0) ca.push_back(i);
	for(int i = 0; i < ca.size(); i++) for(int j = 0; j < ca.size(); j++)
	if(((ca[i] | ca[j]) & ((ca[i] | ca[j]) >> 1)) == 0 && !(ca[i] & ca[j])) p[ca[i]].push_back(ca[j]);
	return;
}
int main() {
	scanf("%d%d", &n, &k);
	get_();
	for(int i = 0; i <= ca.size(); i++)
	f[0][0][0] = 1;
	for(int i = 1; i <= n + 1; i++) for(int j = 0; j <= k; j++)
	for(int m = 0; m < ca.size(); m++) for(int b = 0; b < p[ca[m]].size(); b++)
	if(j >= cnt[ca[m]])	f[i][j][ca[m]] += f[i - 1][j - cnt[ca[m]]][p[ca[m]][b]];
	printf("%lld", f[n + 1][k][0]);
	return 0;
}