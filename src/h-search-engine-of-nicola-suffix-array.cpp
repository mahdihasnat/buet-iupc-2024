///****In the name of ALLAH, most Gracious, most Compassionate****//

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int, int> pii;

#define ALL(a) a.begin(), a.end()
#define FastIO ios::sync_with_stdio(false); cin.tie(0);cout.tie(0)
#define IN freopen("input.txt","r+",stdin)
#define OUT freopen("output.txt","w+",stdout)

#define DBG(a) cerr<< "line "<<__LINE__ <<" : "<< #a <<" --> "<<(a)<<endl
#define NL cerr<<endl

template < class T1,class T2>
ostream &operator <<(ostream &os,const pair < T1,T2 > &p)
{
    os<<"{"<<p.first<<","<<p.second<<"}";
    return os;
}
template <class T , size_t N>
ostream &operator <<(ostream &os,const array <T,N> &a)
{
	os<<"{";
	for(auto x: a)
		os<<x<<" ";
	os<<"}";
	return os;
}

template <class T>
ostream &operator <<(ostream &os,const vector<T> &a)
{
	os<<"{ ";
	for(auto x: a)
		os<<x<<" ";
	os<<"}";
	return os;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N=1e6+5;
const int oo=1e9+7;


/***************************** END OF TEMPLATE *******************************/
/***************************************************************************************
 *     Suffix Array Implementation O(nlog n)
 *     Definition : suffix(i) => substring [i,n-1]
 *     Input : STRING (inpStr) , sigma => Character Set Size
 Output:
 sa => ith smallest suffix of the string
 rak => rak[i] indicates the position of suffix(i) in the suffix array
 height => height[i] indicates the LCP of i-1 and i th suffix
 *     LCP of suffix(i) & suffix(j) = { L = rak[i], R = rak[j] ,  min(height[L+1, R]);}
 ***************************************************************************************/



const int maxn = 1e6+5;
int wa[maxn],wb[maxn],wv[maxn],wc[maxn];
int r[maxn],sa[maxn],rak[maxn], height[maxn],dp[maxn][22],jump[maxn], SIGMA = 0 ;

int cmp(int *r,int a,int b,int l){return r[a] == r[b] && r[a+l] == r[b+l];}
void da(int *r,int *sa,int n,int m)
{
    int i,j,p,*x=wa,*y=wb,*t;
    for( i=0;i<m;i++) wc[i]=0;
    for( i=0;i<n;i++) wc[x[i]=r[i]] ++;
    for( i=1;i<m;i++) wc[i] += wc[i-1];
    for( i= n-1;i>=0;i--)sa[--wc[x[i]]] = i;
    for( j= 1,p=1;p<n;j*=2,m=p){
        for(p=0,i=n-j;i<n;i++)y[p++] = i;
        for(i=0;i<n;i++)if(sa[i] >= j) y[p++] = sa[i] - j;
        for(i=0;i<n;i++)wv[i] = x[y[i]];
        for(i=0;i<m;i++) wc[i] = 0;
        for(i=0;i<n;i++) wc[wv[i]] ++;
        for(i=1;i<m;i++) wc[i] += wc[i-1];
        for(i=n-1;i>=0;i--) sa[--wc[wv[i]]] = y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]] = 0,i=1;i<n;i++) x[sa[i]]= cmp(y,sa[i-1],sa[i],j) ? p-1:p++;
    }
}
void calheight(int *r,int *sa,int n)
{
    int i,j,k=0;
    for(i=1;i<=n;i++) rak[sa[i]] = i;
    for(i=0;i<n;height[rak[i++]] = k ) {
        for(k?k--:0, j=sa[rak[i]-1] ; r[i+k] == r[j+k] ; k ++) ;
    }
}

void initRMQ(int n)
{
    for(int i= 0;i<=n;i++) dp[i][0] = height[i];
    for(int j= 1; (1<<j) <= n; j ++ ){
        for(int i = 0; i + (1<<j) - 1 <= n ; i ++ ) {
            dp[i][j] = min(dp[i][j-1] , dp[i + (1<<(j-1))][j-1]);
        }
    }
    for(int i = 1;i <= n;i ++ ) {
        int k = 0;
        while((1 << (k+1)) <= i) k++;
        jump[i] = k;
    }

}
int askRMQ(int L,int R)
{
    int k = jump[R-L+1];
    return min(dp[L][k], dp[R - (1<<k) + 1][k]);
}


//int main()
//{
//    scanf("%s",s);
//    int n = strlen(s);
//    for(int i = 0; i < n; i ++) {
//        r[i] = s[i]-'a' + 1;
//        SIGMA = max(SIGMA, r[i]);
//    }
//    r[n] = 0;
//    da(r,sa,n+1,SIGMA + 1); // don't forget SIGMA + 1. It will ruin you.
//    calheight(r,sa,n);
//}


int to[N];
int beg[N];
int cur[N];
int len[N];
ll qsum[N];
int nxt_s[N];

int32_t main()
{
    FastIO;

    int T;
    cin>>T;
    while(T--)
    {
        string s;
        cin>>s;
        int q;
        cin>>q;
        int tot = 0;
        auto add_char = [&](int val,int idx)
        {
            r[tot] = val;
            to[tot] = idx;
            tot++;
        };
        SIGMA = 26;
        len[0] = s.size();
        for(char c: s)
        {
            add_char(c-'a'+1,0);
        }
        add_char(++SIGMA,-1);
        for(int i=1;i<=q;i++)
        {
            string s;
            cin>>s;
            beg[i]=tot;
            len[i] = s.size();
            for(char c: s)
            {
                add_char(c-'a'+1,i);
            }
            add_char(++SIGMA,-1);
        }
        add_char(0,-1);
        tot--;

        da(r,sa,tot+1,SIGMA+1);
        calheight(r,sa,tot);
        initRMQ(tot+5);

        {
            nxt_s[tot+1] = tot+1;
            for(int i=tot;i>=0;i--)
            {
                if(to[sa[i]] == 0)
                    nxt_s[i] = i;
                else nxt_s[i] = nxt_s[i+1];
            }
        }
        // DBG(sa);
        // for(int i=0;i<=tot;i++)
        // {
        //     cerr<<sa[i]<<" ";
        // }
        // NL;
        // DBG(nxt_s);
        // for(int i=0;i<=tot;i++)
        // {
        //     cerr<<nxt_s[i]<<" ";
        // }
        // NL;

        {
            memset(qsum,0,sizeof(qsum[0]) * (tot+1));
            int suru = nxt_s[0];
            assert(to[sa[suru]] == 0);
            qsum[suru] = len[0] - sa[suru];
            int last = suru;

            for(int i=suru+1;i<=tot;i++)
            {
                qsum[i] = qsum[i-1];
                if(to[sa[i]] == 0)
                {
                    // DBG(len[0] - sa[i] - askRMQ(last+1,i));
                    qsum[i]+=len[0] - sa[i] - askRMQ(last+1,i);
                    last = i;
                }
            }
            // DBG(qsum[tot]);
        }
        // DBG(qsum);
        // for(int i=0;i<=tot;i++)
        // {
        //     cerr<<qsum[i]<<" ";
        // }
        // NL;

        for(int i=1;i<=q;i++)
        {

            auto solprefix = [&] (int idx,int ln) -> ll
            {
                int niche = idx;
                {
                    int lo = 0 , hi = idx, mid;
                    while(lo<hi)
                    {
                        mid = (lo+hi)/2;
                        if(askRMQ(mid+1,idx) >= ln)
                        {
                            hi = mid;
                        }
                        else lo = mid+1;
                    }
                    niche = hi;
                }
                int upore = idx;
                {
                    int lo = idx, hi = tot+1, mid;
                    while(lo<hi)
                    {
                        mid = (lo+hi+1)/2;
                        if(askRMQ(idx+1,mid) >= ln)
                            lo = mid;
                        else hi = mid-1;
                    }
                    upore = hi;
                }
                // DBG(niche);
                // DBG(upore);
                // NL;
                if(nxt_s[niche] > upore) return 0;
                niche = nxt_s[niche];
                ll ans = qsum[upore] - qsum[niche];
                ans+= len[0] - sa[niche] - ln+1;
                return ans;
            };

            int idx = rak[beg[i]];
            for(int j=1;j<=len[i];j++) cout<<solprefix(idx,j)<<" ";
            cout<<'\n';


        }
    }
}
