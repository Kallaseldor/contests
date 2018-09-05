// ESSE CODIGO NAO EH MEU E VAI DAR WA
// 100%

#include <bits/stdc++.h>
using namespace std;

const int N=1510;

int n,m,i,j,k,x;bitset<N>g[N];
int main(){
  scanf("%d%d",&n,&m);
  for(i=1;i<=n;i++){
    for(j=1;j<=m;j++){
      scanf("%d",&x);
      if(x%2)g[i][j]=1;
    }
    g[i][0]=1;
  }
  for(i=j=1;i<=m;i++){
    for(k=j;k<=n;k++)if(g[k][i])break;
    if(k>n)continue;
    swap(g[k],g[j]);
    for(k=j+1;k<=n;k++)if(g[k][i])g[k]^=g[j];
    j++;
  }
  for(;j<=n;j++)if(g[j][0])return puts("No"),0;
  puts("Yes");
}