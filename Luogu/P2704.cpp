#include <bits/stdc++.h>
using namespace std;

const int N = 12;

int n, m, ans, ma[N * 10], f[2][1 << N][1 << N], cnt[1 << N];
char c[N];
vector <int> ca;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%s", c + 1);
		for(int j = 1; j <= m; j++) ma[i] += (c[j] == 'P') ? (1 << (m - j)) : 0;
	}
	for(int i = 0; i < (1 << m); i++)
        if(!(i & i >> 1) && !(i & i >> 2)) ca.push_back(i);
        
    for(int i = 0, t = 0; i < (1 << m); t = ++i)
		while(t && ((t -= t & -t) | 1)) cnt[i]++;
    
	for(int i = 1; i <= n + 2; i++) {
		for(int a = 0; a < ca.size(); a++) if((ca[a] & ma[i]) == ca[a]) 
		for(int b = 0; b < ca.size(); b++) if(i <= 1 || (ca[b] & ma[i - 1]) == ca[b])
	    for(int c = 0; c < ca.size(); c++) if(i <= 2 || (ca[c] & ma[i - 2]) == ca[c])
    		if(!(ca[a] & ca[b]) && !(ca[c] & ca[b]) && !(ca[a] & ca[c]))
				f[i & 1][a][b] = max(f[1 - (i & 1)][b][c] + cnt[ca[a]], f[i & 1][a][b]);
	}
	printf("%d", f[n + 2 & 1][0][0]);
	return 0;
}