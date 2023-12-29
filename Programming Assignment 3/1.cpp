#include <iostream>
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> Edges_to_adjL(vector<pair<int,int>>edges, int V, int E);
void BFS(int v, vector<int> adj[], int N, int M, vector <int>& distance, vector <int>& visited);
void BFS_Traversal(vector<int> adj[], int N, int M, vector <int>& distance, vector <int>& visited);

int main(){
    int N, M;
    cin>>N>>M;
    
    // vector<pair<int,int>> edges(M);
    // for(int i = 0; i<M; i++){
    //     cin>>edges[i].first>>edges[i].second;
    // }

    //Create Adjacency list
    vector<int> adj[N+1];
    for(int i=0; i<M; i++){
        int u, v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    //Apply BFS
    vector <int> distance(N+1, INT_MAX);
    vector <int> visited(N+1, 0);
    BFS_Traversal(adj,N,M,distance,visited);


    int flag = 0;
    for(int i = 1; i<N+1; i++){
        for(auto v : adj[i]){
            if(distance[i] == distance[v]){
                flag = 1;
                break;
            }
        }
    }

    if(flag == 0){
        cout<<"YES"<<endl;
        for(int i = 1; i<N+1; i++){
            if(distance[i]%2 == 0) cout<<1;
            else cout<<2;
            cout<<" ";
        }
    }
    else{
        cout<<"NO";
    }

    return 0;
}

vector<vector<int>> Edges_to_adjL(vector<pair<int,int>>edges, int V, int E){
    vector<vector<int>> adj(V+1);
    for(auto pr : edges){
        adj[pr.first].push_back(pr.second);
        adj[pr.second].push_back(pr.first);
    }
    for(int i = 1; i<V+1; i++){
        sort(adj[i].begin(),adj[i].end());
    //     for(auto it:adj[i])cout<<it<<" ";
    //     cout<<endl;
    }
    return adj;
}

void BFS(int v, vector<int> adj[], int N, int M, vector <int> &distance, vector <int> &visited){
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
            }
        }
    }

}

void BFS_Traversal(vector<int> adj[], int N, int M, vector <int>& distance, vector <int>& visited){
    for(int i=1; i<N+1; i++){
        if(visited[i] == 0){
            BFS(i,adj,N,M,distance,visited);
        }
    }
}