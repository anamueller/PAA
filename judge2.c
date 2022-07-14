#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    int orig; //indica onde acaba cada vetor, dessa maneira pode usar somente 1 vetor
    unsigned long long num;
}vetor;

//função mergesort padrão
void merge(vetor arr[], int l, int m, int r){
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;
  vetor L[n1], R[n2];
 
  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];
  
  i = 0; 
  j = 0;
  k = l; 
	
  while (i < n1 && j < n2) {
    if (L[i].num < R[j].num){
      arr[k] = L[i];
      i++;
    }
    else if(L[i].num == R[j].num){
      if(L[i].orig < R[j].orig){
        arr[k] = L[i];
        i++;
      }
      else{
        arr[k] = R[j];
        j++;
      }
    }
    else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }
  
  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(vetor arr[], int l, int r){
  if (l < r) {
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
  }
}

int main(){
    int i, k, j, tamanho, m, n = 100000, ind=0;
    unsigned long long x, soma=0;
    
    scanf("%d %d", &k, &i);
    vetor vet[n]; //N=100000 (estipulado no enunciado)
    int v[k]; //max 10000
    for(j=0; j<k; j++){//escaneando os vetores
        scanf("%d", &tamanho);
        for(m=0; m<tamanho; m++){//for que adiciona os itens de cada vetor
            scanf("%lld", &x);
            vet[ind].num = x;//elementos do vetor
            vet[ind].orig = j; //anota onde o primeiro vetor começa
            ind++; //adiciona até o final do primeiro vetor para sempre estar no inicio corretor do segundo vetor
        }
    }
    mergeSort(vet, 0, ind-1); //ordenando o vetor
    for(m=i-1; m<ind; m++){ //iesimo valor como pedido = i-1
        if(v[vet[m].orig] == 0){ //passando pelo primeiro número de cada vetor
            soma = soma + vet[m].num;
            v[vet[m].orig] = 1;
        }
    }
    printf("%lld", soma);
    return 0;
}