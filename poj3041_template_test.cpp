#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 1005;
vector<int>G[MAXN];
void addedge(int u, int v){
    G[u].push_back(v);
    G[v].push_back(u);
}
bool used[MAXN];
int match[MAXN];
bool dfs(int u){
    used[u]=true;
    for(int i=0; i<G[u].size(); i++){
        int v=G[u][i], w=match[v];
        if(w<0 || (!used[w]&&dfs(w)) ){
            match[u]=v;
            match[v]=u;
            return true;
        }
    }
    return false;
}
int big(int n){
    int res = 0;
    memset(match, -1, sizeof(match));
    for(int i=1; i<=n; i++){
        if(match[i]<0){
            memset(used, false, sizeof(used));
            if(dfs(i)){
                res++;
            }
        }
    }
    return res;
}
int main()
{
    int n, m;cin>>n>>m;
    for(int i=0; i<m; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        addedge(u, v+n);
    }
    printf("%d\n", big(n+n));
    return 0;
}

