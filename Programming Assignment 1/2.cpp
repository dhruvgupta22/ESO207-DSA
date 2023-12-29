#include <iostream>
using namespace std;

long long int Sum(long long int n){
    return (n*(n+1))/2;
}
long long int Cost(long long int a, long long int A[], long long int n){
    long long int cost = 0;
    for(long long int i=0; i<n; i++){
        if(A[i]>a)cost += Sum(A[i]) - Sum(a);
        // cout<<cost<<" ";
    }
    return cost;
}
void update_A(long long int a, long long int A[], long long int n){
    for(long long int i=0; i<n; i++){
        if(A[i]>a)A[i]=a;
        // cout<<cost<<" ";
    }
}
bool equal_A(long long int A[], long long int n){
    bool flag = 0;
    long long int min = A[0];
    long long int max = A[0];
    for(long long int i=1; i<n; i++){
        if(A[i]<=min)min = A[i];
        if(A[i]>=max)max = A[i];
    }
    if(max==min)flag = 1;
    return flag;
}
int main(){
    long long int t;
    cin>>t;
    while(t--){
        long long int n;
        long long int k;
        cin>>n>>k;
        long long int A[n];
        //Array Input Loop
        for(long long int i=0; i<n; i++){
            cin>>A[i];
        }
        // Array print loop
        // for(long long int i=0; i<n; i++){
        //     cout<<A[i]<<" ";
        //     if(i==n-1)cout<<"\n";
        // }

        //Finding max and min elements of A.
        long long int min = A[0];
        long long int max = A[0];
        for(long long int i=1; i<n; i++){
            if(A[i]<=min)min = A[i];
            if(A[i]>=max)max = A[i];
        }
        long long int cost=0;
        long long int mid = (max+min)/2;

        long long int ans = 0;
        if(k>=Cost(0,A,n)){ans = 0;cout<<"0\n";continue;}
        // while((mid != max && mid != min)){
        if(equal_A(A,n)){
            long long int i=max;
            while(cost<k){
                i--;
                cost = Cost(i, A, n);
            }
            ans = i;
        }
        else
        {
        while(mid!=max && mid!=min){
            ans = mid;
            cost = Cost(mid, A, n);
            // cout<<max<<" "<<min<<" "<<mid<<" "<<cost<<endl;
            if(cost == k){
                ans = mid;
                break;
            }
            else if(cost < k){
                max = mid;
                mid = (max + min)/2;
            }
            else{
                min = mid;
                mid = (max + min)/2;
            }
        }
        }
        long long int x = ans;
        while(Cost(x,A,n)<=k){
            x--;
        }
        ans = x+1;
        // cout<<Cost(ans, A, n)<<" ";
        cout<<ans<<endl;
        // update_A(ans, A, n);
        // for(long long int i=0; i<n; i++){
        //     cout<<A[i]<<" ";
        //     if(i==n-1)cout<<"\n";
        // }
        
        
    }

    return 0;
}
