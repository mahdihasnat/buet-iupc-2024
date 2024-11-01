#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;
#define getbit(n, i) (((n) & (1LL << (i))) != 0) 
#define setbit0(n, i) ((n) & (~(1LL << (i)))) 
#define setbit1(n, i) ((n) | (1LL << (i))) 
#define togglebit(n, i) ((n) ^ (1LL << (i))) 
#define lastone(n) ((n) & (-(n))) 
char gap = 32;
#define int long long
#define ll long long 
#define lll __int128_t
#define pb push_back
typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll hashPrime = 1610612741;

int n, m;
// int dp[2001][2001][2];
// int a[2001][2001];
vector<vector<vector<int>>> dp;
vector<vector<int>> a;
int recurse(int r, int c, int tight) {
	if(tight == 2) return 0;
    if(r == n - 1 and c == m - 1) {
        if(tight == 2) {
            return 0;
        }
        else if(tight == 1) {
            return - r - c + a[r][c];
        }
        else {
            return a[r][c];
        }
    }
    if(dp[r][c][tight] != -1) return dp[r][c][tight];
    int ans = LONG_LONG_MIN;
    if(tight == 0) {
        if(r + 1 < n) ans = max(ans, recurse(r + 1, c, 0));
        if(c + 1 < m) ans = max(ans, recurse(r, c + 1, 0));
        if(r + 1 < n) ans = max(ans, recurse(r + 1, c, 1) + a[r][c] + r + c);
        if(c + 1 < m) ans = max(ans, recurse(r, c + 1, 1) + a[r][c] + r + c);
        return dp[r][c][tight] = ans;
    }
    else if(tight == 1) {
        if(r + 1 < n) ans = max({ans, recurse(r + 1, c, 1), recurse(r + 1, c, 1) + a[r][c], recurse(r + 1, c, 2) + a[r][c] - r - c});
        if(c + 1 < m) ans = max({ans, recurse(r, c + 1, 1), recurse(r, c + 1, 1) + a[r][c], recurse(r, c + 1, 2) + a[r][c] - r - c});
        return dp[r][c][tight] = ans;
    }
    else {
        return dp[r][c][tight] = 0;
    }

}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t; cin >> t;
    while(t--) {
        cin >> n >> m;
		a.assign(n, vector<int>(m));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cin >> a[i][j];
            }
        }
        dp.assign(n, vector<vector<int>>(m, vector<int>(2, -1)));
        //memset(dp, -1, sizeof(dp));
        cout << recurse(0, 0, 0) << '\n';
    }
    return 0;
}
