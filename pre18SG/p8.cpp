//
// Created by KevinCui on 16/9/18.
//

#include <cstdio>
#include <stack>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
using namespace std;


const int N = 8000;
set<int> home_set;
vector<int> home;
vector<int> inner_bcc;
struct Edge{
    int u,v;
};

bool cut[N];
int pre[N],bccno[N],dfs_clock,bcc_cnt;
vector<int> G[N], bcc[N];
stack<Edge> S;

int dfs(int u,int fa){
    int lowu = pre[u]=++dfs_clock;
    int child =0;
    for(int i=0;i<G[u].size();i++)
    {
        int v =G[u][i];
        Edge e =(Edge){u,v};
        if(!pre[v])
        {
            S.push(e);
            child++;
            int lowv = dfs(v,u);
            lowu = min(lowu,lowv);
            if(lowv>=pre[u]){
                cut[u] = true;
                bcc_cnt++;
                bcc[bcc_cnt].clear();
                for(;;)
                {
                    Edge x =S.top();
                    S.pop();
                    if(bccno[x.u]!=bcc_cnt){
                        bcc[bcc_cnt].push_back(x.u);
                        bccno[x.u]=bcc_cnt;
                    }
                    if(bccno[x.v] !=bcc_cnt){
                        bcc[bcc_cnt].push_back(x.v);
                        bccno[x.v] = bcc_cnt;
                    }
                    if(x.u == u && x.v == v) break;
                }
            }
        }

        else if(pre[v] < pre[u] && v!=fa)
        {
            S.push(e);
            lowu =min(lowu,pre[v]);
        }
    }
    if(fa<0 && child ==1) cut[u] =false;
    return lowu;
}


void find_bcc(int n){
    memset(pre,0,sizeof(pre));
    memset(cut, 0, sizeof(cut));
    memset(bccno,0,sizeof(bccno));
    dfs_clock = bcc_cnt =0;
    for(int i=0;i<n;i++)
        if(!pre[i]) dfs(i,-1);
}





bool ifInOut(int a, int b){
    bool ain = home_set.find(a) !=home_set.end();
    bool bin = home_set.find(b) !=home_set.end();
    return ain^bin;
}

int outer_para(int idx)
{
    int in_sum =0;
    for(int i=0;i<bcc[idx].size();i++)
    {
        int v = bcc[idx][i];
        for(int j=0;j<=G[v].size();j++)
        {
            int x =G[v][j];
            if(bccno[x] == idx)
                in_sum++;
        }
    }
    int l =bcc[idx].size();
    return l*6 - in_sum;
}


int main()
{
    int R,m;
    scanf("%d%d",&R,&m);

    int n=R*R*R - (R-1)*(R-1)*(R-1);
    for(int i=0;i<m;i++)
    {
        int x;
        scanf("%d",&x);
        home.push_back(x);
        home_set.insert(x);
    }



    int cnt =0;
    //upper part
    for(int i=0;i<R;i++)
    {
        int start = cnt+1;
        int length = R+i;
        int finish = start+length-1;
        int up_length = length-1;
        int up_finish = cnt;
        int up_start = up_finish-(up_length-1);
        for(int j=start;j<=finish;j++)
        {
            int ul,ur,l;
            ul = j-up_length-1;
            ur = j-up_length;
            l = j-1;
            if(ul>=up_start && ul<=up_finish && ul >=1 && !ifInOut(ul,j))
            {
                G[j-1].push_back(ul-1);
                G[ul-1].push_back(j-1);
            }
            if(ur>=up_start && ur<=up_finish && ur >=1 && !ifInOut(ur,j))
            {
                G[j-1].push_back(ur-1);
                G[ur-1].push_back(j-1);
            }
            if(l>=start && !ifInOut(l,j))
            {
                G[j-1].push_back(l-1);
                G[l-1].push_back(j-1);
            }
        }
        cnt += length;
    }

    //lower part
    for(int i=R-2;i>=0;i--)
    {
        int start = cnt+1;
        int length = R+i;
        int finish = start+length-1;
        int up_length = length+1;
        int up_finish = cnt;
        int up_start = up_finish-(up_length-1);
        for(int j=start;j<=finish;j++)
        {
            int ul,ur,l;
            ul = j-up_length;
            ur = j-up_length+1;
            l = j-1;
            if(ul>=up_start && ul<=up_finish && !ifInOut(ul,j))
            {
                G[j-1].push_back(ul-1);
                G[ul-1].push_back(j-1);
            }
            if(ur>=up_start && ur<=up_finish && !ifInOut(ur,j))
            {
                G[j-1].push_back(ur-1);
                G[ur-1].push_back(j-1);
            }
            if(l>=start && !ifInOut(l,j))
            {
                G[j-1].push_back(l-1);
                G[l-1].push_back(j-1);
            }
        }
        cnt += length;
    }
    find_bcc(n);
    int home_bcc = bccno[home[0]-1];
    for(int i=1;i<=bcc_cnt;i++)
    {
        if(i == home_bcc) continue;
        bool ifOut =false;
        for(int j=0;j<=bcc[i].size();j++)
        {
            int u = bcc[i][j];
            if(G[u].size()<6)
            {
                ifOut = true;
                break;
            }

        }

        if(!ifOut)
            inner_bcc.push_back(i);
    }
    int res = 0;
    res =outer_para(home_bcc);
//    for(int i=0;i<inner_bcc.size();i++)
//    {
//        res -= outer_para(inner_bcc[i]);
//    }
    printf("%d",res);

}