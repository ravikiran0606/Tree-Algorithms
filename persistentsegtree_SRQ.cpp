#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define maxi 100111

using namespace std;

int l[maxi],r[maxi],st[maxi],root[maxi];
int a[maxi];
int ROOTS=0,NODES=0;

int newleaf(int val){
	int p = NODES;
	NODES++;

	st[p]=val;
	l[p]=r[p]=0;
	return p;
}

int newparent(int left,int right){
	int p = NODES;
	NODES++;

	l[p]=left;
	r[p]=right;
	st[p]=st[left]+st[right];
	return p;
}

int construct(int sl,int sr){
	if(sl==sr){
		return newleaf(a[sl]);
	}
	else{
		int mid = sl + (sr-sl)/2;
		return newparent(construct(sl,mid),construct(mid+1,sr));
	}
}

int update(int u,int val,int si,int sl,int sr){
	if(sl==sr && sl==u){
		return newleaf(val);
	}
	else if(sl>u || sr<u){
		return si;
	}
	else{
		int mid = sl + (sr-sl)/2;
		return newparent(update(u,val,l[si],sl,mid),update(u,val,r[si],mid+1,sr));
	}
}

int query(int ql,int qr,int si,int sl,int sr){
	if(sl>=ql && sr<=qr){
		return st[si];
	}
	else if(qr<sl || ql>sr){
		return 0;
	}
	else{
		int mid = sl + (sr-sl)/2;
		return query(ql,qr,l[si],sl,mid)+query(ql,qr,r[si],mid+1,sr);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n,i,m,ll,rr,val;
	int type;
	cin>>n;

	for(i=0;i<n;i++){
		cin>>a[i];
	}

	root[ROOTS]=construct(0,n-1);
	ROOTS++;

	cin>>m;
	while(m--){
		cin>>type;
		if(type==1){
			cin>>ll>>val;
			root[ROOTS]=update(ll,val,root[ROOTS-1],0,n-1);
			ROOTS++;
		}
		else{
			cin>>ll>>rr;
			int ans = query(ll,rr,root[ROOTS-1],0,n-1);
			cout<<ans<<endl;
		}
	}

	return 0;
}