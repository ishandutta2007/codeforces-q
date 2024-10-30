#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=1e5+5;
const ll B=300;

ll read()
{
	ll s=0;
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
struct query
{
	ll l,r,id;
	bool operator <(const query &a)const
	{
		if (l/B!=a.l/B) return l<a.l;
		return ((l/B)&1)?r>a.r:r<a.r;
	}
}q[N];
ll t[N],a[N],x[N],y[N],totx[N*2],toty[N*2],b[N*2],ans[N],now;
void addl(ll i)
{
	totx[x[i]]++;
	toty[y[i]]++;
	now+=toty[x[i]];
}
void addr(ll i)
{
	totx[x[i]]++;
	toty[y[i]]++;
	now+=totx[y[i]];
}
void dell(ll i)
{
	now-=toty[x[i]];
	totx[x[i]]--;
	toty[y[i]]--;
}
void delr(ll i)
{
	now-=totx[y[i]];
	totx[x[i]]--;
	toty[y[i]]--;
}

signed main(signed Goodbye,char *Wangang[])
{
	(void)Goodbye,(void)Wangang;
	ll n=read(),k=read(),cnt=0;
	for (ll i=1;i<=n;i++) t[i]=read();
	for (ll i=1;i<=n;i++) a[i]=t[i]==1?-read():read();
	for (ll i=1;i<=n;i++) a[i]+=a[i-1];
	for (ll i=1;i<=n;i++) b[++cnt]=x[i]=a[i-1];
	for (ll i=1;i<=n;i++) b[++cnt]=y[i]=a[i]+k;
	sort(b+1,b+1+cnt);
	cnt=unique(b+1,b+1+cnt)-b-1;
	for (ll i=1;i<=n;i++) x[i]=lower_bound(b+1,b+1+cnt,x[i])-b;
	for (ll i=1;i<=n;i++) y[i]=lower_bound(b+1,b+1+cnt,y[i])-b;
	ll m=read();
	for (ll i=1;i<=m;i++) q[i].l=read(),q[i].r=read(),q[i].id=i;
	sort(q+1,q+1+m);
	for (ll i=1,l=1,r=0;i<=m;i++)
	{
		while (l>q[i].l) addl(--l);
		while (r<q[i].r) addr(++r);
		while (l<q[i].l) dell(l++);
		while (r>q[i].r) delr(r--);
		ans[q[i].id]=now;
	}
	for (ll i=1;i<=m;i++) print(ans[i]);
	
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