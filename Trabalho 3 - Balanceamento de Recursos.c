#include <stdio.h>
#include <stdlib.h>

    /*
    --------------------------------------------------------------------------------------
    Programa feito por Victor Graciano de Souza Correia 10431201 ICMC-USP São Carlos 2018.
    --------------------------------------------------------------------------------------
    */

//Função Flood Fill que será usada para calcular o valor de exploração no decorrer do programa
//tem como argumentos a linha e coluna do jogador, a matriz mapa, a linha e coluna do recurso e
//um flag de controle do flood fill respectivamente
void ff(int pos1l, int pos1c, int map[9][9], int posReclin, int posReccol, int* (flag)){
    if(pos1l==posReclin && pos1c==posReccol){
        *flag=1;
    }
    if (*flag){
        return;
    }
    if(pos1l<0 || pos1c<0 || pos1l>=9 || pos1c>=9 || map[pos1l][pos1c]==1 || map[pos1l][pos1c]==9){
        return;
    }else{
        //Trocando os pontos por onde o player passou até chegar ao recurso por 9
        map[pos1l][pos1c]=9;
        //Sul
        ff(pos1l+1, pos1c, map, posReclin, posReccol, flag);
        //Norte
        ff(pos1l-1, pos1c, map, posReclin, posReccol, flag);
        //Oeste
        ff(pos1l, pos1c-1, map, posReclin, posReccol, flag);
        //Leste
        ff(pos1l, pos1c+1, map, posReclin, posReccol, flag);
    }
}


int main(int argc, char* argv[]){
    //Declarando variáveis de controle que serão usadas em futuros FORs
    int i, j, k;
    //Declarando a matriz que será usada de mapa
    int map[9][9];
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            //Passando ao programa os componentes de matriz mapa
            scanf("%d", &map[i][j]);
        }
    }
    //Estrutura For utilizada para calcular o P da fórmula para o valor de exploração
    //No caso, P é a quantidade de células transponíveis na matriz mapa
    int P=0;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            if(map[i][j]==0){
                P++;
            }
        }
    }
    //Declarando e obtendo os valores das posições de linha e coluna do player1 e do player2 respectivamente
    int pos1L, pos1C, pos2L, pos2C;
    scanf("%d", &pos1L);
    scanf("%d", &pos1C);
    scanf("%d", &pos2L);
    scanf("%d", &pos2C);
    //Declarando e obtendo o valor que armazena o numero de recursos dispponíveis no mapa
    int nRec;
    scanf("%d", &nRec);
    //Alocando dinânimicamente e lendo os valores de 2 vetores de inteiros para armazenar a linha e
    //a coluna de cada recurso respectivamente
    int* posReclin = (int*) malloc(nRec*sizeof(int));
    int* posReccol = (int*) malloc(nRec*sizeof(int));
    for(i=0; i<nRec; i++){
        scanf("%d", &posReclin[i]);
        scanf("%d", &posReccol[i]);
    }
    //Declarando as flags de controle do flood fill
    int flag1 = 0, flag2 = 0;
    //Declarando vetores de tamanho nRec que armazenaram os Ei->j do player1 e player2 respectivamente
    double x1[nRec], x2[nRec];
    //Parte do programa no qual é utilizada a função flood fill e é armazenado o contador divido por P em cada
    //elemento do vetor que corresponde com seu devido recurso

    //Para o player1
    for(i=0; i<nRec; i++){
        flag1 = 0;
        ff(pos1L, pos1C, map, posReclin[i], posReccol[i], &flag1);
        int count1 = 1;
        for(j=0; j<9; j++){
            for(k=0; k<9; k++){
                if(map[j][k]==9){
                    count1++;
                }
            }
        }
        x1[i]=(double)count1/P;
        for(j=0; j<9; j++){
            for(k=0; k<9; k++){
                if(map[j][k]==9){
                    map[j][k]=0;
                }
            }
        }
    }
    //Para o player2
    for(i=0; i<nRec; i++){
        flag2 = 0;
        ff(pos2L, pos2C, map, posReclin[i], posReccol[i], &flag2);
        int count2 = 1;
        for(j=0; j<9; j++){
            for(k=0; k<9; k++){
                if(map[j][k]==9){
                    count2++;
                }
            }
        }
        x2[i]=(double)count2/P;
        for(j=0; j<9; j++){
            for(k=0; k<9; k++){
                if(map[j][k]==9){
                    map[j][k]=0;
                }
            }
        }
    }
    //Declarando as variáveis que armazenarão o resultado final
    double E1 = 0, E2 = 0;
    //Estrutura FOR utilizada para calcular a parte da somatoria da fórmula
    for(i=0; i<nRec; i++){
        E1 = E1 + x1[i];
        E2 = E2 + x2[i];
    }
    //Calculo final da formula da exploração de cada jogador
    E1 = E1 * (1/(double)nRec);
    E2 = E2 * (1/(double)nRec);
    //Prints de exploração de cada jogador
    printf("%lf\n", E1);
    printf("%lf\n", E2);
    //Teste em IFs para saber se o mapa é balanceado ou não
    if ((E1-E2) > -0.001 && (E1-E2) < 0.001) printf("O mapa eh balanceado\n");
    else if (E1 > E2){
         printf("O jogador 2 possui vantagem\n");
    }else {
        printf("O jogador 1 possui vantagem\n");
    }
    //Desalocando os vetores alocados dinamicamente
    free(posReclin);
    free(posReccol);
    return 0;
}
