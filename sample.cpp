#include<cstdio>  
#include<iostream>  
#include<algorithm>  
#include<cstring>  
#include<cmath>  
#include<queue>  
using namespace std;  
int n,s,t,m;  
const int MAXM = 160000;    
const int MAXN = 400;    
const int INF = 0x3f3f3f3f;   
struct edge{  
    int to,cap,next;  
}e[MAXM];  
int head[MAXN],level[MAXN];  
int eid;  
void adde(int u,int v,int c)  
{  
    e[eid].to=v;  
    e[eid].cap=c;  
    e[eid].next=head[u];  
    head[u] = eid++;  
}  
int bfs()  
{  
    memset(level,-1,sizeof(level));  
    queue<int> q;  
    level[s] = 0;  
    q.push(s);  
    while(!q.empty())  
    {  
        int u = q.front();  
        q.pop();  
        for(int i=head[u];~i;i=e[i].next)  
        {  
            int v = e[i].to;  
            if(e[i].cap>0&&level[v]==-1)  
            {  
                level[v] = level[u]+1;  
                q.push(v);  
            }  
        }  
    }  
    return level[t]!=-1;  
}  
int dfs(int u,int f)  
{  
    if(u == t)return f;  
    int tmp;  
    for(int i=head[u];~i;i=e[i].next)  
    {  
        int v = e[i].to;  
        if(e[i].cap>0&&level[v]==level[u]+1)  
        {  
            tmp = dfs(v,min(f,e[i].cap));  
            if(tmp>0)  
            {  
                e[i].cap -= tmp;  
                e[i^1].cap += tmp;  
                return tmp;  
            }  
        }  
    }  
    level[u] = -1;  
    return 0;  
}  
int Dinic()  
{  
    int ans = 0,tmp;  
    while(bfs())  
        while((tmp = dfs(s,INF))>0)  
            ans +=tmp;        
    return ans;  
}  
int main(void)  
{  
    int a,b,c;  
    int kase = 0;  
    while(scanf("%d",&n),n)  
    {  
        memset(head,-1,sizeof(head));  
        scanf("%d%d%d",&s,&t,&m);  
        for(int i=1;i<=m;i++)  
        {  
            scanf("%d%d%d",&a,&b,&c);  
            adde(a,b,c);  
            adde(b,a,c);  
        }         
        printf( "Network %d\nThe bandwidth is %d.\n\n",++kase, Dinic() );  
    }  
    return 0;  
}  
