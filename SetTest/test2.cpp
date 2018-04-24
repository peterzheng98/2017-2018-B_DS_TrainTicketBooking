#include<set>
#include<queue>
#include<cstdio>
#include<algorithm>

using namespace std;

multiset<int> s;
multiset<int>::iterator it;
priority_queue<int>q;

int n,k,a[500010],o;
long long ans;

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)
		scanf("%d",&o),s.insert(o);
	for(int i=1;i<=n;i++)
	{
		it=s.upper_bound(a[i]);
		if(it==s.begin())continue;
		it--;
		ans+=a[i];
		s.erase(it);
		q.push(a[i]-*it);
	}
	for(it=s.begin();it!=s.end();it++)
	{
		ans+=*it;
		k--;
	}
	if(k<0)return puts("NIE"),0;
	for(int i=1;i<=k;i++)
		ans-=q.top(),q.pop();
	printf("%lld",ans);
}
