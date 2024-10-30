#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
const int p=1e9+7;

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
void add(int &x,int y){x+=y;if (x>=p) x-=p;if (x<0) x+=p;}
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
int f[N][2],ans=0,a[N];
void dfs1(int now,int father)
{
	f[now][1]=1;
	f[now][0]=0;
	for (int i=head[now];i;i=e[i].nxt)
	{
		int to=e[i].to;
		if (to==father) continue;
		dfs1(to,now);
		add(ans,1LL*f[now][1]*f[to][0]%p*a[now]%p);
		add(ans,-1LL*f[now][0]*f[to][1]%p*a[now]%p);
		f[now][0]+=f[to][1];
		f[now][1]+=f[to][0];
	}
}
void dfs2(int now,int father,int x,int y)
{
	add(ans,1LL*f[now][1]*x%p*a[now]%p);
	add(ans,-1LL*f[now][0]*y%p*a[now]%p);
	f[now][0]+=y,f[now][1]+=x;
	for (int i=head[now];i;i=e[i].nxt)
	{
		int to=e[i].to;
		if (to==father) continue;
		int x=f[now][0]-f[to][1];
		int y=f[now][1]-f[to][0];
		dfs2(to,now,x,y);
	}
}

signed main(signed Goodbye,char *Wangang[])
{
	(void)Goodbye,(void)Wangang;
	int n=read();
	for (int i=1;i<=n;i++) a[i]=read();
	for (int i=1;i<n;i++)
	{
		int u=read(),v=read();
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,0,0,0);
	ans=ans*2%p;
	for (int i=1;i<=n;i++) add(ans,a[i]);
	print(ans);
	
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