#include<bits/stdc++.h>
#define have(x,i) (st[x]<=st[i]&&ed[i]<=ed[x])
#define ll long long
using namespace std;
const int N=2e5+5;

int read()
{
	int s=0;
	char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(ll x)
{
	if (x<0) putchar('-'),x=-x;
	if (x<10) putchar(x+'0');
	else write(x/10),putchar(x%10+'0');
}
void print(ll x=-1,char c='\n')
{
	write(x);
	putchar(c);
}
struct edge
{
	int to,nxt;
}e[N*2];
int head[N],cnte=0;
void add_edge(int u,int v)
{
	e[++cnte].to=v;
	e[cnte].nxt=head[u];
	head[u]=cnte;
}
int st[N],ed[N],cnt,siz[N],bel[N],n;
void dfs(int now,int father)
{
	st[now]=++cnt;
	for (int i=head[now];i;i=e[i].nxt)
	{
		int to=e[i].to;
		if (to==father) continue;
		dfs(to,now);
	}
	ed[now]=cnt;
	siz[now]=ed[now]-st[now]+1;
}
void dfs1(int now,int father,int x)
{
	bel[now]=x;
	for (int i=head[now];i;i=e[i].nxt)
	{
		int to=e[i].to;
		if (to==father) continue;
		dfs1(to,now,x);
	}
}
void clear(int n)
{
	cnte=cnt=0;
	for (int i=0;i<n;i++) head[i]=0;
}
ll ans[N];
ll calc(int x,int y)
{
	if (!x) return 1LL*(n-siz[bel[y]])*siz[y];
	if (bel[x]==bel[y])
	{
		if (have(x,y)) return 1LL*(n-siz[bel[y]])*siz[y];
		if (have(y,x)) return 1LL*(n-siz[bel[x]])*siz[x];
		return 0;
	}
	return 1LL*siz[x]*siz[y];
}

signed main(signed Recall,char *_902_[])
{
	(void)Recall,(void)_902_;
	int T=read();
	while (T--)
	{
		n=read();
		clear(n);
		for (int i=1;i<n;i++)
		{
			int u=read(),v=read();
			add_edge(u,v);
			add_edge(v,u);
		}
		dfs(0,0);
		ans[0]=1LL*n*(n-1)/2;
		for (int i=1;i<=n+1;i++) ans[i]=0;
		int x=0,y=0,sum=1;
		for (int i=head[0];i;i=e[i].nxt)
		{
			int to=e[i].to;
			dfs1(to,0,to);
			ans[1]+=1LL*sum*siz[to];
			sum+=siz[to];
		}
		for (int i=1;i<n;i++)
		{
			if (!x&&!y) y=i;
			else
			{
				if (!have(i,y)&&!have(i,x))
				{
					if (have(y,i)) y=i;
					else if (have(x,i)) x=i;
					else break;
				}
				if (siz[x]<siz[y]) swap(x,y);
			}
			ans[i+1]=calc(x,y);
		}
		for (int i=0;i<=n;i++) print(ans[i]-ans[i+1],' ');puts("");
	}
	
	return 0;
}
//....................  ..                        .    . . ..   .                                          .........
//...................  ....,]]]]]]`.   . .         . .,@@@@@@`.. .                                          ........
//................... ,@@@@@@@@@@@@@@@@@@\].,]]]]]`,@@@@@@@@@@@. .                                          ........
//....................@^...[@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@`                                            .......
//...................,@`......\@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@`.                                          .......
//...................=@......../@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@`.                                         .......
//...................=@....../@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.                                         .......
//...................=@....=@@@@@@/[[[[[@@@@@@@@@@@@@@@@@/`...[@@@@^                                         .......
//...................=@.../@@@/`...........\@@@@@@@@@@@`........,@@@.                                     . ........
//......,/@@@@@@@O\]`.@`.=@@@`...............\@@@@@@@@`...........@@^                                       ........
//....,@^........,/@@@@^,@@/..................,@@@@@@^............,@@.                                     .........
//....//......,/@[=OOOOO=@@....................,@@@@@...]O@@]......=@^                                     .........
//....@`....]@OO^.=OOO/@@@^.../@@@@@@@`.........=@@@@.=@@@@@@@@....=@^                                     .........
//...=@...,@OOO/.......=@@^.,@@@@@@@@@@@........=@@@@,@@@@@@@@@@...=@^                                    ..........
//...=@..=@`............\@^,@@@@@@@@@@@@@........@@@@=@@@@@@@@@@^..=@.                                 .............
//...=@.=@@OO@@]........@@@=@@@@@@@@@@@@@^......=@@@@O@@@@@@@@@@^..//.                                  ............
//...=@,@`.   .,\@`....=@\@@@@@@@@@@@@@@@^......O@@@@@@@@@@@@@@@..=@.  ......  .  . .......            .............
//...=@@/ ........\@`..=@.\@@@@@@@@@@@@@@^.....=@@@@@@@@@@@@@@@^./@`...,/@O[[...[[[O@@/.=/ .  ...... ...............
//....@@^   /@OOOO@@@\.=@  =@@@@@@@@@@@@@...../@@@@@@@@@@@@@@/]/@/...,@`...............[@@[[O@\`,[[@]...............
//....\@^  =@OOOOOOOO@\.@. OO@@@@@@@@@@/...,@@@@@@@@@@@@@@@@@@@@` .,@`.......,^...........,`...,\@`..,@.............
//....,@^ .=OOOOOOOOOO@\O^.\OOOO@@@@@@@@@@@@@@@@@@@@@@@@@@@@@/... ,@........=/..../@/[............\@...@`...........
//.....=@. =@OOOOOOOOOO@/@.,@OOOO@@@@@@@@@@@@@@@@@@@@@@@/[...    .@`...........,@`.................,@..=O...........
//......@\..\OOOOOOOOOO@^=@.,@OO@@@@@@@@@@@@@@@@@@@@@^         . .O......@O@^.,@....................=\..@*..........
//.......\@..\@OOOOOOOO@O.,@`..@@@@@@@@@@@@@@@@@@@@@@O    .     .,O......=@@`.=^.....................@..@@@]`.......
//........,@\..\@@OOOO@@^...\@@@@@@@@@@@@@@@@@@@@@@@@@.  ..,/@@@@@@..=@`......=O.........../^........@]@@O\*,O@`....
//..........,O@O]....,/@......@@@@@@@@@@@@@@@@@@@@@@@@^../@`*****=@@/@[....,[@`\@.......,@` .......,@/*********@\...
//..............,[\O@@@@@@@O@@@@@@@@@@@@@@@@@@@@@@@@@@@.=O*******[[[[O@@O]`]]]/@`@@@O@@O[[[***[[[\@@`*********,O@^..
//.................**O@...../@@@@@@@@@@@@@@@@@@@@@@@@@@@`*****************,\@*****[[`**************************=@...
//................****,@@@@@/*,@@@@@@@@@@@@@@@@@@@@@@@@O*******************************************************O/*..
//...................************[[\OO@@@@@@O/[[[[[[[*,@@\]**************************************************,@@*...
//..............................**********************.***[[@@O]]`***************************************]]@@[**....
//..........................................................*****,[[[OOOOOOOOOOOOOO@@@@@@@@@@@@O@OOOOO[[[****.......
//................................................................................******************................