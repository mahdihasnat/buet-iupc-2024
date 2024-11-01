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

int solve(vector<vi> &freq, vector<vi> &occur, int n, int k) {
    
    int start = 0;
    vi cur(26);
    int ans = 0;
    while(start < n) {
        bool pos = false;
        for (int i=0; i<26; i++) 
            if (freq[n-1][i] - cur[i] >= k) pos = true;
        if (!pos) break;

        int low = n + 1;

        for (int i=0; i<26; i++) {
            low = min(low, occur[i][ cur[i] + k ]);
        }
        

        ans += k;
        start = low + 1;
        cur = freq[low];
    }
    
    return ans;
}

signed main() {
    IO;

    int t; cin >> t;
    for (int cs=1; cs <= t; cs++) {
        string s;
        cin >> s;
        int p;
        cin >> p;

        int n = s.size(); 
        vector<vi> freq(n, vi(26));

        vector<vi> occur_pos(26, vi(n+1, n+1));

        freq[0][s[0] - 'A']++;
        occur_pos[s[0] - 'A'][ freq[0][s[0] - 'A'] ] = 0;
        for (int i=1; i<n; i++) {
            freq[i] = freq[i-1];
            freq[i][s[i] - 'A']++;
            occur_pos[s[i] - 'A'][ freq[i][s[i] - 'A'] ] = i;
        }

        int ans = 0;
        for (int k=p; k<=n; k++) {
            ans = max(ans, solve(freq, occur_pos, n, k));
        }
        cout << ans << endl;
    }
}
