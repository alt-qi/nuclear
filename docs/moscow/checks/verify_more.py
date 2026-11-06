import itertools,random,math
from collections import deque
from verify_derived import socks_pair

def flow_value(n,m,edges):
    N=n+m+2;s=N-2;t=N-1;g=[{} for _ in range(N)]
    def add(u,v,c):g[u][v]=g[u].get(v,0)+c;g[v].setdefault(u,0)
    for u in range(n):add(s,u,1)
    for v in range(m):add(n+v,t,1)
    for u,v in edges:add(u,n+v,1);add(n+v,u,1)
    ans=0
    while True:
        p={s:None};q=deque([s])
        while q and t not in p:
            u=q.popleft()
            for v,c in g[u].items():
                if c and v not in p:p[v]=u;q.append(v)
        if t not in p:return ans
        v=t
        while v!=s:u=p[v];g[u][v]-=1;g[v][u]+=1;v=u
        ans+=1

def verify_ads():
    count=0
    for n,m in [(1,3),(2,2),(2,3),(3,3)]:
        all_e=list(itertools.product(range(n),range(m)))
        for emask in range(1<<len(all_e)):
            edges=[e for i,e in enumerate(all_e) if emask>>i&1]
            opt=0
            for lab in itertools.product([-1,0,1],repeat=len(edges)):
                a=[0]*n;b=[0]*m
                for z,(u,v) in zip(lab,edges):a[u]+=z;b[v]+=z
                if max(map(abs,a+b),default=0)<=1:opt=max(opt,sum(lab))
            assert flow_value(n,m,edges)==opt,(n,m,edges,opt)
            count+=1
    print('2018 B:',count,'graphs match exhaustive -1/0/1 edge labels')

def toll_dp(seq,a,b):
    dp=[0,math.inf,math.inf,math.inf] # none,E,T,TE
    for i,c in enumerate(seq):
        if i:dp[0]=min(dp[0],min(dp)+b)
        nd=[v+a for v in dp]
        target=1 if c=='E' else 2
        nd[target]=min(nd[target],dp[0])
        if c=='E':nd[3]=min(nd[3],dp[2])
        dp=nd
    return min(dp)

def toll_brute(seq,a,b):
    n=len(seq);best=n*a
    trips=[(i,j) for i in range(n) for j in range(i+1,n) if seq[i]=='E' and seq[j]=='T']
    for mask in range(1<<(2*n-1)):
        cost=a*(mask&((1<<n)-1)).bit_count()+b*(mask>>n).bit_count()
        if cost>=best:continue
        seen=set();ok=True
        for i,j in trips:
            obs=tuple([x for x in [i,j] if mask>>x&1]+[n+k for k in range(i,j) if mask>>(n+k)&1])
            if not obs or obs in seen:ok=False;break
            seen.add(obs)
        if ok:best=cost
    return best

def verify_toll():
    count=0
    for n in range(2,8):
        for mid in itertools.product('ET',repeat=n-2):
            seq='E'+''.join(mid)+'T'
            for a,b in [(1,1),(2,1),(1,3),(4,5)]:
                assert toll_dp(seq,a,b)==toll_brute(seq,a,b),(seq,a,b)
                count+=1
    print('2019 F:',count,'instances match enumeration of every gate set')

def rebels_brute(s):
    n=len(s)
    # Arbitrarily many subsequences, encoded as subset-cover DP.
    bad=[]
    for mask in range(1,1<<n):
        cur=0;mn=0
        for i,c in enumerate(s):
            if mask>>i&1:cur+=1 if c=='(' else -1;mn=min(mn,cur)
        if cur==0 and mn<0:bad.append(mask)
    dp={0}
    for mask in range(1,1<<n):
        for b in bad:
            if b&mask==b and mask^b in dp:dp.add(mask);break
    return (1<<n)-1 in dp

def verify_rebels():
    count=0
    for half in range(1,6):
        n=2*half
        for os in itertools.combinations(range(n),half):
            o=set(os);s=''.join('(' if i in o else ')' for i in range(n))
            h=0;valid=True
            for c in s:
                h+=1 if c=='(' else -1
                if h<0:valid=False;break
            if not valid:continue
            f=s.index(')')+(n-1-s.rindex('('))<=half-2
            assert f==rebels_brute(s),s
            count+=1
    print('2019 H:',count,'balanced strings match arbitrary subset partitions')

def matrix_reduce(M):
    p,q,r,s=M
    if p*s-q*r!=1 or q%2 or r%2 or p%4!=1 or s%4!=1:return False
    while q:
        if abs(p)>abs(q):
            # nearest integer p/(2q), exact rational rounding, no float
            k=(p+q)//(2*q)
            p,r=p-2*k*q,r-2*k*s
        else:
            k=(q+p)//(2*p)
            q,s=q-2*k*p,s-2*k*r
        assert max(map(abs,[p,q,r,s]))<=1000100,(M,p,q,r,s)
    assert p==s==1
    return True

def verify_matrix():
    rng=random.Random(2020)
    for _ in range(10000):
        p,q,r,s=1,0,0,1
        for j in range(12):
            k=rng.randrange(-3,4)
            if rng.randrange(2):u,v=p+2*k*q,r+2*k*s;z=(u,q,v,s)
            else:u,v=q+2*k*p,s+2*k*r;z=(p,u,r,v)
            if max(map(abs,z))<=1000000:p,q,r,s=z
        assert matrix_reduce((p,q,r,s))
    print('2020 M: 10000 generated group matrices reduce to identity within bound')

if __name__=='__main__':
    verify_ads();verify_toll();verify_rebels();verify_matrix()
    assert abs(float(21+socks_pair(3,2)*2+socks_pair(2,2))-29.571428571)<1e-8
    print('2021 C: all four statement samples agree')
