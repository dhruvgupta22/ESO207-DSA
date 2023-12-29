#include <iostream>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        long long int A[n];
        //Array Input Loop
        for(long long int i=0; i<n; i++){
            cin>>A[i];
        }
        long long int S[n];
        S[n-1] = A[n-1];
        for(int i=n-2; i>=0; i--){
            if(S[i+1] > 0)S[i] = S[i+1] + A[i];
            else S[i] = A[i];
        }
        // Array print loop
        for(long long int i=0; i<n; i++){
            cout<<S[i]<<" ";
            if(i==n-1)cout<<"\n";
        }
    }

    return 0;
}
