#include <iostream>
using namespace std;

struct node{
    int l,r,sum;
};

void update(int a[], int n, int Query[], int q){
    for(int i=0; i<q; i++){
        a[Query[i]-1] = 1;
    }
}

int main(){
    int t;
    cin>>t;
    while(t--){
        int n, s;
        cin>>n>>s;
        int a[n];
        for(int i=0; i<n; i++){
            cin>>a[i];
        }
        int l[s], r[s];
        for(int i=0; i<s; i++){
            cin>>l[i]>>r[i];
        }
        int q, k;
        cin>>q>>k;
        int Query[q];
        for(int i=0; i<q; i++){
            cin>>Query[i];
        }


        struct node Sub[s];
        int start_sum[n+1] = {0};
        start_sum[0] = 0;
        for(int i = 1; i<=n; i++){
            start_sum[i] = start_sum[i-1] + a[i-1];
        }

        for(int i=0; i<s; i++){
            Sub[i].l = l[i]-1;
            Sub[i].r = r[i]-1;
            Sub[i].sum = start_sum[Sub[i].r+1] - start_sum[Sub[i].l];
        }
        int L = 0;
        int R = q;
        int ans = -1;
        while(L<=R){
            int temp[n];
            for(int i=0; i<n; i++){
                temp[i] = a[i];
            }
            int mid = (L+R)/2;
            update(temp, n, Query, mid);

            int start_sum[n+1] = {0};
            start_sum[0] = 0;
            for(int i = 1; i<=n; i++){
                start_sum[i] = start_sum[i-1] + temp[i-1];
            }
            int count=0;
            for(int i=0; i<s; i++){
                if(start_sum[Sub[i].r+1] - start_sum[Sub[i].l] > 0)count++;
            }
            if(count >= k){
                ans = mid;
                R = mid-1;
            }
            else{
                L = mid+1;
            }
        }
        cout<<ans<<endl;
        // for(int i=0; i<s; i++){
        //     cout<<Sub[i].l<<" "<<Sub[i].r<<" "<<Sub[i].sum<<endl;
        // }

        
        


    }

    return 0;
}