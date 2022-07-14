#include<stdio.h>

typedef struct{
    int Orig; //indica onde acaba cada vetor, dessa maneira pode usar somente 1 vetor
    unsigned long long num;
}vet;
 
void merge(vet arr[], int l, int m, int r){
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;
  vet L[n1], R[n2];
 
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
    }else if(L[i].num == R[j].num){
      if(L[i].Orig < R[j].Orig){
        arr[k] = L[i];
        i++;
      }else{
        arr[k] = R[j];
        j++;
      }
    }else {
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
 
void mergeSort(vet arr[], int l, int r){
  if (l < r) {
    int m = l + (r - l) / 2;
  
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
  }
}
 
int main(){
  int k, i, l, j, tamanho, n = 100000, ind=0;
  unsigned long long x, soma=0;
  scanf("%i %i", &k, &i);
  vet vetor[n];
  int verifica[k];
  for(j=0; j<k; j++){
    scanf("%i", &tamanho);
    for(l=0; l<tamanho; l++){ //for que adiciona os itens de cada vetor
      scanf("%lld", &x);
      vetor[ind].num = x; //elementos do vetor
      vetor[ind++].Orig = j; //onde 
    }
  }
  mergeSort(vetor, 0, ind-1);
  for(l=i-1; l<ind; l++){
    if(verifica[vetor[l].Orig] == 0){
      soma += vetor[l].num;
      verifica[vetor[l].Orig] = 1;                
    }
  }
  printf("%lld", soma);
  return 0;
}