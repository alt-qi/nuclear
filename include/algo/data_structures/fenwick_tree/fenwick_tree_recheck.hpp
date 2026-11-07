#ifdef NUCLEAR_TRD_EXAMPLE
#include <vector>
using std::vector;
using ll = long long;
#endif

/// &TRD_BEGIN
/// @author Не указан в исходном файле
/// @brief Дерево Фенвика RECHECK.
/// @date 2026-11-06
/// @note Дата переноса; код из приложенного файла без изменений.

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

// Пример использования
inline bool example_fenwick() {
    Fenwick f(4);
    f.add(1, 3); f.add(3, 5);  // индексы с единицы
    return f.sumRange(2, 4) == 5;  // обе границы включены
}
/// &TRD_END
