#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<map>
using namespace std;
const int MAXN=100005;
const int BASE[2]={223,233};
const int MOD[2]={1000000007,1000000009};
int pw[MAXN<<1][2];
void build()
{
    for(int i=(pw[0][0]=pw[0][1]=1);i<(MAXN<<1);i++)
        for(int j=0;j<2;j++)pw[i][j]=1LL*pw[i-1][j]*BASE[j]%MOD[j];
}
struct info
{
    int v[2],sz;
    info operator + (const info &r)const
    {
        int tv[2];
        for(int j=0;j<2;j++)
            tv[j]=(1LL*pw[r.sz][j]*v[j]+r.v[j])%MOD[j];
        return info{tv[0],tv[1],sz+r.sz};
    }
    bool operator < (const info &r)const
    {
        return v[0]==r.v[0] ? (v[1]==r.v[1] ? sz<r.sz : v[1]<r.v[1]) : v[0]<r.v[0];
    }
    bool operator == (const info &r)const
    {
        return v[0]==r.v[0] && v[1]==r.v[1] && sz==r.sz;
    }
};
vector<int>e[MAXN];
info dp[MAXN];
void dfs1(int u,int fa)
{
    vector<info>nxt;
    for(int i=0;i<(int)e[u].size();i++)
    {
        int v=e[u][i];
        if(v==fa)continue;
        dfs1(v,u);
        nxt.push_back(dp[v]);
    }
    dp[u]=info{'(','(',1};
    sort(nxt.begin(),nxt.end());
    for(int i=0;i<(int)nxt.size();i++)
        dp[u]=dp[u]+nxt[i];
    dp[u]=dp[u]+info{')',')',1};
}
map<info,int>mp;
void add(const info &t)
{
    mp[t]++;
}
void del(const info &t)
{
    if(--mp[t]==0)mp.erase(t);
}
int res,cnt;
void dfs2(int u,int fa,info o)
{
    vector<pair<info,int> >nxt;
    for(int i=0;i<(int)e[u].size();i++)
    {
        int v=e[u][i];
        if(v==fa)nxt.push_back(make_pair(o,v));
        else nxt.push_back(make_pair(dp[v],v));
    }
    info all=info{'(','(',1};
    sort(nxt.begin(),nxt.end());
    for(int i=0;i<(int)nxt.size();i++)
        all=all+nxt[i].first;
    all=all+info{')',')',1};
    del(dp[u]),add(all);
    if(cnt<(int)mp.size())res=u,cnt=(int)mp.size();
    vector<info>pre(nxt.size()),suf(nxt.size());
    if(!nxt.empty())pre.front()=suf.back()=info{0,0,0};
    for(int i=0;i<(int)nxt.size()-1;i++)
        pre[i+1]=pre[i]+nxt[i].first;
    for(int i=(int)nxt.size()-1;i>=1;i--)
        suf[i-1]=nxt[i].first+suf[i];
    for(int i=0;i<(int)nxt.size();i++)
    {
        int v=nxt[i].second;
        if(v==fa)continue;
        info tmp=info{'(','(',1}+pre[i]+suf[i]+info{')',')',1};
        del(all),add(tmp);
        dfs2(v,u,tmp);
        del(tmp),add(all);
    }
    del(all),add(dp[u]);
}
int main()
{
    build();
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs1(1,0);
    for(int i=1;i<=n;i++)
        add(dp[i]);
    dfs2(1,0,info{0,0,0});
    return 0*printf("%d",res);
}