#include<bits/stdc++.h>

using namespace std;

vector< vector<int> >graph;
vector<int>p,par,l;

void dfs(int s,int lvl){
    l[s]=lvl;
    for(int i=0;i<graph[s].size();i++){
        par[graph[s][i]]=s;
        dfs(graph[s][i],lvl+1);
    }
}

void constructdfs(int s,int sqr){
    if(l[s]<sqr){
        p[s]=1;
    }
    else if(sqr%l[s]==0){
        p[s]=par[s];
    }
    else{
        p[s]=p[par[s]];
    }
    for(int i=0;i<graph[s].size();i++){
        constructdfs(graph[s][i],sqr);
    }
}

int query(int u,int v){
    while(p[u]!=p[v]){
        if(l[u]>l[v]){
            u=p[u];
        }
        else{
            v=p[v];
        }
    }

    while(u!=v){
        if(l[u]>l[v]){
            u=par[u];
        }
        else{
            v=par[v];
        }
    }
    return u;
}


int main(){

    // for filling l and par array...

    int n;
    cin>>n;
    graph.resize(n+1);
    p.resize(n+1);
    par.resize(n+1);
    l.resize(n+1);
    dfs(1,0);
    par[1]=-1;

    // for filling p array...
    constructdfs(1,sqrt(n));

    // query..
    ll ans=query(1,2);

    return 0;
}
