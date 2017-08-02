#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdlib>
#define LL long long
#define CLR(a,x) memset(a,x,sizeof(a))
using namespace std;
const int maxm=410;
const int INF=0x3f3f3f3f;
const int mod=998244353;
const int N=500000+5;
inline LL SUB(LL x,LL y){return (x-y<0)?x-y+mod:x-y;}
LL qpow(LL a,int t){
    LL ans=1LL;
    for (;t;t>>=1){if (t&1) ans=(ans*a)%mod;a=(a*a)%mod;}
    return ans;
}
LL fac[N+10],inv[N+10];
int deg[maxm],d[maxm][maxm];
LL a[maxm][maxm];
int m;
void init(){
    fac[0]=1LL;
    for (int i=1;i<=N;i++) fac[i]=(fac[i-1]*i)%mod;
    inv[N]=qpow(fac[N],mod-2);
    for (int i=N-1;i>=0;i--) inv[i]=(inv[i+1]*(i+1))%mod;
}
LL guass(int n){
    LL ans=1LL;bool f=false;
    for (int i=1;i<=n;i++){
        if (a[i][i]==0LL){
            int j=i+1;
            while (j<=n&&a[j][i]==0) j++;
            if (j>n) return 0LL;
            for (int k=i;k<=n;k++) swap(a[i][k],a[j][k]);
            f=!f;
        }
        ans=ans*a[i][i]%mod;
        LL x=qpow(a[i][i],mod-2);
        for (int k=i+1;k<=n;k++) a[i][k]=a[i][k]*x%mod;
        for (int j=i+1;j<=n;j++){
            if (a[j][i]==0LL) continue;
            for (int k=i+1;k<=n;k++) a[j][k]=SUB(a[j][k],a[j][i]*a[i][k]%mod);
        }
    }
    return f?mod-ans:ans;
}
void work(){
    for (int i=1;i<=m;i++) deg[i]=0;
    for (int i=1;i<=m;i++)
        for(int j=1;j<=m;j++) scanf("%d",&d[i][j]);
    for (int i=1;i<=m;i++){
        LL indeg=0LL,outdeg=0LL;
        for (int j=1;j<=m;j++) {indeg+=d[j][i];outdeg+=d[i][j];}
        if (indeg!=outdeg) {puts("0");return;}
        deg[i]=outdeg;
    }
    for (int i=1;i<=m;i++)
        for(int j=1;j<=m;j++) a[i][j]=SUB((i^j)?mod:deg[i],d[i][j]);
    LL ans=guass(m-1)*fac[deg[1]]%mod;
    for (int i=2;i<=m;i++) if (deg[i]>0) ans=ans*fac[deg[i]-1]%mod;
    for (int i=1;i<=m;i++)
        for (int j=1;j<=m;j++) ans=ans*inv[d[i][j]]%mod;
    printf("%lld\n",ans);
}
int main(){
    #ifdef VGel
    freopen("1009.in","r",stdin);
    #endif // VGel
    int T_T=0;
    init();
    while(~scanf("%d",&m)){
        printf("Case #%d: ",++T_T);
        work();
    }
    return 0;
}
