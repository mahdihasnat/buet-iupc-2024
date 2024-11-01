#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
const int K = 31, A = 1 << K;

vector<int> adj[N];
int val[N];
int color[N];
int dfs(int ind, int c){
	color[ind] = c;
	for(auto x : adj[ind]){
		if(color[x] == -1 && !dfs(x, c ^ 1))
			return 0;
		if(color[x] == color[ind])
			return 0;
	}
	return 1;
}

struct basis{
	int bs[K];
	int sz;
	basis(){
		sz = 0;
		memset(bs, 0, sizeof bs);
	}
	void add(int x){
		for(int i = K - 1; i >= 0; --i){
			if(x >> i & 1){
				if(bs[i] == 0)bs[i] = x, ++sz;
				x ^= bs[i];
			}
		}
	}
	int get(int x = 0){
		int ans = x;
		for(int i = K - 1; i >= 0; --i){
			if(ans >> i & 1)continue;
			ans ^= bs[i];
		}
		return ans;
	}
};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; ++i){
		cin >> val[i];
		color[i] = -1;
	}
	
	
	for(int j = 0; j < m; ++j){
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	if(n == 1){
		cout << val[1] << "\n";
		return 0;
	}
	auto getVal = [&](){
		basis b;
		for(int i = 1; i <= n; ++i)b.add(val[i]);
		return b.get();
	};
	if(dfs(1, 0)){
		basis B[2];
		for(int i = 1; i <= n; ++i)B[color[i]].add(val[i]);
		if(B[0].sz + B[1].sz == n){
			int ans = 0;
			for(int i = 1; i <= n; ++i){
				for(auto x : adj[i]){
					int a = val[i], b = val[x];
					int c = a ^ b;
					val[i] = val[x] = c;
					ans = max(ans, getVal());
					val[i] = a, val[x] = b;
				}
			}
			long long result = (long long)ans * n;
			result = max(result, accumulate(val + 1, val + n + 1, 0LL));
			cout << result << "\n";
			return 0;
		}
	}
	cout << (long long)getVal() * n << "\n";
	
	return 0;
}
