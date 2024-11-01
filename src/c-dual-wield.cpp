#include <bits/stdc++.h>
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt")
using namespace std;
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())
#define edl '\n'
#ifdef LOCAL
#include "../cp-template/Basic/debug.h"
#else
#define dbg1(args...)
#define dbg2(x)
#define stop
#endif
typedef long long LL;
typedef unsigned long long uLL;
// typedef __int128_t LLL;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;
typedef pair<LL, int> pli;
typedef pair<LL, LL> pll;
const int INF = 1e9;
const LL MOD = 998244353;
const int N = 5e5 + 5;
vector<pii> g[N];
int deg[N];
bool visv[N], vise[N];
bool dvisv[N];
bool dvise[N];
int A[N], B[N];
void dfs(int u)
{
    visv[u] = true;
    for(auto [v, i]: g[u]){
        if(vise[i]) continue;
        vise[i] = true;
        A[i] = u, B[i] = v;
        if(visv[v]) continue;

        dfs(v);
    }
}

int getLeafOrCycle(int u)
{
    dvisv[u] = true;
    for(auto [v, i]: g[u]){
        if(dvise[i]) continue;

        dvise[i] = true;
        if(dvisv[v]){
            return v;
        }
        
        int res = getLeafOrCycle(v);

        if(res != -1)
            return res;
    }

    if((int)g[u].size() == 1)
        return u;
    else
        return -1;
}

int getVariety(int C[], int n)
{
    set<int> s;
    for(int i = 0; i < n; i++)
        s.insert(C[i]);
    
    return (int)s.size();
}

void solve(int csno)
{
    int n;
    cin >> n;
    fill(g + 1, g + 2 * n, vector<pii>());
    fill(deg + 1, deg + 2 * n, 0);
    fill(visv + 1, visv + 2 * n, 0);
    fill(vise + 1, vise + 2 * n, 0);
    fill(dvisv + 1, dvisv + 2 * n, 0);
    fill(dvise + 1, dvise + 2 * n, 0);

    for(int i = 0; i < n; i++)
        cin >> A[i];
    
    for(int i = 0; i < n; i++)
        cin >> B[i];
    
    for(int i = 0; i < n; i++){
        if(A[i] == B[i]) continue;

        deg[A[i]]++;
        deg[B[i]]++;
        g[A[i]].emplace_back(B[i], i);
        g[B[i]].emplace_back(A[i], i);
    }

    for(int i = 1; i <= 2 * n; i++){
        if(visv[i]) continue;

        int v = getLeafOrCycle(i);
        dfs(v);
    }

    int variety = getVariety(A, n) + getVariety(B, n);

    cout << variety << edl;
    for(int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << edl;
    for(int i = 0; i < n; i++)
        cout << B[i] << " ";
    cout << edl;
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int csno = 1; csno <= T; csno++)
        solve(csno);
}
