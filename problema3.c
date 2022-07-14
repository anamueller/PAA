#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int n=1, linha, coluna, i, j, m, c, maxcav, count, atual=0;
int move_cavalo[8];

typedef struct{
    int posicao;
    int peca;
} tab;

tab tabuleiro [8][8];

void inicia_tabuleiro(int peoes[], int cavalo, int np){
    for(i=0; i<8;i++){ //posicoes 1-64 do tabuleiro
        for(int j=0; j<8; j++){
            tabuleiro[i][j].posicao = n;
            n++;
        }
    }
    for(i=0; i<np;i++){ //adicionando os peoes=1
        linha = floor(peoes[i]/8);
        coluna = peoes[i]-(8*linha) - 1;
        tabuleiro[linha][coluna].peca = 1;
    } //cavalo=2
    linha = floor(cavalo/8);
    coluna = cavalo-(8*linha) - 1;
    tabuleiro[linha][coluna].peca = 2;
}

void atualiza(int posicoes[], int cavalo, int cnovo, int novapos[]){ //atualiza a posicao do cavalo e peoes
    linha = floor(cavalo/8); //mexendo o cavalo
    coluna = cavalo-(8*linha) - 1;
    tabuleiro[linha][coluna].peca = 0;
    linha = floor(cnovo/8);
    coluna = cnovo-(8*linha) - 1;
    tabuleiro[linha][coluna].peca = 2;
    for(i=0; i<m;i++){ 
        linha = floor(posicoes[i]/8);
        coluna = posicoes[i]-(8*linha) - 1;
        if(tabuleiro[linha][coluna].peca!=2){
            tabuleiro[linha][coluna].peca = 0; //posicao antiga
        }
        if(tabuleiro[linha][coluna].peca==2){
            novapos[i]=0;//foi comido pelo cavalo
        }
    }
    for(i=0; i<m;i++){ //adicionando os peoes=1 e atualizando vetor original de posicoes
        if(novapos[i]!=0){
            posicoes[i]=novapos[i];
            linha = floor(novapos[i]/8);
            coluna = novapos[i]-(8*linha) - 1;
            tabuleiro[linha][coluna].peca = 1; //posicao nova
        }
    }
}

void posicoes_cavalo(int posc){//gera as posicoes possiveis do cavalo dada a posicao q ele se encontra
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
            linha = floor(temp[i]/8);
            coluna = temp[i]-(8*linha) - 1;
            if(tabuleiro[linha-1][coluna].peca==1){//peao come na proxima jogada, n eh uma posicao viavel
                continue;
            }
            else{
                move_cavalo[j]=temp[i];//adicionando ao vetor as posicoes do cavalo
                j++;
            }
        }
        maxcav = j;
    }
}

void mexer_pecas(int p[], int cavalo, int cnovo){ //da as posições anterior, adiciona 8 na posicao
    int novo[m];
    for(i=0;i<m;i++){
        novo[i]=p[i]+8;
    }
    atualiza(p, cavalo, cnovo, novo);
}

int checa_peao(){
    for(i=0; i<8;i++){ //posicoes 1-64 do tabuleiro
        for(int j=0; j<8; j++){
            if(tabuleiro[i][j].peca==1){
                return 1; //ainda tem peao
            }
        }
    }
    return 0; //nao tem peao no tabuleiro
}

int checa_impossivel(){
    int p0=0, p1=0, p2=0, p3=0, p4=0, p5=0, p6=0, p7=0, pt=0;
    for(j=0;j<8;j++){
        if(tabuleiro[6][j].peca==1 && tabuleiro[5][j].peca==1){
            return 1; //jogo impossível
        }
        if(tabuleiro[0][j].peca == 1){
            p0++;//contando quantos peoes tem na linha 0
            pt++;
        }
        if(tabuleiro[1][j].peca == 1){
            p1++;//contando quantos peoes tem na linha 1
            pt++;
        }
        if(tabuleiro[2][j].peca == 1){
            p2++;//contando quantos peoes tem na linha 2
            pt++;
        }
        if(tabuleiro[3][j].peca == 1){
            p3++;//contando quantos peoes tem na linha 3
            pt++;
        }
        if(tabuleiro[4][j].peca == 1){
            p4++;//contando quantos peoes tem na linha 4
            pt++;
        }
        if(tabuleiro[5][j].peca == 1){
            p5++;//contando quantos peoes tem na linha 5
            pt++;
        }
        if(tabuleiro[6][j].peca == 1){
            p6++;//contando quantos peoes tem na linha 6
            pt++;
        }
        if(tabuleiro[7][j].peca==1){
            p7++; //contando quantos peoes tem na linha 7
            pt++;
        }
        if(p6>=2 || p5>=3 || p4>=4 || p3>=5 || p2>=6 || p1>=7 || p0==8 || pt==8){
            return 1; //jogo perdido, impossivel de ganhar
        }
        if(p7>0 && c<41){
            return 1;
        }
    }
    return 0; //jogo ainda tem chances de ganhar
}

int backtracking(int vetor_depeos[], int cavalo, int atual){
    int imp = checa_impossivel();
    int pe=checa_peao();
    if(imp==1){
        return 8; //impossivel
    }
    if(atual>=count){
        return 8; //maior q a outra jogada, descartada
    }
    if(pe==0){
        return atual;
    }
    posicoes_cavalo(cavalo);
    for(i=0;i<8;i++){
        mexer_pecas(vetor_depeos, cavalo, move_cavalo[i]);
        int resultado = backtracking(vetor_depeos, move_cavalo[i], atual+1);
        if(resultado<count){
            count = resultado;
        }
    }
    return count;
}

void imprimi(){
    printf("\nPeças");
    for(i=0; i<8;i++){ 
        printf("\n");
        for(int j=0; j<8; j++){
            printf("%d ", tabuleiro[i][j].peca);
        }
    }
}

int main(){
    scanf("%d", &m);
    int posicoes[m];
    for(i=0; i<m; i++){
        scanf("%d", &posicoes[i]);
    }
    scanf("%d", &c);
    inicia_tabuleiro(posicoes, c, m);
    int final = backtracking(posicoes, c, atual);
    if(final==8){
        printf("impossible");
    }
    if(final!=8){
        printf("%d", final);
    }
    return 0;
}