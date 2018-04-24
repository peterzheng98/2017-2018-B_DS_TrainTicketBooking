#include<cstdio>
#include<set>

using namespace std;

set<int>a;

int n,x,opt,o;

namespace fastIO{
    #define BUF_SIZE 100000
    #define OUT_SIZE 100000
    inline char nc(){
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
        if (p1==pend){
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
        }
        return *p1++;
    }
    inline bool blank(char ch){return ch==' '||ch=='\n';}
    inline void read(int &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
    }
    struct Ostream_fwrite{
        char *buf,*p1,*pend;
        Ostream_fwrite(){buf=new char[BUF_SIZE];p1=buf;pend=buf+BUF_SIZE;}
        void out(char ch){
            if (p1==pend){
                fwrite(buf,1,BUF_SIZE,stdout);p1=buf;
            }
            *p1++=ch;
        }
        void print(int x){
            static char s[15],*s1;s1=s;
            if (!x)*s1++='0';
            while(x)*s1++=x%10+'0',x/=10;
            while(s1--!=s)out(*s1);
        }
        void flush(){if (p1!=buf){fwrite(buf,1,p1-buf,stdout);p1=buf;}}
        ~Ostream_fwrite(){flush();}
    }Ostream;
    inline void print(int x){Ostream.print(x);}
    #undef OUT_SIZE
    #undef BUF_SIZE
};
using namespace fastIO;

set<int>::iterator it,nowb,nowe;

int main()
{
	scanf("%*d%d",&n);
	nowb=a.begin();
	nowe=a.end();
	for(int i=1;i<=n;i++)
	{
		read(opt);
		if(opt!=3&&opt!=4)read(x);
		if(opt==1)
		{
			a.insert(x);
			nowb=a.begin();
			nowe=a.end();
			continue;
		}
		if(opt==2)
		{
			a.erase(x);
			nowb=a.begin();
			nowe=a.end();
			continue;
		}
		if(opt==3)
		{
			if(nowb!=nowe)printf("%d",*nowb);
			else putchar('-'),putchar('1');
			putchar('\n');
			continue;
		}
		if(opt==4)
		{
			it=nowe;
			if(nowe!=nowb)printf("%d",*(--it));
			else putchar('-'),putchar('1');
			putchar('\n');
			continue;
		}
		if(opt==5)
		{
			it=a.lower_bound(x);
			if(it!=nowb)printf("%d",*(--it));
			else putchar('-'),putchar('1');
			putchar('\n');
			continue;
		}
		if(opt==6)
		{
			it=a.upper_bound(x);
			if(it!=nowe)printf("%d",*it);
			else putchar('-'),putchar('1');
			putchar('\n');
			continue;
		}
		if(opt==7)
		{
			if(a.find(x)!=nowe)puts("1");
			else puts("-1");
		}
	}
}
