"""Independent small-instance checks for reconstructed solutions. No downloaded code runs."""
import itertools, math, random
from collections import deque
from fractions import Fraction

def circle(bags):
    ans=[]
    for b in bags:
        ans.append(ans[-1] if ans and ans[-1] in b else min(b))
    last=ans[-1]
    for i,b in enumerate(bags):
        if last not in b: break
        ans[i]=last
    return ans

def verify_circle():
    sets=[set(x for x in range(3) if mask>>x&1) for mask in range(1,8)]
    count=0
    for n in range(2,7):
        for bags in itertools.product(sets,repeat=n):
            x=circle(bags)
            assert all(x[i-1] not in bags[i] or x[i-1]==x[i] for i in range(n)),(bags,x)
            count+=1
    print('2021 D:',count,'exhaustive cyclic bag collections passed')

def judge_greedy(d,owners,a,b,k):
    cap=[k]*len(a)
    for i in sorted(range(len(d)),key=lambda i:-d[i]):
        o=owners[i]
        if cap[o] and b[o]>=d[i]: cap[o]-=1;continue
        cand=next((j for j in range(len(a)) if cap[j] and a[j]>=d[i]),None)
        if cand is None:return False
        cap[cand]-=1
    return True

def judge_brute(d,owners,a,b,k):
    caps=[k]*len(a)
    def dfs(i):
        if i==len(d):return True
        for j in range(len(a)):
            if caps[j] and (b[j] if owners[i]==j else a[j])>=d[i]:
                caps[j]-=1
                if dfs(i+1):return True
                caps[j]+=1
        return False
    return dfs(0)

def verify_judge():
    rng=random.Random(104)
    for _ in range(20000):
        n=rng.randrange(1,9);m=rng.randrange(1,5)
        a=[rng.randrange(1,5) for _ in range(m)]
        b=[rng.randrange(x,6) for x in a]
        d=[rng.randrange(1,7) for _ in range(n)]
        o=[rng.randrange(m) for _ in range(n)]
        k=rng.randrange(1,4)
        assert judge_greedy(d,o,a,b,k)==judge_brute(d,o,a,b,k),(d,o,a,b,k)
    print('2018 J: 20000 random cases match exhaustive assignment')

def bad(points,l):
    if not points:return True
    s=sorted(points)
    return max([s[i+1]-s[i] for i in range(len(s)-1)]+[s[0]+l-s[-1]])*2>l

def go_formula(xs,l):
    n=len(xs);x=sorted(xs);x+= [z+l for z in x]
    r=[];j=0
    for i in range(2*n):
        j=max(j,i)
        while j+1<2*n and (x[j+1]-x[i])*2<l:j+=1
        r.append(j)
    one=1+sum(2**(r[i]-i) for i in range(n))
    overlap=0
    for i in range(n):
        for j in range(i+1,r[i]+1):
            if r[j]>=i+n-1:overlap+=2**(r[i]-j)
    dia=sum(1 for i in range(n) for j in range(i+1,i+n) if (x[j]-x[i])*2==l)
    both=2*int(any(r[i]==i+n-1 for i in range(n)))+2*overlap+dia
    return 2**n-2*one+both

def verify_go():
    count=0
    for l in range(1,12):
        for mask in range(1,1<<l):
            xs=[i for i in range(l) if mask>>i&1]
            if len(xs)>8:continue
            brute=sum(not bad([x for i,x in enumerate(xs) if c>>i&1],l) and not bad([x for i,x in enumerate(xs) if not(c>>i&1)],l) for c in range(1<<len(xs)))
            f=go_formula(xs,l)
            assert f==brute,(l,xs,f,brute)
            count+=1
    print('2020 N:',count,'point sets match exhaustive colorings')

def socks_pair(a,b):
    p=[[Fraction(0) for _ in range(2*b+1)] for _ in range(2*a+1)]
    p[0][0]=Fraction(1);ans=Fraction(0)
    for u in range(2*a+1):
        for v in range(2*b+1):
            rem=2*(a+b)-u-v
            if not rem:continue
            if u<2*a:
                q=p[u][v]*Fraction(2*a-u,rem);p[u+1][v]+=q
                if v%2:ans+=q*(1 if u%2==0 else Fraction(1,2))
            if v<2*b:
                q=p[u][v]*Fraction(2*b-v,rem);p[u][v+1]+=q
                if u%2:ans+=q*(1 if v%2==0 else Fraction(1,2))
    return ans

def verify_socks():
    for a in range(1,4):
        for b in range(1,4):
            total=Fraction(0);cnt=0
            for apos in itertools.combinations(range(2*(a+b)),2*a):
                aset=set(apos);u=v=0;z=Fraction(0)
                for i in range(2*(a+b)):
                    if i in aset:
                        if v%2:z+=1 if u%2==0 else Fraction(1,2)
                        u+=1
                    else:
                        if u%2:z+=1 if v%2==0 else Fraction(1,2)
                        v+=1
                total+=z;cnt+=1
            assert socks_pair(a,b)==total/cnt
    print('2021 C: pair probabilities match all relative shuffles for multiplicities 1..3')

if __name__=='__main__':
    verify_circle();verify_judge();verify_go();verify_socks()
