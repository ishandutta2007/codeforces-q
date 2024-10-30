#include<bits/stdc++.h>
using namespace std;
const int N=4e5+5;

int read()
{
	int s=0;
	char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(int x)
{
	if (x<0) putchar('-'),x=-x;
	if (x<10) putchar(x+'0');
	else write(x/10),putchar(x%10+'0');
}
void print(int x=-1,char c='\n')
{
	write(x);
	putchar(c);
}
struct edge
{
	int to,nxt,id;
}e[N*2];
int head[N],cnte=0;
void add_edge(int u,int v,int w)
{
	e[++cnte].to=v;
	e[cnte].id=w;
	e[cnte].nxt=head[u];
	head[u]=cnte;
}
map<int,int>g[N];
int u[N],v[N],f[N];
void dx(int i,int x){f[i]=u[i]!=x;}
bool vis[N];
int st[N],top=0,dfn[N],low[N],cntdfn=0;
vector<int>mx(0),tmp;
void tarjan(int now,int father)
{
	vis[st[++top]=now]=1;
	low[now]=dfn[now]=++cntdfn;
	for (int i=head[now];i;i=e[i].nxt)
	{
		int to=e[i].to;
		if (to==father) continue;
		if (!dfn[to]) tarjan(to,now),low[now]=min(low[now],low[to]);
		else if (vis[to]) low[now]=min(low[now],dfn[to]);
	}
	if (low[now]==dfn[now])
	{
		tmp.clear();
		do tmp.push_back(st[top--]);while (tmp.back()!=now);
		if (mx.size()<tmp.size()) mx=tmp;
	}
}
void dfs1(int now)
{
	while (!g[now].empty())
	{
		int to=g[now].begin()->first,id=g[now].begin()->second;
		g[to].erase(now);
		g[now].erase(to);
		dx(id,now);
		dfs1(to);
	}
}
void dfs2(int now)
{
	for (int i=head[now];i;i=e[i].nxt)
	{
		int to=e[i].to;
		if (vis[to]) continue;
		vis[to]=1;
		dx(e[i].id,to);
		dfs2(to);
	}
}

signed main(signed Goodbye,char *Wangang[])
{
	(void)Goodbye,(void)Wangang;
	int n=read(),m=read();(void)n;
	for (int i=1;i<=m;i++)
	{
		u[i]=read(),v[i]=read();
		add_edge(u[i],v[i],i);
		add_edge(v[i],u[i],i);
	}
	tarjan(1,0);
	memset(vis,0,sizeof(vis));
	for (int i:mx) vis[i]=1;
	for (int i=1;i<=m;i++) if (vis[u[i]]&&vis[v[i]]) g[u[i]][v[i]]=i,g[v[i]][u[i]]=i;
	dfs1(mx[0]);
	for (int i:mx) dfs2(i);
	print(mx.size());
	for (int i=1;i<=m;i++)
	{
		if (f[i]) swap(u[i],v[i]);
		print(u[i],' '),print(v[i]);
	}
	
	return 0;
}
//...................  ..                        .    . . ..   .                                          .........
//..................  ....,]]]]]]`.   . .         . .,@@@@@@`.. .                                          ........
//.................. ,@@@@@@@@@@@@@@@@@@\].,]]]]]`,@@@@@@@@@@@. .                                          ........
//...................@^...[@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@`                                            .......
//..................,@`......\@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@`.                                          .......
//..................=@......../@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@`.                                         .......
//..................=@....../@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.                                         .......
//..................=@....=@@@@@@/[[[[[@@@@@@@@@@@@@@@@@/`...[@@@@^                                         .......
//..................=@.../@@@/`...........\@@@@@@@@@@@`........,@@@.                                     . ........
//.....,/@@@@@@@O\]`.@`.=@@@`...............\@@@@@@@@`...........@@^                                       ........
//...,@^........,/@@@@^,@@/..................,@@@@@@^............,@@.                                     .........
//...//......,/@[=OOOOO=@@....................,@@@@@...]O@@]......=@^                                     .........
//...@`....]@OO^.=OOO/@@@^.../@@@@@@@`.........=@@@@.=@@@@@@@@....=@^                                     .........
//..=@...,@OOO/.......=@@^.,@@@@@@@@@@@........=@@@@,@@@@@@@@@@...=@^                                    ..........
//..=@..=@`............\@^,@@@@@@@@@@@@@........@@@@=@@@@@@@@@@^..=@.                                 .............
//..=@.=@@OO@@]........@@@=@@@@@@@@@@@@@^......=@@@@O@@@@@@@@@@^..//.                                  ............
//..=@,@`.   .,\@`....=@\@@@@@@@@@@@@@@@^......O@@@@@@@@@@@@@@@..=@.  ......  .  . .......            .............
//..=@@/ ........\@`..=@.\@@@@@@@@@@@@@@^.....=@@@@@@@@@@@@@@@^./@`...,/@O[[...[[[O@@/.=/ .  ...... ...............
//...@@^   /@OOOO@@@\.=@  =@@@@@@@@@@@@@...../@@@@@@@@@@@@@@/]/@/...,@`...............[@@[[O@\`,[[@]...............
//...\@^  =@OOOOOOOO@\.@. OO@@@@@@@@@@/...,@@@@@@@@@@@@@@@@@@@@` .,@`.......,^...........,`...,\@`..,@.............
//...,@^ .=OOOOOOOOOO@\O^.\OOOO@@@@@@@@@@@@@@@@@@@@@@@@@@@@@/... ,@........=/..../@/[............\@...@`...........
//....=@. =@OOOOOOOOOO@/@.,@OOOO@@@@@@@@@@@@@@@@@@@@@@@/[...    .@`...........,@`.................,@..=O...........
//.....@\..\OOOOOOOOOO@^=@.,@OO@@@@@@@@@@@@@@@@@@@@@^         . .O......@O@^.,@....................=\..@*..........
//......\@..\@OOOOOOOO@O.,@`..@@@@@@@@@@@@@@@@@@@@@@O    .     .,O......=@@`.=^.....................@..@@@]`.......
//.......,@\..\@@OOOO@@^...\@@@@@@@@@@@@@@@@@@@@@@@@@.  ..,/@@@@@@..=@`......=O.........../^........@]@@O\*,O@`....
//.........,O@O]....,/@......@@@@@@@@@@@@@@@@@@@@@@@@^../@`*****=@@/@[....,[@`\@.......,@` .......,@/*********@\...
//.............,[\O@@@@@@@O@@@@@@@@@@@@@@@@@@@@@@@@@@@.=O*******[[[[O@@O]`]]]/@`@@@O@@O[[[***[[[\@@`*********,O@^..
//................**O@...../@@@@@@@@@@@@@@@@@@@@@@@@@@@`*****************,\@*****[[`**************************=@...
//...............****,@@@@@/*,@@@@@@@@@@@@@@@@@@@@@@@@O*******************************************************O/*..
//..................************[[\OO@@@@@@O/[[[[[[[*,@@\]**************************************************,@@*...
//.............................**********************.***[[@@O]]`***************************************]]@@[**....
//.........................................................*****,[[[OOOOOOOOOOOOOO@@@@@@@@@@@@O@OOOOO[[[****.......
//...............................................................................******************................