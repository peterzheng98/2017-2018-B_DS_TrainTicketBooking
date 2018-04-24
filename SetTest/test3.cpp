#include<set>
#include<cstdio>

using namespace std;

int n,m,x,y;
int ans[200010],sum[200010];
set<int>a[200010];
set<int>::iterator it;

inline void read(int &x)
{
	x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
}

int main()
{
	read(n),read(m);
	for(int i=1;i<=m;i++)
	{
		char ch=getchar();
		while(ch!='!'&&ch!='+'&&ch!='-')ch=getchar();
		if(ch=='!')
		{
			read(x);
			sum[x]++;
		}
		if(ch=='+')
		{
			read(x),read(y);
			ans[x]-=sum[y];
			ans[y]-=sum[x];
			a[x].insert(y);
			a[y].insert(x);
		}
		if(ch=='-')
		{
			read(x),read(y);
			ans[x]+=sum[y];
			ans[y]+=sum[x];
			a[x].erase(y);
			a[y].erase(x);
		}
	}
	for(int i=1;i<=n;i++)
		for(it=a[i].begin();it!=a[i].end();it++)
			ans[*it]+=sum[i];
	for(int i=1;i<n;i++)
		printf("%d ",ans[i]);
	printf("%d\n",ans[n]);
}
