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

const int N=2e5+5;
const int oo=1e9+7;



const int ALPHA = 26;
int len[N], link[N], nxt[N][ALPHA];
int sz;
int last;
bool vis[N];

void sa_init() {
    memset(nxt, -1, sizeof nxt);
	memset(vis, 0, sizeof vis);
    len[0] = 0;
    link[0] = -1;
    sz = 1;
    last = 0;
}

void add(char ch) {
    int c = ch-'a';

    int cur = sz++;                             //create new node
    len[cur] = len[last]+1;

    int u = last;
    while (u != -1 && nxt[u][c] == -1) {
        nxt[u][c] = cur;
        u = link[u];
    }

    if (u == -1) {
        link[cur] = 0;
    }
    else {
        int v = nxt[u][c];
        if (len[v] == len[u]+1) {
            link[cur] = v;
        }
        else {
            int clone = sz++;                   //create node by cloning
            len[clone] = 1 + len[u];
            link[clone] = link[v];

            for (int i=0; i<ALPHA; i++)
                nxt[clone][i] = nxt[v][i];

            while (u != -1 && nxt[u][c] == v) {
                nxt[u][c] = clone;
                u = link[u];
            }

            link[v] = link[cur] = clone;
        }
    }
    last = cur;
}

ll ans[N];
void dfs(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    ans[u] = 1;
    for(int i=0; i<ALPHA; i++){
        if (nxt[u][i] == -1)    continue;
        dfs(nxt[u][i]);
        ans[u] += ans[nxt[u][i]];
    }
}




int32_t main()
{
    FastIO;
	// freopen("input.txt","r",stdin);
    int T,cs=0;
    cin>>T;
    while(T--)
    {
		sa_init();
		string s;
		cin>>s;
		// DBG(s.size());
		for(char c: s)
			add(c);
		// DBG(sz);
		dfs(0);
		int q;
		cin>>q;
		// DBG(q);
		while(q--)
		{
			string t;
			cin>>t;
			int u = 0;
			int tot = 0;
			for(char c: t)
			{
				tot++;
				// DBG(tot);
				if(u!=-1)
					u=nxt[u][c-'a'];
				if(u==-1)
				{
					cout<<"0 ";
				}
				else
				{
					cout<<ans[u]<<" ";
				}
			}
			cout<<"\n";
		}
    }
}
