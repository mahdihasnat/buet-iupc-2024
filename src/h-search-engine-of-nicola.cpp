#include <bits/stdc++.h>
using namespace std;
#define MAX 100005
#define INF 1000000000000000000
#define EPS 0.0000000001
#define MASKS 20
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
vector<int> sort_cyclic_shifts(char *s) {
    int n = strlen(s);
    const int alphabet = 256;
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++)
        cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            int ind=p[i] + (1 << h);
            if(ind>=n) ind=ind-n;
            pair<int, int> cur = {c[p[i]], c[ind]};
            ind=p[i-1] + (1 << h);
            if(ind>=n) ind=ind-n;
            pair<int, int> prev = {c[p[i-1]], c[ind]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}
vector<int> suffix_array_construction(char *s) {
    int n=strlen(s);
    s[n]='#';
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    s[n]='\0';
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}
vector<int> lcp_construction(char *s, vector<int> const& p) {
    int n = strlen(s);
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++)
        rank[p[i]] = i;

    int k = 0;
    vector<int> lcp(n-1, 0);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k])
            k++;
        lcp[rank[i]] = k;
        if (k)
            k--;
    }
    return lcp;
}

vector<int> sa,lcp_arr;
vector<long long> lsum,ssum;
char s[MAX];
char qq[MAX];

int build()
{
    int n=strlen(s);
    sa=suffix_array_construction(s);
    lcp_arr=lcp_construction(s,sa);
    for(int i=0;i<sa.size();i++)
    {
        ssum.push_back(n-sa[i]);
        if(i) ssum[i]=ssum[i]+ssum[i-1];
        //printf("ssum[%d]=%lld\n",i,ssum[i]);
    }
    //printf("SA done!\n");
    for(int i=0;i<lcp_arr.size();i++)
    {
        lsum.push_back(lcp_arr[i]);
        if(i) lsum[i]=lsum[i]+lsum[i-1];
        //printf("lsum[%d]=%lld\n",i,lsum[i]);

    }
    //printf("LCP done!\n");
    return n;
}

int lex(int sidx,int pos,int n,char c)
{
    int idx=sa[sidx]+pos;
    if(idx>=n) return -1;
    if(s[idx]==c) return 0;
    else if(s[idx]<c) return -1;
    else return 1;
}

int low_search(int L,int R,int n,int pos,char c)
{
    int lo=L,hi=R;
    while(lo<hi)
    {
        int mid=(lo+hi)/2;
        if(hi-lo==1&&lex(lo,pos,n,c)==0) hi=lo;
        else if(hi-lo==1) lo=hi;
        else if(lex(mid,pos,n,c)<0) lo=mid;
        else hi=mid;
    }
    if(lex(lo,pos,n,c)) return n;
    return lo;
}

int high_search(int L,int R,int n,int pos,char c)
{
    int lo=L,hi=R;
    while(lo<hi)
    {
        int mid=(lo+hi)/2;
        if(hi-lo==1&&lex(hi,pos,n,c)==0) lo=hi;
        else if(hi-lo==1) hi=lo;
        else if(lex(mid,pos,n,c)>0) hi=mid;
        else lo=mid;
    }
    if(lex(lo,pos,n,c)) return -1;
    return lo;
}

long long subcnt(int L,int R)
{
    long long ans=ssum[R];
    if(L) ans=ans-ssum[L-1];
    if(L<R)
    {
        ans=ans-lsum[R-1];
        if(L) ans=ans+lsum[L-1];
    }
    return ans;
}

void answer_query(int n)
{
    int m=strlen(qq);
    int i;
    int L=0,R=n-1;
    for(i=0;i<m;i++)
    {
        int cl=low_search(L,R,n,i,qq[i]);
        int cr=high_search(L,R,n,i,qq[i]);
        if(cl>cr) break;
        L=cl;
        R=cr;
        long long ans=subcnt(L,R)-i;
        printf("%lld ",ans);
    }

    for(;i<m;i++)
    {
        printf("0 ");
    }
    printf("\n");
}

int main()
{
    int T;
    scanf("%d",&T);
    for(int t=0;t<T;t++)
    {
        scanf(" %s",s);
        int n=build();
        int q;
        scanf("%d",&q);
        for(int i=0;i<q;i++)
        {
            scanf(" %s",qq);
            answer_query(n);
        }
        lcp_arr.clear();
        sa.clear();
        lsum.clear();
        ssum.clear();
    }
    return 0;
}
