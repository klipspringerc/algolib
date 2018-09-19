//
// Created by KevinCui on 15/9/18.
//
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
const int N= 1e4+10,M = 1e5+10;
struct Edge{
    int next;
    Edge(int next): next(next){}
};

int pre[N], dfs_clock,ebc_cnt,ebcno[N];
bool bridge[2*M];
vector<Edge> edges;
vector<int> G[N],ebc[N];

int dfs(int u, int fa){
    int lowu = pre[u] = ++dfs_clock;
    for(int i=0;i<G[u].size();i++)
    {
        int v =edges[G[u][i]].next;
        if(!pre[v])
        {
            int lowv = dfs(v,u);
            lowu = min(lowu,lowv);
            if(lowv>lowu)
            {
                bridge[G[u][i]] =true;
                bridge[G[u][i]^1] =true;
            }
        }
        else if(pre[v] <pre[u] && v!=fa)
        {
            lowu = min(lowu,pre[v]);
        }
    }
    return lowu;
}


void dfs2(int u)
{
    ebcno[u] =ebc_cnt;
    ebc[ebc_cnt].push_back(u);
    for(int i=0;i<G[u].size();i++)
    {
        if(bridge[G[u][i]]) continue;
        int v = edges[G[u][i]].next;
        if(!ebcno[v]) dfs2(v);
    }
}


int main()
{
    memset(pre,0,sizeof(pre));
    memset(ebcno, 0 , sizeof(ebcno));
    dfs_clock = ebc_cnt = 0;
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0;i<2*m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(i);
        edges.push_back(Edge(v));
        i++;
        G[v].push_back(i);
        edges.push_back(Edge(u));

    }
    for(int i=0;i<n;i++)
        if(!pre[i]) dfs(i,-1);
    for(int i=0;i<n;i++)
    {
        if(!ebcno[i])
        {
            ebc_cnt++;
            dfs2(i);
        }
    }

    int res = ebcno[0], sum =0;
    for(int i=0;i<n;i++)
        if(ebcno[i]==res)
            sum++;
    printf("%d", sum);

}


