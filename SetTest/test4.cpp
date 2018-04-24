#include<cstdio>
#include<algorithm>
#include<set>

#define mo 1000000

using namespace std;

set<int>a;

int n,bo,b,p,i,o,o1,o2,ans;

int main()
{
	scanf("%d",&n);
	set<int>::iterator it;
	for(i=1;i<=n;i++)
	{
		scanf("%d%d",&bo,&o);
		if(a.empty())b=bo,a.insert(o);
		else
		{
			if(bo==b)a.insert(o);
			else
			{
				o1=-211111111;
				o2=-211111111;
				it=a.lower_bound(o);
				o1=*it;
				if(it!=a.begin())
				{
					it--;
					o2=*it;
				}
				if(abs(o-o1)<abs(o-o2))ans=(ans+abs(o-o1)%mo)%mo,a.erase(o1);
				else ans=(ans+abs(o-o2)%mo)%mo,a.erase(o2);
			}
		}
	}
	printf("%d",ans);
}
