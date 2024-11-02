#include <bits/stdc++.h>
using namespace std;
#define MAX 200005
#define MOD 998244353
#define BASE 30
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define DBG(a) cerr << "line " << __LINE__ << " : " << #a << " --> " << (a) << endl

typedef long long ll;
typedef pair<ll,ll> pt;
typedef pair<pair<ll,ll>,ll> line;
vector<pair<ll,ll>> polygon;
vector<pair<pair<ll,ll>,ll>> sides;

typedef long double ftype;
const ftype EPS = 1E-11;


ll dSqr(pair<ll,ll> p, pair<ll,ll> q)
{
    ll ans = (p.first-q.first)*(p.first-q.first) + (p.second - q.second)*(p.second - q.second);
    return ans;
}

line getBisector(pt pa, pt pb)
{
    ll a = (pa.first-pb.first);
    ll b = (pa.second-pb.second);
    ll c = a*(pa.first+pb.first) + b*(pa.second+pb.second);
    ll g = __gcd(abs(a),abs(b));
    a = a*2;
    b = b*2;
    g = __gcd(g, abs(c));
    a = a/g;
    b = b/g;
    c = c/g;
    if(a<0 || (a==0 && b<0))
    {
        a = -a;
        b = -b;
        c = -c;
    }

    return {{a,b},c};
}

ftype findCoordinate(line side, line perpend, bool isY)
{
    if(isY)
    {
        swap(side.first.first,side.first.second);
        swap(perpend.first.first, perpend.first.second);
    }

    ftype ans = side.second*perpend.first.second - perpend.second*side.first.second;
    ans = ans / (side.first.first*perpend.first.second - perpend.first.first*side.first.second);
    return ans;
}

ftype semi_integration(line l, pt farthest, ftype xl, ftype xh, bool isY)
{
    if(isY)
    {
        swap(l.first.first,l.first.second);
        swap(farthest.first,farthest.second);
    }

//    printf("%lld x + %lld y = %lld\n",l.first.first, l.first.second, l.second);
    ftype y0_2 = farthest.second*farthest.second;

    ftype a0_2 = l.second;
    a0_2 = a0_2/l.first.second;
    a0_2 = a0_2*a0_2;

    ftype x0 = farthest.first;

    ftype a0y02 = farthest.second*l.second*2;
    a0y02 = a0y02/l.first.second;

    ftype term1 = (xh - xl)*(y0_2 + a0_2 + x0*x0 - a0y02);

    ftype a0a1 = -l.second*l.first.first;
    a0a1 = a0a1/(l.first.second*l.first.second);

    ftype a1y0 = -l.first.first*farthest.second;
    a1y0 = a1y0/l.first.second;

    ftype term2 = (xh*xh - xl*xl)*(a0a1 - a1y0 - x0);

    ftype multiplier = l.first.first*l.first.first + l.first.second*l.first.second;
    ll den = l.first.second*l.first.second*3;
    multiplier = multiplier/den;
    ftype term3 = (xh*xh*xh - xl*xl*xl)*multiplier;

    return (term1 + term2 + term3);
}

ftype solve()
{
    int n = polygon.size();
//    vector<int> fidx;
//
//    for(int i=0, j=1; i<n; i++)
//    {
//        while(dSqr(polygon[i],polygon[j])<=dSqr(polygon[i],polygon[(j+1)%n]))
//            j = (j+1)%n;
//        fidx.push_back(j);
//    }
    vector<int> fidx(n);
    for(int i=0; i<n; i++){
        double dur = 0;
        for(int j=0; j<n; j++){
            double d =  dSqr( polygon[i], polygon[j] );
            if (d > dur) fidx[i] = j, dur = d;
        }
    }

//    for(int i=0; i<n; i++){
//        cout<<"farthest of"<< i<< " => " <<fidx[i]<<endl;
//    }

    ftype ans = 0;
    for(int i=0; i<n; i++)
    {
        bool isY = abs(polygon[i].first-polygon[(i+1)%n].first)<abs(polygon[i].second-polygon[(i+1)%n].second);

        ftype lo = isY? polygon[i].second : polygon[i].first;
        ftype last = isY? polygon[(i+1)%n].second : polygon[(i+1)%n].first;
        ftype diff = last-lo;
        line currLine = sides[i];

        vector<pair<int,ftype>> boundaries;
        int next_idx = fidx[(i+1)%n];

        for(int j = fidx[i]; j != next_idx; j = (j+1)%n)
        {
            ftype coordinate;
            int curr = (j+1)%n;
            int last = j;
            bool firstCal = true;
            do
            {
                if(!firstCal)
                {
                    last = boundaries.back().first;
                    boundaries.pop_back();
                }
                line intersector = getBisector(polygon[last],polygon[curr]);
                coordinate = findCoordinate(currLine, intersector, isY);
                firstCal = false;
            } while((!boundaries.empty())&&((diff>0&&coordinate<boundaries.back().second)||
                                            (diff<0&&coordinate>boundaries.back().second)));

            boundaries.push_back({last,coordinate});
        }
        boundaries.push_back({next_idx,last});

        ftype curr = 0;
//        printf("(i=%d, isY=%d)\n",i,isY);

        for(int j=0;j<boundaries.size();j++)
        {
            ftype l = (j==0) ? lo : boundaries[j-1].second;
            int idx = boundaries[j].first;
//            printf("Point %d is farthest for %f to %f\n",idx,(double) l, (double) boundaries[j].second);
            curr = curr + semi_integration(currLine, polygon[idx], l, boundaries[j].second, isY);
        }
//        printf("curr=%f\n",(double) curr);
        curr = curr/diff;
        curr = curr*sqrtl(dSqr(polygon[i],polygon[(i+1)%n]));
        ans = ans + curr;
//        printf("ans=%f\n",(double) ans);
    }
    return ans;
}

int main()
{
    int T;
    scanf("%d",&T);
    for(int t=0; t<T; t++)
    {

        int n;
        scanf("%d",&n);

        polygon.clear();
        sides.clear();

        for(int i=0; i<n; i++)
        {
            pair<ll,ll> p;
            scanf("%lld %lld",&p.first, &p.second);
            polygon.push_back(p);
        }

        for(int i=0; i<n; i++)
        {
            ll A = (polygon[i].second-polygon[(i+1)%n].second);
            ll B = -(polygon[i].first-polygon[(i+1)%n].first);
            ll C = A*polygon[i].first + B*polygon[i].second;
            ll g = __gcd(abs(A),abs(B));
            g = __gcd(g,abs(C));
            A = A/g;
            B = B/g;
            C = C/g;
            if(A<0 || (A==0&&B<0))
            {
                A = -A;
                B = -B;
                C = -C;
            }
            sides.push_back({{A,B},C});
        }

        ftype ans = solve();
        cout<<fixed<<setprecision(8)<<ans<<"\n";
    }
    return 0;
}
