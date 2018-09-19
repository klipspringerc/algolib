//
// // 17 Asia Daejeon
// Created by KevinCui on 13/9/18.
//

#include <vector>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

vector<int>dmap[123456],mmap[123456];
int ind[123456];
int main() {
    int n,m,i,j,k, x,y,des;
    scanf("%d%d",&n, &m);
    printf("OK\n");
    for(i=0;i<m;i++)
    {
        scanf("%d%d",&x,&y);
        mmap[x].push_back(y);
        mmap[y].push_back(x);
    }
    printf("OK\n");
    for(i=0;i<n;i++)
    {
        dmap[i].push_back(mmap[i].size());
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<mmap[i].size();j++)
        {
            des = mmap[i][j];
            if(dmap[des][0] > dmap[i][0])
            {
                dmap[i].push_back(des); //小->大
            }
        }
    }
    int ans = 0, vis=0;
    memset(ind,0,sizeof(ind));
    queue<int>q, q1;
    //for ind
    for(i=0;i<n;i++) //小点
    {
        for(j=0;j<mmap[i].size();j++)
        {
            des = mmap[i][j]; //大
            ind[des]++;
        }
    }
    int u,v;
    while(vis!=n)
    {
        while(!q.empty())
        {
            u = q.front(); //small
            vis++;
            q.pop();
            for(i=1;i<dmap[u].size();i++) {
                v = dmap[u][i]; //big
                ind[v]--;
                if (ind[v] == 0) {
                    q1.push(v);
                }
            }
        }
        ans++;
        while(!q1.empty())
        {
            u = q1.front();
            q1.pop();
            q.push(u);
        }

    }
    printf("%d\n", ans);

    return 0;
}