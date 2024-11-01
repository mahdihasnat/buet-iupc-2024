#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#ifdef LOKAL
#include "DEBUG_TEMPLATE.h"
#else
#define HERE
#define debug(args...)
#endif
typedef pair<int,int> pii;
#define ALL(x) x.begin(),x.end()

const int N = 3e5 +5;
const int oo = 1e9+7;

int total_qn=0;
bool empty_out=0;
bool ask(string const &s)
{
    total_qn+=1;
    assert(total_qn <= 1024);
    cout<<s<<endl;
	if(s=="") empty_out=1;
    string t;
    cin>>t;
    if(t=="Correct")
	{
		if(empty_out)
			assert(0);
        exit(0);

	}
    if(t=="Yes")
        return 1;
    else if(t=="No")
        return 0;
    else
    {
        // assert(0);
        // while(1);
    }
}


int number_of_zero(int n)
{
    int lo = 0, hi = n;
    while(lo<hi)
    {
        int mid = (lo+hi+1)/2;
        if(ask(string(mid,'0')))
            lo=mid;
        else
            hi = mid-1;
    }
    return lo;
}

void solve()
{
    int n;
    cin>>n;
    int total_zero = number_of_zero(n);
    string pre = "";
    for(int i=0;i<total_zero;i++)
    {
        while(1)
        {
            pre+="1";
            if(ask(pre + string(total_zero-i, '0')))
            {
                continue;
            }
            else
            {
                pre.pop_back();
                break;
            }
        }
        pre+="0";
    }
    pre+=string(n-pre.size(), '1');
    ask(pre);
    assert(0);
}
/*

*/

int32_t main()
{
#ifndef LOKAL
    // ios_base::sync_with_stdio(false);
    // cin.tie(nullptr);
#endif
    int T=1;
    // cin>>T;
    while(T--)
    {
        solve();
    }
    return 0;
}