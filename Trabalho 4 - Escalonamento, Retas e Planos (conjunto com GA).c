#include <stdio.h>
#include <stdlib.h>

    /*
    --------------------------------------------------------------------------------------
    Programa feito por Victor Graciano de Souza Correia 10431201 ICMC-USP São Carlos 2018.
    --------------------------------------------------------------------------------------
    */

//Struct que será utilizada como base de informações de cada elemento da matriz, sendo compostas cada elemento por um numerador
// inteiro (num) e um denominador inteiro (den).
typedef struct{
    int num;
    int den;
}coeficientes;

//Função que alocará dinamicamente a matriz que será usada na main para o escalonamento
coeficientes** AlocaMat(int n, int m){
    int i;
    coeficientes **mat = (coeficientes**)calloc(n,sizeof(coeficientes*));
    for (i = 0; i < n; i++){
       mat[i] = (coeficientes*) calloc(m,sizeof(coeficientes));
    }
    return mat;
}
//Função para desalocar a matriz do programa.
void DesalocaMat(coeficientes** mat, int n){
    int i;
    for (i=0; i < n;i++){
        free(mat[i]);
    }
    free(mat);
}
//Função para trocar a linha cujo primeiro elemento é zero com outra linha cujo o primeiro elemento não é zero da matriz
//a ser escalonada.
void swap(coeficientes **mat, int i, int destino){
    coeficientes *aux=mat[destino];
    mat[destino]=mat[i];
    mat[i]=aux;
}
//Função para determinar o maior número entre dois números
int maior(int a, int b){
    if(a>=b){
        return a;
    }else{
        return b;
    }
}
//Função para calcular o mmc (Mínimo Múltiplo Comum) entre dois números.
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
//Função que efetua o escalonamento da matriz, uma das funções mais importantes do programa.
void escalonamento(coeficientes **mat, int linha, int coluna, int cont){
    //Condição de parada da recursão da função.
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
    //Estrutura dentro da função escalonamento a qual faz todos os cálculos para a geração da nova matriz escalonada.
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
    //Parte da função que chama ela mesma (Recursão).
    escalonamento(mat, linha, coluna, cont);
}

int main(int argc, char* argv[]){

    //Declaração de Linhas e Colunas e Variáveis que serão usadas em FORs.
    int n, m, i, j, k;
    scanf("%d", &n);
    scanf(" %d[^\n]", &m);

    //Alocação da matriz a ser escalonada.
    coeficientes **mat = AlocaMat(n, m);

    //Parta do programa que lê o tipo de entrada, sendo "r" uma reta com 2 equações e "p" um plano com 1 equação.
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
    //Estrutura para realizar a troca de linha da matriz se necessário.
    if(mat[0][0].num!=0){
        for(i=0; i<n; i++){
            if(mat[i][0].num!=0){
            swap(mat, i, 0);
            break;
            }
        }
    }

    //Chamada da função que realizará o escalanomento da matriz
    escalonamento(mat, n, m, 0);

    //Após o escalonamento realizado, a estrutura a seguir atribui a variável colisão se houve colisão ou não entre os elementos
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

    //Parte do programa que imprimirá na tela sim caso houve colisão e não caso não houve colisão, calculado
    //na estrutura anterior.
    if(colisao==0){
        printf("sim\n");
    }else if(colisao==1){
        printf("nao\n");
    }

    //Print da matriz escalonada com espaçamento simples (\t).
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
    //Desalocação da matriz escalonada.
    DesalocaMat(mat, n);
    return 0;
    //Fim do programa.
}
