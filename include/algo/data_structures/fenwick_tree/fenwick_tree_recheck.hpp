#ifdef NUCLEAR_TRD_EXAMPLE
#include <vector>
using std::vector;
using ll = long long;
#endif

/// &TRD_BEGIN
/// @author unknown
struct Fenwick {
   int n;
   vector<ll> f;
   Fenwick() {}
   Fenwick(int n): n(n), f(n+1, 0) {}
   void add(int i, ll v){
       for(; i<=n; i+=i&-i) f[i]+=v;
   }
   ll sumPrefix(int i){
       ll r=0;
       for(; i>0; i-=i&-i) r+=f[i];
       return r;
   }
   ll sumRange(int l, int r){
       if(r<l) return 0;
       return sumPrefix(r)-sumPrefix(l-1);
   }
};
/// &TRD_END
