#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#define MAX 200005
#define MOD 998244353
#define BASE 30
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

int main()
{
    int T;
    scanf("%d",&T);
    for(int t=0; t<T; t++)
    {
        char ss[10];
        scanf(" %s", ss);
        int len = strlen(ss);
        int scores[2] = {0};
        int player = len%2;

        for(int i=0; i<len; i++)
        {
            int res = (ss[i] - '0');
            scores[i%2] += res;
            scores[(i+1)%2] += (1-res);
        }

        if(scores[player]-scores[player^1] == 10-len)
        {
            printf("1");
        }
        else if (scores[player^1]-scores[player] == 10-len)
        {
            printf("0");
        }
        else
        {
            printf("-1");
        }
        printf("\n");
    }
    return 0;
}

