import itertools,random,math
from collections import deque

def edge_color(n,edges):
    adj=[[] for _ in range(n)]
    for i,(u,v) in enumerate(edges):adj[u].append(i);adj[v].append(i)
    if any(len(a)<2 for a in adj):return None
    seen=set();answer=[None]*len(edges)
    for root in range(n):
        if root in seen:continue
        vs=[];es=set();q=[root];seen.add(root)
        while q:
            u=q.pop();vs.append(u)
            for e in adj[u]:
                es.add(e);a,b=edges[e];v=a^b^u
                if v not in seen:seen.add(v);q.append(v)
        odd=[v for v in vs if len(adj[v])%2]
        if not odd and len(es)%2 and all(len(adj[v])==2 for v in vs):return None
        local=[edges[e] for e in es];ids=list(es)
        if odd:
            dummy=n;start=dummy
            for v in odd:local.append((v,dummy));ids.append(None)
        else:start=next((v for v in vs if len(adj[v])>=4),root)
        g=[[] for _ in range(n+1)]
        for i,(u,v) in enumerate(local):g[u].append((v,i));g[v].append((u,i))
        used=set();stack=[(start,None)];order=[]
        while stack:
            u,e=stack[-1]
            while g[u] and g[u][-1][1] in used:g[u].pop()
            if g[u]:
                v,z=g[u].pop();used.add(z);stack.append((v,z))
            else:
                stack.pop()
                if e is not None:order.append(e)
        order.reverse()
        for k,e in enumerate(order):
            if ids[e] is not None:answer[ids[e]]=k%2
    return answer

def verify_colors():
    rng=random.Random(18)
    for _ in range(10000):
        n=rng.randrange(1,6);m=rng.randrange(0,10)
        edges=[(rng.randrange(n),rng.randrange(n)) for _ in range(m)]
        got=edge_color(n,edges)
        possible=False
        for mask in range(1<<m):
            colors=[set() for _ in range(n)]
            for i,(u,v) in enumerate(edges):colors[u].add(mask>>i&1);colors[v].add(mask>>i&1)
            if all(len(c)==2 for c in colors):possible=True;break
        assert (got is not None)==possible,(n,edges,got)
        if got is not None:
            colors=[set() for _ in range(n)]
            for c,(u,v) in zip(got,edges):colors[u].add(c);colors[v].add(c)
            assert all(len(c)==2 for c in colors)
    print('2018 K: 10000 multigraphs including loops match exhaustive colorings')

def chip_check(a,b):
    n=len(a)
    if sum(a)!=sum(b):return False
    k=[0]*n
    for i in range(n):
        if a[i]>b[i]:
            if (a[i]-b[i])%2:return False
            k[i]=(a[i]-b[i])//2
    if any(k[i] and k[(i+1)%n] for i in range(n)):return False
    if any(b[i]!=a[i]-2*k[i]+k[(i-1)%n]+k[(i+1)%n] for i in range(n)):return False
    for j in range(n):
        donors=[i for i in [(j-1)%n,(j+1)%n] if k[i]]
        donors.sort(key=lambda i:(b[i],i))
        h=a[j]
        for i in donors:
            if h+k[i]-1>b[i]:return False
            h+=k[i]
    return True

def reachable(a):
    n=len(a);seen={a};q=[a]
    while q:
        x=q.pop()
        for i in range(n):
            p=(i-1)%n;r=(i+1)%n
            if x[i]>=x[p]+2 and x[i]>=x[r]+2:
                y=list(x);y[i]-=2;y[p]+=1;y[r]+=1;y=tuple(y)
                if y not in seen:seen.add(y);q.append(y)
    return seen

def compositions(s,n):
    if n==1:yield(s,);return
    for x in range(s+1):
        for z in compositions(s-x,n-1):yield(x,)+z

def verify_chips():
    rng=random.Random(20);count=0
    for n in range(3,6):
        for z in range(100):
            a=tuple(rng.randrange(4) for _ in range(n));seen=reachable(a)
            for b in compositions(sum(a),n):
                assert chip_check(a,b)==(b in seen),(a,b,chip_check(a,b),seen)
                count+=1
    print('2020 F:',count,'target distributions match exhaustive legal operation graphs')

def pi(s):
    p=[0]*len(s)
    for i in range(1,len(s)):
        j=p[i-1]
        while j and s[i]!=s[j]:j=p[j-1]
        if s[i]==s[j]:j+=1
        p[i]=j
    return p

def step(pat,p,j,c):
    if j==len(pat):j=p[j-1]
    while j and pat[j]!=c:j=p[j-1]
    if pat[j]==c:j+=1
    return j

def demolition(s,p,ds):
    m=len(p);f=pi(p);rp=p[::-1];rf=pi(rp);r=[0]*(len(s)+1)
    for i in range(len(s)-1,-1,-1):r[i]=step(rp,rf,r[i+1],s[i])
    j=0;answer=0
    for c in s:
        j=step(p,f,j,c)
        answer+=j==m
    dead=set(ds);j=0
    for i,c in enumerate(s):
        if i in dead:
            L=set();u=j
            while u:L.add(u);u=f[u-1]
            R=set();u=r[i+1]
            while u:R.add(u);u=rf[u-1]
            answer+=sum(k in L and m-k in R for k in range(1,m))
        else:j=step(p,f,j,c)
    return answer

def verify_demolition():
    rng=random.Random(16)
    for _ in range(15000):
        n=rng.randrange(1,11);s=''.join(rng.choice('ab') for _ in range(n))
        p=''.join(rng.choice('ab') for _ in range(rng.randrange(1,n+2)))
        ds=sorted(rng.sample(range(n),rng.randrange(n+1)));alive=list(range(n));subsets=set()
        for z in [None]+ds:
            if z is not None:alive.remove(z)
            for i in range(len(alive)-len(p)+1):
                group=alive[i:i+len(p)]
                if ''.join(s[x] for x in group)==p:subsets.add(tuple(group))
        assert demolition(s,p,ds)==len(subsets),(s,p,ds,len(subsets),demolition(s,p,ds))
    print('2016 D: 15000 cases match explicit unique subsets across all demolition times')

def digit_table():
    ans={i:str(i) for i in range(1,10)}
    for mask in range(1,1024):
        digits=[i for i in range(10) if mask>>i&1]
        if len(digits)<2:continue
        g=0
        for d in digits:g=math.gcd(g,d-digits[0])
        if g<=1:continue
        M=9*g;full=(1<<len(digits))-1
        q=deque();seen=set()
        for i,d in enumerate(digits):
            if d:
                state=(1<<i,d%M);seen.add(state);q.append((*state,str(d)))
        while q:
            used,r,z=q.popleft()
            if used==full:
                G=math.gcd(r,M)
                if G not in ans or (len(z),z)<(len(ans[G]),ans[G]):ans[G]=z
            for i,d in enumerate(digits):
                state=(used|1<<i,(10*r+d)%M)
                if state not in seen:seen.add(state);q.append((*state,z+str(d)))
    return ans

def verify_digits():
    ans=digit_table();brute={}
    for z in range(1,100001):
        ds=list(map(int,str(z)));g=0
        for d in ds:g=math.gcd(g,d-ds[0])
        G=z if not g else math.gcd(z,9*g)
        brute.setdefault(G,z)
        if z<=300:
            real=0
            for perm in set(itertools.permutations(str(z))):real=math.gcd(real,int(''.join(perm)))
            assert real==G,(z,G,real)
    for G,z in brute.items():
        expected=str(G) if len(set(str(G)))==1 else ans.get(G)
        assert expected==str(z),(G,z,expected)
    print('2021 E: gcd formula checked by permutations up to 300; minima agree through 100000')
    print('2021 E nontrivial finite table:',{G:z for G,z in sorted(ans.items()) if G>9})

if __name__=='__main__':
    verify_colors();verify_chips();verify_demolition();verify_digits()
