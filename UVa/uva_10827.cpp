#include<cstdio>
#include<cstring>


#define N 160


int ss[N][N] ,num[N][N];
int main ()
{

    int t ,i ,j ,k ,n ,Ans;
    scanf("%d" ,&t);
    while(t--)
    {
        scanf("%d" ,&n);
        int maxx = -100000;
        for(i = 1 ;i <= n ;i ++)
            for(j = 1 ;j <= n ;j ++)
            {
                scanf("%d" ,&num[i][j]);
                num[i+n][j] = num[i][j+n] = num[i+n][j+n] = num[i][j];
                if(maxx < num[i][j]) maxx = num[i][j];
            }
        if(maxx <= 0)
        {
            printf("%d\n" ,maxx);
            continue;
        }
        memset(ss ,0 ,sizeof(ss));
        for(i = 1 ;i <= n * 2 ;i ++)
            for(j = 1 ;j <= n * 2;j ++)
                ss[i][j] = ss[i][j-1] + num[i][j];
        Ans = 0;
        for(i = 1 ;i <= n ;i ++)
            for(j = i ;j <= i + n - 1 && j <= n+n;j ++)
            {
                for(int ii = 1 ;ii <= n ;ii ++)
                {
                    int now = 0;
                    for(int jj = ii ;jj <= ii + n - 1 && jj <= n + n;jj ++)
                    {
                        now += ss[jj][j] - ss[jj][i - 1];
                        if(now < 0) now = 0;
                        if(Ans < now) Ans = now;
                    }
                }
            }
        printf("%d\n" ,Ans);
    }
    return 0;
}