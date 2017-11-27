#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define mp make_pair
#define inchar getchar_unlocked
#define maxi 100111

using namespace std;

vector< pair<int,int> >v;
vector<int>st[4*maxi];
vector<int>::iterator it;
int a[maxi];

template<typename T> void inpos(T &x){
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

void construct(int si,int sl,int sr){
	if(sl==sr){
		st[si].pb(v[sl].second);
		return;
	}
	else{
		int mid = sl + (sr-sl)/2;
		int lt=2*si+1;
		int rt=2*si+2;
		construct(lt,sl,mid);
		construct(rt,mid+1,sr);
		merge(st[lt].begin(),st[lt].end(),st[rt].begin(),st[rt].end(),back_inserter(st[si]));
	}
}

int query(int si,int sl,int sr,int ql,int qr,int k){
	if(sl==sr){
		return st[si][0];
	}
	else{
		int mid = sl + (sr-sl)/2;
		int lt,rt;
		lt = 2*si+1;
		rt = 2*si+2;
		it = upper_bound(st[lt].begin(),st[lt].end(),qr);
		int tot = it - lower_bound(st[lt].begin(),st[lt].end(),ql);
		if(tot >=k){
			return query(lt,sl,mid,ql,qr,k);
		}
		else{
			return query(rt,mid+1,sr,ql,qr,k-tot);
		}
	}
}

int main(){
	int n,m,i,l,r,k,ans;
	inpos(n);
	inpos(m);

	for(i=0;i<n;i++){
		inpos(a[i]);
		v.pb(mp(a[i],i));
	}

	sort(v.begin(),v.end());
	construct(0,0,n-1);

	for(i=1;i<=m;i++){
		inpos(l);
		inpos(r);
		inpos(k);

		l--;
		r--;

		ans = query(0,0,n-1,l,r,k);
		cout<<a[ans]<<endl;	
	}


	return 0;
}