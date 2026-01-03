#include <bits/stdc++.h>
using namespace std;

const int N = 200100;

int n, a[N], mode;
int tmp[N];

bool check(int x) {
	for(int i = 1; i <= (n << 1) - 1; i++) tmp[i] = a[i] >= x ? 1 : -1;
	int dis_r = 1e9, dis_l = 1e9, l_mode, r_mode;
	for(int i = n + 1; i <= (n << 1) - 1; i++) if(tmp[i] == tmp[i - 1]) {
		dis_r = i - n, r_mode = tmp[i];
		break;
	}
	for(int i = n - 1; i; i--) if(tmp[i] == tmp[i + 1]) {
		dis_l = n - i, l_mode = tmp[i];
		break;
	}
	if(dis_r < 1e9 || dis_l < 1e9) {
		int dis, dis_mode;
		if(dis_r < dis_l) dis = dis_r, dis_mode = r_mode;
		else dis = dis = dis_l, dis_mode = l_mode;
		if(dis <= n) return dis_mode >= 0;
	}
	return tmp[n] * mode >= 0;
}

int main() {
	scanf("%d", &n), mode = (n & 1) ? 1 : -1;
	for(int i = 1; i <= (n << 1) - 1; i++) scanf("%d", &a[i]);

	int l = 1, r = (n << 1) - 1;
	while(l < r) {
		int mid = l + r + 1 >> 1;
		if(check(mid)) l = mid;
		else r = mid - 1;
	}
	printf("%d", l);
	return 0;
}