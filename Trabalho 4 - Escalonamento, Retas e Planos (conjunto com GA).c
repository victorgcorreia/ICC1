#include <stdio.h>
#include <stdlib.h>

    /*
    --------------------------------------------------------------------------------------
    Programa feito por Victor Graciano de Souza Correia 10431201 ICMC-USP S�o Carlos 2018.
    --------------------------------------------------------------------------------------
    */

//Struct que ser� utilizada como base de informa��es de cada elemento da matriz, sendo compostas cada elemento por um numerador
// inteiro (num) e um denominador inteiro (den).
typedef struct{
    int num;
    int den;
}coeficientes;

//Fun��o que alocar� dinamicamente a matriz que ser� usada na main para o escalonamento
coeficientes** AlocaMat(int n, int m){
    int i;
    coeficientes **mat = (coeficientes**)calloc(n,sizeof(coeficientes*));
    for (i = 0; i < n; i++){
       mat[i] = (coeficientes*) calloc(m,sizeof(coeficientes));
    }
    return mat;
}
//Fun��o para desalocar a matriz do programa.
void DesalocaMat(coeficientes** mat, int n){
    int i;
    for (i=0; i < n;i++){
        free(mat[i]);
    }
    free(mat);
}
//Fun��o para trocar a linha cujo primeiro elemento � zero com outra linha cujo o primeiro elemento n�o � zero da matriz
//a ser escalonada.
void swap(coeficientes **mat, int i, int destino){
    coeficientes *aux=mat[destino];
    mat[destino]=mat[i];
    mat[i]=aux;
}
//Fun��o para determinar o maior n�mero entre dois n�meros
int maior(int a, int b){
    if(a>=b){
        return a;
    }else{
        return b;
    }
}
//Fun��o para calcular o mmc (M�nimo M�ltiplo Comum) entre dois n�meros.
int mmc(int a, int b){
    int bigger = maior(a, b);
    if(a==0 || b==0){
        return 0;
    }
    if(bigger==a && a%b==0){
        return a;
    }else if(bigger==b && b%a==0){
        return b;
    }else{
        return a*b;
    }
}
//Fun��o que efetua o escalonamento da matriz, uma das fun��es mais importantes do programa.
void escalonamento(coeficientes **mat, int linha, int coluna, int cont){
    //Condi��o de parada da recurs�o da fun��o.
    if(cont==linha-1){
        return;
    }
    //Estrutura de troca de linha
    int k;
    if(mat[cont][cont].num==0){
        for(k=cont+1; k<linha; k++){
            if(mat[k][cont].num!=0){
                swap(mat, k, cont);
                break;
            }
        }
    }
    //Estrutura dentro da fun��o escalonamento a qual faz todos os c�lculos para a gera��o da nova matriz escalonada.
    int i, j, aux, var;
    coeficientes linhapivo;
    for(i=cont+1; i<linha; i++){
            linhapivo = mat[i][cont];
        for(j=cont; j<coluna; j++){
            var =(mat[cont][j].den)*(linhapivo.den)*(mat[cont][cont].num);
            aux = mmc(mat[i][j].den, var);
            mat[i][j].num = (aux/mat[i][j].den)*(mat[i][j].num) - (aux/var)*(mat[cont][j].num*(linhapivo.num*mat[cont][cont].den));
            mat[i][j].den = aux;
        }
    }
    cont++;
    //Parte da fun��o que chama ela mesma (Recurs�o).
    escalonamento(mat, linha, coluna, cont);
}

int main(int argc, char* argv[]){

    //Declara��o de Linhas e Colunas e Vari�veis que ser�o usadas em FORs.
    int n, m, i, j, k;
    scanf("%d", &n);
    scanf(" %d[^\n]", &m);

    //Aloca��o da matriz a ser escalonada.
    coeficientes **mat = AlocaMat(n, m);

    //Parta do programa que l� o tipo de entrada, sendo "r" uma reta com 2 equa��es e "p" um plano com 1 equa��o.
    char char1;
    int cont=0, aux = cont;
    for(i=0; i<2; i++){
        scanf(" %c[^\n]", &char1 );
        if(char1 == 'r'){
            for(j=aux; j<aux+2; j++){
                for(k=0; k<m; k++){
                    scanf(" %d %d[^\n]", &mat[j][k].num, &mat[j][k].den);
                }
                cont++;
            }
            aux = cont;
        }
        if(char1 =='p'){
            for(k=0; k<m; k++){
                scanf(" %d %d[^\n] ", &mat[aux][k].num, &mat[aux][k].den);
            }
            aux++;
        }
    }
    //Estrutura para realizar a troca de linha da matriz se necess�rio.
    if(mat[0][0].num!=0){
        for(i=0; i<n; i++){
            if(mat[i][0].num!=0){
            swap(mat, i, 0);
            break;
            }
        }
    }

    //Chamada da fun��o que realizar� o escalanomento da matriz
    escalonamento(mat, n, m, 0);

    //Ap�s o escalonamento realizado, a estrutura a seguir atribui a vari�vel colis�o se houve colis�o ou n�o entre os elementos
    //da matriz.
    int zeros=0, colisao=0;
    for(i=0; i<n; i++){
        for(j=0; j<m-1; j++){
            if(mat[i][j].num==0){
                zeros++;
            }
            if(zeros==m-1 && mat[i][m-1].num!=0){
                colisao=1;
            }else{
                colisao=0;
            }
        }
        zeros=0;
    }

    //Parte do programa que imprimir� na tela sim caso houve colis�o e n�o caso n�o houve colis�o, calculado
    //na estrutura anterior.
    if(colisao==0){
        printf("sim\n");
    }else if(colisao==1){
        printf("nao\n");
    }

    //Print da matriz escalonada com espa�amento simples (\t).
    for(j=0; j<n; j++){
        for(k=0; k<m; k++){
            if(mat[j][k].num%mat[j][k].den==0){
                    printf("%d", mat[j][k].num/mat[j][k].den);
                }else{
                    printf("%d/%d", mat[j][k].num, mat[j][k].den);
                }
            if(k!=m-1){
                printf("\t");
            }
        }
    printf("\n");
}
    //Desaloca��o da matriz escalonada.
    DesalocaMat(mat, n);
    return 0;
    //Fim do programa.
}
