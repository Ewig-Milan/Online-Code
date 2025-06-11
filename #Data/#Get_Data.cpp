#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("#data.in", "w", stdout);
    srand(time(0));
    int n=2*(rand()%50+1); // 随机偶数行，范围2~100
    printf("%d\n",n);
    for(int i=1;i<=n;i++){
        int len;
        if(i & 1) len=rand()%20+1;
        else len=rand()%100+1;
        string s;
        for(int j=0;j<len;j++) s+='a'+rand()%4;
        int num;
        if(i & 1) num=rand()%500000+1;
        else len=rand()%490000+500001;
        printf("%s %d\n",s.c_str(),num);
    }
    return 0;
}