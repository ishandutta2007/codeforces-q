#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;

int read()
{
	int s=0;
	char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
int get()
{
	char c=getchar();
	while (c<'0'||'1'<c) c=getchar();
	return c=='1';
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
bool is[N];
int s[N],fa[N*2],siz[N*2],c[N],n,k,ans=0;
int find(int x)
{
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
void merge(int x,int y)
{
//	print(x,',');print(y);
	x=find(x),y=find(y);
	if (x==y) return;
	if (is[(y-1)%k+1])
	{
		fa[x]=y;
		siz[y]+=siz[x];
		siz[x]=0;
	}
	else
	{
		fa[y]=x;
		siz[x]+=siz[y];
		siz[y]=0;
	}
}
vector<int>bel[N];
void change(int x,int y)
{
	is[x]=1;
	ans-=siz[x+c[x]*k];
	c[x]=y;
	ans+=siz[x+c[x]*k];
}

signed main(signed Recall,char *_902_[])
{
	(void)Recall,(void)_902_;
	n=read(),k=read();
	for (int i=1;i<=n;i++) s[i]=get();
	for (int i=1;i<=k;i++)
	{
		int m=read();
		for (int j=1;j<=m;j++) bel[read()].push_back(i);
	}
	for (int i=1;i<=k*2;i++) fa[i]=i,siz[i]=i>k;
	for (int i=1;i<=n;i++)
	{
		if ((int)bel[i].size()==1)
		{
			int x=find(bel[i][0]+k*!s[i]);
			change((x-1)%k+1,x>k);
		}
		else if ((int)bel[i].size()==2)
		{
			int x=bel[i][0],y=bel[i][1];
			int tmpx=(find(x)-1)%k+1,tmpy=(find(y)-1)%k+1;
			if (tmpx!=tmpy)
			{
				ans-=siz[tmpx+c[tmpx]*k];
				ans-=siz[tmpy+c[tmpy]*k];
//				print(ans,',');
//				print(tmpx,' ');print(tmpy);
				if (s[i]) merge(x,y),merge(x+k,y+k);
					 else merge(x,y+k),merge(x+k,y);
//				for (int i=1;i<=k*2;i++) print(find(i),' ');puts("");
//				for (int i=1;i<=k*2;i++) print(siz[i],' ');puts("");
				x=(find(x)-1)%k+1;
				if (!is[x]) c[x]=siz[x]>siz[x+k];
				ans+=siz[x+c[x]*k];
			}
		}
		print(ans);
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