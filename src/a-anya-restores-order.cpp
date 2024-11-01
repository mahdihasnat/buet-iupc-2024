#include<bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL); cout.tie(NULL);
#define endl '\n'


struct Tube{
    bool active = true;
    set<int> st;
    int mex;
};

Tube* tube[100005];


void solve() {
    int n,q;
    cin>>n>>q;

    for(int i=1;i<=n;i++){
        tube[i] = new Tube();
    }

    for(int i=1;i<=n;i++){
        int m;
        cin>>m;
        for(int j=0;j<m;j++){
            int a;
            cin>>a;
            tube[i]->st.insert(a);
        }
        tube[i]->mex = 1;
        while(!tube[i]->st.empty() and *tube[i]->st.begin() == tube[i]->mex ){
            tube[i]->st.erase(tube[i]->st.begin());
            tube[i]->mex++;
        }
    }
    while(q--) {
        int t;
        cin>>t;
        if( t == 1 ) {
            int to,from;
            cin>>to>>from;
            if( tube[from]->st.size() > tube[to]->st.size() )
                swap(tube[from],tube[to]);
            assert(tube[to]->active);
            assert(tube[from]->active);

            tube[to]->mex = max(tube[to]->mex,tube[from]->mex);
            for(auto s:tube[from]->st) tube[to]->st.insert(s);

            tube[from]->st.clear();
            tube[from]->active = false;

            while(!tube[to]->st.empty() and *tube[to]->st.begin() < tube[to]->mex ){
                tube[to]->st.erase(tube[to]->st.begin());
            }

            while(!tube[to]->st.empty() and *tube[to]->st.begin() == tube[to]->mex ){
                tube[to]->st.erase(tube[to]->st.begin());
                tube[to]->mex++;
            }

        }else{
            int x;
            cin>>x;
            assert(tube[x]->active);
            if( tube[x]->st.empty() ) cout<<"complete"<<endl;
            else cout<<tube[x]->mex<<endl;;
        }
    }

    for(int i=1;i<=n;i++){
        delete(tube[i]);
    }

}

signed main() {
    FASTIO;
    int tc=1;
    cin>>tc;
    while(tc--) solve();
}
