#include<cstdio>
#include<set>
#include<cstring>

#define mo 1000000007

using namespace std;

struct lhy{
	int x,y,l,next;
}edge[5010];

set<pair<int,int> >q;
set<pair<int,int> >::iterator it;

int ans[5010],dis[1510],b[1510],sum1[1510],sum2[1510],c[1510],son[1510];
int n,m,tot,x,y,l;

void dij(int st)
{
	q.clear();
	memset(dis,0x3f,sizeof(dis));
	memset(b,0,sizeof(b));
	dis[st]=0;
	tot=0;
	q.insert(make_pair(0,st));
	while(!q.empty())
	{
		it=q.begin();
		int x=(*it).second;
		q.erase(it);
		if(b[x])continue;
		c[++tot]=x;
		b[x]=1;
		for(int i=son[x];i;i=edge[i].next)
			if(dis[x]+edge[i].l<dis[edge[i].y])
			{
				dis[edge[i].y]=dis[x]+edge[i].l;
				q.insert(make_pair(dis[edge[i].y],edge[i].y));
			}
	}
	memset(sum1,0,sizeof(sum1));
	memset(sum2,0,sizeof(sum2));
	sum1[st]=1;
	for(int i=1;i<=tot;i++)
		sum2[c[i]]=1;
	for(int i=1;i<=tot;i++)
		for(int j=son[c[i]];j;j=edge[j].next)
			if(dis[c[i]]+edge[j].l==dis[edge[j].y])(sum1[edge[j].y]+=sum1[c[i]])%=mo;
	for(int i=tot;i;i--)
		for(int j=son[c[i]];j;j=edge[j].next)
			if(dis[c[i]]+edge[j].l==dis[edge[j].y])(sum2[c[i]]+=sum2[edge[j].y])%=mo;
	for(int i=1;i<=n;i++)
		for(int j=son[i];j;j=edge[j].next)
			if(dis[i]+edge[j].l==dis[edge[j].y])ans[j]=(ans[j]+1ll*sum1[i]*sum2[edge[j].y]%mo)%mo;
}

inline void add(int x,int y,int l)
{
	edge[++tot].x=x;edge[tot].y=y;edge[tot].l=l;edge[tot].next=son[x];son[x]=tot;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&l);
		add(x,y,l);
	}
	for(int i=1;i<=n;i++)dij(i);
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
}
