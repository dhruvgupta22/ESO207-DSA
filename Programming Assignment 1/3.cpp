#include <iostream>
using namespace std;

long long int M = 998244353;

long long int pow(long long int x, long long int n){
    if(n==0) return 1;
    else{
        long long int temp = pow(x, n/2);
        temp = (temp*temp)%M;
        if(n%2 == 1) temp = (temp*x)%M;
        return temp;
    }
}

void init(long long int A[][20], int k){
    for(int i=0; i<k; i++){
        for(int j=0; j<k; j++){
            if(i==0 || i-1==j)A[i][j] = 1;
            else A[i][j] = 0;
        }
    }
}
void inti2(long long int B[][20], int k){
    long long int temp[2*k-1];
    temp[0] = 0;
    temp[1] = 1;
    for(int i=2; i<=k+1; i++){
        temp[i] = pow(2, i-2);
        temp[i] = temp[i]%M;
    }
    for(int i=k+2; i<2*k-1; i++){
        temp[i] = 0;
        for(int j=i-k; j<i; j++){
            temp[i] += temp[j]%M;
            temp[i] = temp[i]%M;
        }
    }

    for(int i=0; i<k; i++){
        for(int j=0; j<k; j++){
            B[i][j] = temp[2*k-i-j-2]%M;
        }
    }
}
void printArr(long long int A[][20], int k){
    for(int i=0; i<k; i++){
        for(int j=0; j<k; j++){
            cout<<A[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void copy(long long int A[][20], long long int B[][20], int k){
    for(int i=0; i<k; i++){
        for(int j=0; j<k; j++){
            A[i][j] = B[i][j]%M;
        }
    }
}
void matrix_multiply(long long int A[][20], long long int B[][20], int k){
    long long int temp[k][20];
    for(int i=0; i<k; i++){
        for(int j=0; j<k; j++){
            temp[i][j]=0;
            for(int r=0; r<k; r++){
                temp[i][j] += (A[i][r] * B[r][j]%M)%M;
                temp[i][j] = temp[i][j]%M;
            }
        }
    }
    copy(A,temp,k);
}

void power(long long int A[][20], long long int B[][20], long long int n, int k){
    if(n == 1){
        return;
    }
    if(n%2 == 0){   
        power(A, B, n/2, k);
        matrix_multiply(A, A, k);
        return;
    }
    else{
        power(A, B, (n-1)/2, k);
        matrix_multiply(A, A, k);
        matrix_multiply(A, B, k);
        return;
    }
}

int main(){
    int t;
    cin>>t;
    while(t--){
        long long int n;
        int k;
        cin>>n>>k;
        long long int A[k][20];
        init(A,k);
        // printArr(A,k);

        long long int A1[k][20];
        long long int B[k][20];
        init(A1,k);
        inti2(B,k);

        power(A,A1,n,k);
        matrix_multiply(A,B,k);
        cout<<A[k-2][k-1]<<endl;
    }
    return 0;
}