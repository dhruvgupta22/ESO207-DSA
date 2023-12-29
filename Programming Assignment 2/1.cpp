#include <iostream>
using namespace std;



long long int Merge_and_CountInversion(int A[],int i,int mid,int k, int C[]){
    int p = i;
    int j = mid+1;
    int r = 0;
    long long int count_3 = 0;
    while(p<=mid && j<=k){
        if(A[p]<=A[j]){ C[r] = A[p]; r++; p++; }
        else{ C[r] = A[j]; r++; j++; count_3 = count_3 + mid-p+1; }
    }
    while(p<=mid){ C[r] = A[p]; r++; p++; }
    while(j<=k){ C[r] = A[j]; r++; j++; }
    return count_3;
}



long long int Sort_and_CountInversion(int A[],int i,int k){
    if(i==k) return 0;
    else{
        int mid = (i+k)/2;
        long long int count_1 = Sort_and_CountInversion(A,i,mid);
        long long int count_2 = Sort_and_CountInversion(A,mid+1,k);
        int C[k-i+1];
        long long int count_3 = Merge_and_CountInversion(A,i,mid,k,C);
        
        for(int idx = 0; idx<k-i+1; idx++){
            A[i+idx] = C[idx];
        }
        // int count_3 = 0;
        return count_1 + count_2 + count_3;
    }
}



int main(){
    int t;
    cin>>t;
    while(t--){
        int N;
        cin>>N;
        int A[N];
        // int C[N];
        for(int i=0; i<N; i++){
            cin>>A[i];
        }
        long long int ans = Sort_and_CountInversion(A,0,N-1);
        cout<<ans<<endl;
        // cout<<"Test case terminated successfully"<<endl;
    }
    // cout<<"Program terminated succesfully";
    return 0;
}
