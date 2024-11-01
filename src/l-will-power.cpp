#include <bits/stdc++.h>

#define pb             push_back
#define int            long long
#define endl "\n" 
#define fill(x, y)     memset(x, y, sizeof(x))
#define all(x)         (x).begin(), (x).end()
#define debug(x)       { cerr << #x << " = " << x << endl; }
#define IO	       { ios_base::sync_with_stdio(false); cin.tie(0); }
#define read(x)	       freopen(x, "r", stdin)
#define write(x)       freopen(x, "w", stdout)

using namespace std;

typedef long long      ll;
typedef pair<int, int> ii;
typedef vector<int>    vi;

const ll mod = 1e9 + 7;

ll bigmod(ll a, ll m) {
    if (m == 0) return 1LL;
    else if (m & 1) {
        return (a * bigmod(a, m-1)) % mod;
    } else {
        ll r = bigmod(a, m/2);
        return  (r*r) % mod;
    }
}

ll modinv(ll a) {
    return bigmod(a, mod-2);
}

int divide(int p, int q) {
    return p * modinv(q) % mod;
}

ii find_wealth(int node, vector<ii> &parent, vi &wealth, vi &childs, vector<bool> &alive) {
    int par = parent[node].first;
    int mul = parent[node].second;
    if (alive[par]) return {par, mul};
    ii x = find_wealth(par, parent, wealth, childs, alive);
    wealth[node] = (wealth[node] + divide(mul, childs[par]) * wealth[par] % mod) % mod;
    x.second = x.second * divide(mul, childs[par]) % mod;
    parent[node] = x;
    return parent[node];
}

signed main() {
    IO;
    // read("in2.txt");
    // write("out2.txt");
    int t; cin >> t;
    for (int cs=1; cs <= t; cs++) {
        int q;
        cin >> q;

        vector<ii> parent(q+1);
        vector<int> wealth(q+1);
        vector<int> childs(q+1);
        childs[0] = 1;
        parent[1] = {0, 1}; // parent of 1 is 0
        vector<bool> alive(q+1, true);

        while(q--) {
            int type; cin >> type;
            if (type == 1) {
                int x; cin >> x;
                alive[x] = false;
            }
            else if (type == 2) {
                int x, y, p;
                cin >> x >> y >> p;
                parent[x] = {p, 1};
                wealth[x] = y;
                childs[p]++;
            } else {
                int x;
                cin >> x;
                find_wealth(x, parent, wealth, childs, alive);
                cout << wealth[x] << endl;
            }
        }
    }
}
