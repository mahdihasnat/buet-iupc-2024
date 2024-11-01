#include <bits/stdc++.h>
using namespace std;

void solve(int cs) {
    int n;
    cin >> n;
    vector<int> d(n);
    int x = 0;
    int mn = INT_MAX, mx = 0;
    for (auto &e: d){
        cin >> e;
        x ^= e;
        mn = min(mn, e);
        mx = max(mx, e);
    }
    string s;
    cin >> s;
    if (s == "BOB") {
        int rest = x ^ mx;
        if (rest >= mx) {
            cout << "ALICE\n";
            return;
        }
        for(int i = 0; i < n; ++i) {
            if (d[i] == mx) {
                d[i] = rest;
                if (rest == 0) {
                    swap(d[i], d.back());
                    d.pop_back();
                }
                break; 
            }
        }
        n = d.size();
    }
    if(n == 0){
        cout << "BOB\n";
        return;
    }
    mn = INT_MAX;
    mx = 0;
    x = 0;
    for(auto &e: d){
        mn = min(mn, e);
        mx = max(mx, e);
        x ^= e; 
    }
    if (x) {
        cout << "ALICE\n";
        return;
    }
    if (n == 2 || (mx == mn && mx == 1) ) {
        cout << "BOB\n";
        return;
    }
    cout << "ALICE\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        solve( i + 1 );
    }
}
