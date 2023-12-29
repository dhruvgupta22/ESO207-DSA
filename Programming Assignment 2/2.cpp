#include <iostream>
using namespace std;

int max(int a[], int i, int j){
    int temp = i;
    for(int k = i; k<j; k++){
        if(a[k+1] > a[temp]) temp = k+1;
    }
    return temp;
}

void find_depth(int a[],int depth[], int n, int i, int j){
    if(i==j){
        // depth[i]++;
        return;
    }
    if(i<0 ||j<0 || i>n-1 || j>n-1)return;
    else{
        int root = max(a,i,j);
        for(int k=i; k<=j; k++){
            depth[k]++;
        }
        depth[root]--;
        if(root != i)find_depth(a,depth,n,i,root-1);
        if(root != j)find_depth(a,depth,n,root+1,j);
        return;
    }
}

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int a[n];
        for(int i=0; i<n; i++){
            cin>>a[i];
        }
        int depth[n] = {0};
        find_depth(a,depth,n,0,n-1);
        for(int i=0; i<n; i++){
            cout<<depth[i]<<" ";
        }
        cout<<endl;
    }
    

    return 0;
}
