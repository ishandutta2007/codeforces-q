#include<bits/stdc++.h>

using namespace std;

void solve(){
    int n; cin>>n;
    long long ans=0;
    for (int i=1;i<=n;++i){
        int x; cin>>x;
        ans+=x;
    }
    int mx=0;
    for (int i=1;i<=n;++i){
        int x; cin>>x;
        ans+=x;
        mx=max(mx,x);
    }
    ans-=mx;
    cout<<ans<<'\n';
}
int main(){
    ios::sync_with_stdio(0);
    int t; cin>>t;
    while (t--) solve();
}