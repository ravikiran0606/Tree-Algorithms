#include<bits/stdc++.h>
#define maxi 111
#define logmaxi 11

using namespace std;

vector< vector<int> >graph;
vector<int>par,l;
int p[maxi][logmaxi];

void dfs(int s,int lvl){
    l[s]=lvl;
    for(int i=0;i<graph[s].size();i++){
        par[graph[s][i]]=s;
        dfs(graph[s][i],lvl+1);
    }
}

void construct(int n){
    int i,j;

    for(i=1;i<=n;i++){
        for(j=1;pow(2,j)<=n;j++){
            p[i][j]=-1;
        }
    }

    // base case..
    for(i=1;i<=n;i++){
        p[i][0]=par[i];
    }

    // bottom up dp...
    for(j=1;pow(2,j)<=n;j++){
        for(i=1;i<=n;i++){
            if(p[i][j-1]!=-1){
                p[i][j]=p[p[i][j-1]][j-1];
            }
        }
    }
}

int query(int u,int v){
    int temp;
    if(l[u]<l[v]){
        temp=u;
        u=v;
        v=temp;
    }

    int log;
    for(log=1;pow(2,log)<=l[u];log++);
    log--;

    for(int i=log;i>=0;i--){
        if(l[u]-pow(2,i)>=l[v]){
            u=p[u][i];
        }
    }

    if(u==v)return u;

    for(int i=log;i>=0;i--){
        if(p[u][i]!=-1 && p[u][i]!=p[v][i]){
            u=p[u][i];
            v=p[v][i];
        }
    }

    return par[u];
}



int main(){

    // for filling l and par array...

    int n;
    cin>>n;
    graph.resize(n+1);
    l.resize(n+1);
    par.resize(n+1);
    dfs(1,0);
    par[1]=-1;

    // for filling p array..

    construct(n);

    // for query..

    int ans=query(1,2);


    return 0;
}
