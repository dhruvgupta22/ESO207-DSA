#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void BFS(int v, vector<int> adj[], int N, int M, vector <int> &distance, vector <int> &visited, vector <int> &parent){
    queue <int> nodes;
    parent[v] = 0;
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

void BFS_Traversal(vector<int> adj[], int N, int M, vector <int>& distance, vector <int>& visited, vector<int> &parent){
    for(int i=1; i<N+1; i++){
        if(visited[i] == 0){
            BFS(i,adj,N,M,distance,visited,parent);
        }
    }
}

int main(){
    int N,M;
    cin>>N>>M;
    int A[M], B[M];
    for(int i=0; i<M; i++){
        cin>>A[i];
    }
    for(int i=0; i<M; i++){
        cin>>B[i];
    }

    //Creating Adjacency list
    vector<int> adj[N+1];
    for(int i=0; i<M; i++){
        adj[A[i]].push_back(B[i]);
        adj[B[i]].push_back(A[i]);
    }
    for(int i = 1; i<N+1; i++){
        sort(adj[i].begin(),adj[i].end());
        // for(auto it:adj[i])cout<<it<<" ";
        // cout<<endl;
    }

    vector <int> distance(N+1, INT_MAX);
    vector <int> visited(N+1,0);
    vector <int> parent(N+1);
    BFS_Traversal(adj,N,M,distance,visited,parent);

    vector <pair<int,int>> non_tree;
    for(int i=0; i<M; i++){
        if(distance[A[i]] == distance[B[i]] || 
          (distance[A[i]] > distance[B[i]] && parent[A[i]] != B[i]) || 
          (distance[A[i]] < distance[B[i]] && parent[B[i]] != A[i])){
            non_tree.push_back({A[i],B[i]});
        }
    }
    
    vector<int>marked(N+1,0);
    for(auto pr: non_tree){
        int x = pr.first;
        int y = pr.second;
        while(x!=y){
            if(distance[x] == distance[y]){
                marked[x] = 1;
                marked[y] = 1;
                x = parent[x];
                y = parent[y];
            }
            else if(distance[x] > distance[y]){
                marked[x] = 1;
                x = parent[x];
            }
            else{
                marked[y] = 1;
                y = parent[y];
            }
        }
        marked[x] = 1;
    }
    
    for(int i=1; i<N+1; i++){
        cout<<marked[i];
        if(i!=N)cout<<" ";
    }

    return 0;
}