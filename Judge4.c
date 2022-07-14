#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int N, C, i, j, r, s, final;

typedef struct{
    int ri, si;
}blocks;

int max(int a, int b){ //maximo entre 2 valores 
    if(a>=b){
        return a;
    }
    else{
        return b;
    }
}

int blockchain(int C, blocks entradas[], int N){
    //construindo matriz de resolução
    int K[N+1][C+1];
    for(i=0;i<=N;i++){
        for(j=0;j<=C;j++){
            if(i==0 || j==0){
                K[i][j]=0; //caso base
            }
            else if (entradas[i-1].si <= j){
                K[i][j] = max(entradas[i-1].ri + K[i-1][j-entradas[i-1].si],  K[i-1][j]);
            }

           else{
               K[i][j] = K[i-1][j];
           }
        }
    }
    return K[N][C];
}

int main(){
    scanf("%d %d", &N, &C);
    blocks entradas[N];
    for(i=0;i<N;i++){
        scanf("%d %d", &r, &s);
        entradas[i].ri=r;
        entradas[i].si=s;
    }
    final = blockchain(C, entradas, N);
    printf("%d", final);
    return 0;
}