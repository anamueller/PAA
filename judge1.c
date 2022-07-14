#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int dia_trinta = 0;
int N, M, i, dias, media;
float soma;
int acessos[30];

void calcular(){
    while(N<M){ //calculando quantos dias será necessário
        media = ceil(soma/30);
        soma = soma - acessos[dia_trinta];
        soma = soma + media;
        acessos[dia_trinta] = media;
        if(dia_trinta<29){
            dia_trinta++;
        }
        else{
            dia_trinta = 0; 
        }
        N = N + media;
        dias++;//enquanto n atingeo n° de usuários continua no loop
    }
}

int main(){
    scanf("%d %d", &N, &M);
    for (i=0; i<30; i++){ //escaneando os 30 acessos e adicionando em um vetor
        scanf("%d", &acessos[i]);
        soma = soma + acessos[i];
    }
    calcular();
    printf("%d ", dias);
    return 0;
}