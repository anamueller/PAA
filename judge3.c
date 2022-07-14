#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int n=1, linha, coluna, i, j, m, c, k, count=9, curr=0;
int move_cavalo[8];

typedef struct{
    int posicao;
    int capturado; //0 = capturado, 1 = não capturado
} peao;

peao vetor_de_peos[8];
peao peos_copiados[8];

typedef struct{
    int posicao;
    int posicao_antiga;
} cav;

cav cavalo;

void inicia_tabuleiro(peao vetor[], int c, int np){
   for(i=0;i<np;i++){
       vetor[i].capturado=1;
   }
   cavalo.posicao=c;
   cavalo.posicao_antiga=c;
}

void posicoes_cavalo(int posc, peao vetor[]){//gera as posicoes possiveis do cavalo dada a posicao q ele se encontra
    linha = floor(posc/8);
    coluna = posc-(8*linha) - 1;
    int temp[8];
    temp[0] = (coluna-2)+8*(linha+1)+1;//possiveis movimentos
    temp[1] = (coluna-2)+8*(linha-1)+1;
    temp[2] = (coluna+2)+8*(linha+1)+1;
    temp[3] = (coluna+2)+8*(linha-1)+1;
    temp[4] = (coluna-1)+8*(linha+2)+1;
    temp[5] = (coluna-1)+8*(linha-2)+1;
    temp[6] = (coluna+1)+8*(linha+2)+1;
    temp[7] = (coluna+1)+8*(linha-2)+1;
    j=0;
    for(i=0;i<8;i++){
        if(temp[i]>0){ //descarta os movimentos nao possiveis
            for(k=0;k<m;k++){
                if(temp[i]-8==vetor[k].posicao){//peao come na proxima jogada
                    continue;
                }
                else{
                    move_cavalo[j]=temp[i];//adicionando ao vetor as posicoes do cavalo
                    j++;
                }
            }
        }
    }
}

void copiar(){
    for(i=0;i<8;i++){
        peos_copiados[i].posicao=vetor_de_peos[i].posicao;
        peos_copiados[i].capturado=vetor_de_peos[i].capturado;
    }
}

void mexer_pecas(peao p[], int cantigo, int cnovo){ //da as posições anterior, adiciona 8 na posicao
    cavalo.posicao=cnovo;
    cavalo.posicao_antiga=cantigo; //cavalo é atualizado
    for(i=0;i<8;i++){ //peos sao mexido uma casa para frente
        if(cnovo==p[i].posicao){
            p[i].capturado=0;
        }
        p[i].posicao=p[i].posicao+8;
    }
}

int checa_peao(peao p[]){
    for(i=0; i<8;i++){ //itera sobre o vetor de peos
        if(p[i].capturado==1){
            return 1; //ainda tem peao
        }
    }
    return 0; //nao tem peao no tabuleiro
}

int checa_impossivel(peao p[]){
    int p0=0, p1=0, p2=0, p3=0, p4=0, p5=0, p6=0, p7=0, pt=0;
    for(i=0;i<8;i++){
        linha = floor(p[i].posicao/8);
        if(linha==0){
            p0++;//contando quantos peoes tem na linha 0
            pt++;
        }
        if(linha==1){
            p1++;//contando quantos peoes tem na linha 1
            pt++;
        }
        if(linha==2){
            p2++;//contando quantos peoes tem na linha 2
            pt++;
        }
        if(linha==3){
            p3++;//contando quantos peoes tem na linha 3
            pt++;
        }
        if(linha==4){
            p4++;//contando quantos peoes tem na linha 4
            pt++;
        }
        if(linha==5){
            p5++;//contando quantos peoes tem na linha 5
            pt++;
        }
        if(linha==6){
            p6++;//contando quantos peoes tem na linha 6
            pt++;
        }
        if(linha==7){
            p7++; //contando quantos peoes tem na linha 7
            pt++;
        }
        if(p7>=1 || p6>=2 || p5>=3 || p4>=4 || p3>=5 || p2>=6 || p1>=7 || p0==8 || pt==8){
            return 1; //jogo perdido, impossivel de ganhar
        }
        if(p7>0 && c<41){//cavalo não chega na linha 7 nao come peao e como ja esta na linha 7 vira rei
            return 1;
        }
    }
    return 0; //jogo ainda tem chances de ganhar
}

int backtracking(peao vetor[], int c, int atual){
    int imp = checa_impossivel(vetor);
    int pe=checa_peao(vetor);
    if(imp==1){
        return 8; //impossivel
    }
    if(atual>=count){
        return 8; //maior q a outra jogada, descartada
    }
    if(pe==0){
        return atual;
    }
    posicoes_cavalo(c, vetor);
    for(i=0;i<8;i++){
        copiar();
        mexer_pecas(peos_copiados, c, move_cavalo[i]);
        int resultado = backtracking(peos_copiados, move_cavalo[i], atual+1);
        if(resultado<count){
            count = resultado;
        }
    }
    return count;
}

int main(){
    scanf("%d", &m);
    for(i=0; i<m; i++){
        scanf("%d", &vetor_de_peos[i].posicao);
    }
    scanf("%d", &c);
    inicia_tabuleiro(vetor_de_peos, c, m);
    posicoes_cavalo(c, vetor_de_peos);
    int final = backtracking(vetor_de_peos, c, curr);
    if(final==8){
        printf("impossible");
    }
    if(final!=8){
        printf("%d", final);
    }
    return 0;
}