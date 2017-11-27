#include<bits/stdc++.h>
#define maxi 1111
#define inf 1111111
#define pb push_back
#define mp make_pair
#define ll long long
#define mod 1e9+7

using namespace std;

ll leastfactor[inf];
ll a[maxi],st[4*maxi];

ll construct(ll l,ll r,ll si){
    if(l==r){
        st[si]=a[l];
        return st[si];
    }
    else{
        ll mid=l+(r-l)/2;
        st[si]=max(construct(l,mid,2*si+1),construct(mid+1,r,2*si+2));
        return st[si];
    }
}

ll query(ll sl,ll sr,ll si,ll ql,ll qr){
    if(ql<=sl && qr>=sr){
        return st[si];
    }
    else if(ql>sr || qr<sl){
        return -1;
    }
    else{
        ll mid=sl+(sr-sl)/2;
        return max(query(sl,mid,2*si+1,ql,qr),query(mid+1,sr,2*si+2,ql,qr));
    }
}

ll update(ll sl,ll sr,ll si,ll l,ll r){
    if(sl==sr && sl>=l && sl<=r){
        st[si]*=2;
        return st[si];
    }
    else if(sr<l || sl>r){
        return st[si];
    }
    else{
        ll mid=sl+(sr-sl)/2;
        st[si]=max(update(sl,mid,2*si+1,l,r),update(mid+1,sr,2*si+2,l,r));
        return st[si];
    }
}

int main()
{
    int t,type;
    ll n,m,l,i,j,r,temp;
    int ch;
    cin>>n;
    for(i=0;i<n;i++)cin>>a[i];
    ll ans=construct(0,n-1,0);

    cout<<"choice 1) Query 2) Update ";
    while(1){
        cout<<"\nEnter..";
        cin>>ch;
        if(ch==1){
            cin>>l>>r;
            ll ans=query(0,n-1,0,l,r);
            cout<<ans<<endl;
        }
        else if(ch==2){
            cin>>l>>r;
            ll ans=update(0,n-1,0,l,r);
        }
    }


    return 0;
}

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            