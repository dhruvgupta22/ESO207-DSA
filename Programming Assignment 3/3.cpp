#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void BFS(int v, vector<int> adj[], int N, int M, vector <int> &distance, vector <int> &visited, vector <int> &parent);
void BFS_Traversal(vector<int> adj[], int N, int M, vector <int>& distance, vector <int>& visited, vector<int> &parent);
int Find_ancestor(int i, int k, vector<vector<int>> Ancestors);
int common_ancestor(int u, int v, vector<int> distance, vector<vector<int>> Ancestors, int logN);
void DFS(int v, int V, int E, vector<int> adj[], vector<int>&visited,int breadcrumbs[]);
void DFS_Traversal(int V, int E, vector<int> adj[], vector<int>&visited, int breadcrumbs[]);

void BFS(int v, vector<int> adj[], int N, int distance[], int visited[], int parent[]){
    queue <int> nodes;
    nodes.push(v);
    visited[v] = 1;
    distance[v] = 0;
    while(!nodes.empty()){
        int x = nodes.front();
        nodes.pop();
        for(auto it : adj[x]){
            if(visited[it] == 0){
                nodes.push(it);
                distance[it] = distance[x] + 1;
                visited[it] = 1;
                parent[it] = x;
            }
        }
    }

}

int Find_ancestor(int i, int k, vector<int> Ancestors[]){
    int c=i;
    int a=log2(k);
    for(int j=a;j>=0;j--){
        if(k>=pow(2,j)){
            c=Ancestors[c][j];
            k-=pow(2,j);
        }
    }
    return c;
}

int common_ancestor(int u, int v, int distance[], vector<int> Ancestors[], int logN){
    if(distance[u] > distance[v]){
        u = Find_ancestor(u,distance[u]-distance[v],Ancestors);
    }
    else if(distance[v] > distance[u]){
        v = Find_ancestor(v,distance[v]-distance[u],Ancestors);
    }
    if(u==v) return u;
    int j = logN;
    for(;j>=0;j--){
        if(Ancestors[u][j] != Ancestors[v][j]){
            u = Ancestors[u][j];
            v = Ancestors[v][j];
        }
    }
    if(u==v) return u;
    return Ancestors[u][0];
}


void DFS(int v, int V, int E, vector<int> adj[], int visited[],int breadcrumbs[]){
    visited[v] = 1;
    // cout<<v<<" ";
    for(auto w : adj[v]){
        if(visited[w] == 0){
            DFS(w,V,E,adj,visited,breadcrumbs);
            breadcrumbs[v] += breadcrumbs[w];
        }
    }
}

void DFS_Traversal(int V, int E, vector<int> adj[], int visited[], int breadcrumbs[]){
    for(int i=0; i<V; i++){
        visited[i] = 0;
    }
    for(int i=0; i<V; i++){
        if(visited[i] == 0){
            DFS(i,V,E,adj,visited,breadcrumbs);
        }
    }
}


int main(){

    //Input
    int N,K;
    cin>>N>>K;
    int A[N-1],B[N-1];
    int Q1[K], Q2[K];
    for(int i=0; i<N-1; i++){
        cin>>A[i];
        A[i]--;
    }
    for(int i=0; i<N-1; i++){
        cin>>B[i];
        B[i]--;
    }
    for(int i=0; i<K; i++){
        cin>>Q1[i]>>Q2[i];
        Q1[i]--;
        Q2[i]--;
    }

    //Adjacency list
    vector<int> adj[N+1];
    for(int i=0; i<N-1; i++){
        adj[A[i]].push_back(B[i]);
        adj[B[i]].push_back(A[i]);
    }

    //BFS Tree
    int distance[N];
    int visited[N];
    int parent[N];
    for(int i=0; i<N; i++){
        distance[i] =0;
        visited[i] = 0;
        parent[i] = -1;
    }
    BFS(0,adj,N,distance,visited,parent);
    int max = distance[0];
    for(int i=1; i<N; i++){
        if(max < distance[i]){
            max = distance[i];
        }
    }
    
    //Ancestors
    int logN = log2(max);
    vector<int> Ancestors[N];
    for(int i = 0; i<N; i++){
        Ancestors[i].push_back(parent[i]);
    }
    for(int j = 1; j < logN+1; j++){
        for(int i = 0; i<N; i++){
            int temp = Ancestors[i][j-1];
            if(temp==-1) Ancestors[i].push_back(-1);
            else Ancestors[i].push_back(Ancestors[temp][j-1]);
        }
    }
//     //Breadcrumbs
    int breadcrumbs[N] = {0};
    for(int i=0; i<K; i++){
        breadcrumbs[Q1[i]] += 1;
        breadcrumbs[Q2[i]] += 1;
        int q = common_ancestor(Q1[i],Q2[i],distance,Ancestors,logN);
        breadcrumbs[q] -= 1;
        if(q !=0){
            breadcrumbs[parent[q]] -= 1;
        }
    }

    DFS_Traversal(N,N-1,adj,visited,breadcrumbs);

    for(int i = 0; i<N; i++){
        cout<<breadcrumbs[i]<<" ";
    }

    return 0;
}
