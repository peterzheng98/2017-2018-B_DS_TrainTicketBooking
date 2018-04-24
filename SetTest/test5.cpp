#include<set>
#include<cmath>
#include<cstdio>
#include<algorithm>

using namespace std;

struct P{
	int x,y;
};

set<P>Point;

double nowans,ans[200010];
int anscnt,n,m,x,y,Px[100010],Py[100010],opt[200020],Del[200020],flag[100010];

int operator * (P a,P b)
{
	return a.x*b.y-a.y*b.x;
}

bool operator <(P a,P b)
{
	if(a.x==b.x)return a.y<b.y;
	return a.x<b.x;
}

P operator - (P a,P b)
{
	return (P){a.x-b.x,a.y-b.y};
}

double dis(P a,P b)
{
	return sqrt(1.*(a.x-b.x)*(a.x-b.x)+1.*(a.y-b.y)*(a.y-b.y));
}

void Insert(P now)
{
	set<P>::iterator r=Point.lower_bound(now),l=r,t;
	l--;
	if((*r-*l)*(now-*l)<0)return;
	nowans-=dis(*l,*r);
	while(1)
	{
		t=r;
		r++;
		if(r==Point.end())break;
		if((*r-now)*(*t-now)>0)break;
		nowans-=dis(*t,*r);
		Point.erase(t);
	}
	while(l!=Point.begin())
	{
		t=l;
		l--;
		if((*t-now)*(*l-now)>0)break;
		nowans-=dis(*l,*t);
		Point.erase(t);
	}
	Point.insert(now);
	t=l=r=Point.find(now);
	l--;
	r++;
	nowans+=dis(*l,now)+dis(now,*r);
}

int main()
{
	scanf("%d%d%d",&n,&x,&y);
	Point.insert((P){0,0});
	Point.insert((P){n,0});
	Point.insert((P){x,y});
	nowans=dis((P){0,0},(P){x,y})+dis((P){x,y},(P){n,0});
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&Px[i],&Py[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&opt[i]);
		if(opt[i]==1)scanf("%d",&Del[i]),flag[Del[i]]=1;
	}
	for(int i=1;i<=n;i++)
		if(!flag[i])Insert((P){Px[i],Py[i]});
	for(int i=m;i;i--)
	{
		if(opt[i]==1)Insert((P){Px[Del[i]],Py[Del[i]]});
		else ans[++anscnt]=nowans;
	}
	for(int i=anscnt;i;i--)printf("%.2lf\n",ans[i]);
}
