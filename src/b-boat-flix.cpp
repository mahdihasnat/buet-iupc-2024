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
#define double long double

using namespace std;

typedef long long      ll;
typedef pair<int, int> ii;
typedef vector<int>    vi;


signed main() {
    IO;

    cout << fixed << setprecision(12);
    int t; cin >> t;
    for (int cs=1; cs <= t; cs++) {
        double n, k, d, x, y;
        cin >> n >> k >> d >> x >> y;
        if (y <= x) {
            cout << (d/x) << endl;
        } 
        else if (k >= n) {
            cout << (d/y) << endl;
        } else {
            double ans = d / x;
            double p = (1 / y) - (1 / x);
            ans += k * d * p / n;
            cout << ans << endl;
        }
    }
}
