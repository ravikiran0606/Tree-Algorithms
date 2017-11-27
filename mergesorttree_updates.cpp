#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define mp make_pair
#define maxi 100011
#define inchar getchar_unlocked
#define outchar(x) putchar_unlocked(x)

using namespace std;

template<typename T> void read(T &x){
	x=0;
	register T c=inchar();
	while(((c<48)||(c>57))&&(c!='-')){
		c=inchar();
	}
	bool neg=false;
	if(c=='-')neg=true;
	for(;c<48||c>57;c=inchar());
	for(;c>47&&c<58;c=inchar()){
		x=(x<<3)+(x<<1)+(c&15);
	}
	if(neg)x=-x;
}

template<typename T> void write(T n){
	if(n<0){
		outchar('-');
		n*=-1;
	}
	char snum[65];
	int i=0;
	do {
		snum[i++]=n%10+'0';
		n/=10;
	}while(n);

	i=i-1;
	while(i>=0){
		outchar(snum[i--]);
	}
	outchar('\n');
}

ll a[maxi];
multiset<ll>st[4*maxi];
multiset<ll>::iterator it;

void construct(ll si,ll sl,ll sr){
	if(sl==sr){
		st[si].insert(a[sl]);
		return;
	}
	else{
		ll lt,rt;
		lt = 2*si+1;
		rt = 2*si+2;
		ll mid = sl + (sr-sl)/2;
		construct(lt,sl,mid);
		construct(rt,mid+1,sr);
		st[si]=st[lt];
		for(it=st[rt].begin();it!=st[rt].end();it++){
			st[si].insert(*it);
		}
		return;
	}	
}

void update(ll si,ll sl,ll sr,ll u,ll prev,ll val){
	if(sl==sr && sl==u){
		st[si].erase(st[si].find(prev));
		st[si].insert(val);
		return;
	}
	else if(sr<u || sl>u){
		return;
	}
	else{
		ll mid = sl + (sr-sl)/2;
		update(2*si+1,sl,mid,u,prev,val);
		update(2*si+2,mid+1,sr,u,prev,val);
		st[si].erase(st[si].find(prev));
		st[si].insert(val);
		return;
	}
}

ll calc(ll a,ll b,ll c){
	return (b-a)*(c-b);
}

ll query(ll si,ll sl,ll sr,ll ql,ll qr){
	if(sl>=ql && sr<=qr){
		ll val = (a[ql]+a[qr])/2;
		ll maxv = 0LL;
		it = st[si].lower_bound(val);

		if(it!=st[si].end()){
			maxv = max(maxv,calc(a[ql],*it,a[qr]));
			it++;
			if(it!=st[si].end()){
				maxv = max(maxv,calc(a[ql],*it,a[qr]));
			}
			it--;
		}
		
		if(it!=st[si].begin()){
			it--;
			maxv = max(maxv,calc(a[ql],*it,a[qr]));
		}
		return maxv;
	}
	else if(sr<ql || sl>qr){
		return 0;
	}
	else{
		ll mid = sl + (sr-sl)/2;
		return max(query(2*si+1,sl,mid,ql,qr),query(2*si+2,mid+1,sr,ql,qr));
	}
}

int main(){
	ll t;
	read(t);
	ll n,q,val;
	ll ans;
	int type;
	ll l,r,i;
	while(t--){
		read(n);
		read(q);
		for(i=0;i<n;i++){
			read(a[i]);
		}

		for(i=0;i<=4*n;i++){
			st[i].clear();
		}

		construct(0,0,n-1);

		while(q--){
			read(type);
			if(type==1){
				read(l);
				read(r);
				l--;
				r--;
				ans = query(0,0,n-1,l,r);
				cout<<ans<<endl;
			}
			else{
				read(l);
				read(val);
				l--;
				update(0,0,n-1,l,a[l],val);
				a[l]=val;
			}
		}
	}

	return 0;
}