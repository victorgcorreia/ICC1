#include <stdio.h>
#include <math.h>
#define EPS 1e-3

    /*
    --------------------------------------------------------------------------------------
    Programa feito por Victor Graciano de Souza Correia 10431201 ICMC-USP São Carlos 2018.
    --------------------------------------------------------------------------------------
    */

//Variáveis globais que serão utilizadas ao percorrer do programa
int n, i;
double t;

//Função para calcular a similaridade entre dois usuários.
double similaridade(int p,int f,int mp[n][i]){
        int j;
        double numerador = 0.00, denominador = 0.00, similar, modulop = 0.00, modulof = 0.00;
        for (j=0 ; j<i ; j++){
            numerador += (mp[p][j]*mp[f][j]);
            modulop += pow(mp[p][j],2);
            modulof += pow(mp[f][j],2);
        }
        denominador = sqrt(modulop*modulof);
        similar = numerador/denominador;
        return similar;
}

int main(int argc, char* argv[])
{
    //Armazenando os valores das variáveis.
    scanf("%d %d %lf", &n, &i, &t);

    //Analisando se os valores armazenados são coerentes com os valores requeridos do progrma.
    if((n>=4 && n<=15) && (i>=1 && i<=15) && (t>=0.5 && t<=1.0)){

    //Declarando variáveis que vão ser usadas ao longo do programa.
    int notas[n][i], j, k, lin0[n*i], col0[n*i], tam=0;
    double vm[n];

    //Armazenando a matriz de notas a ser analisada.
    for(j=0;j<n;j++){
        for(k=0;k<i;k++){
            scanf("%d", &notas[j][k]);
        }
    }

    //Criando vetores para armazenar a linha e a coluna de cada zero da matriz de notas.
    for (j=0; j<n; j++){
        for(k=0; k<i; k++){
            if (notas[j][k]==0){
                lin0[tam] = j;
                col0[tam] = k;
                tam++;
            }
        }
    }

    //Calculando e armazenando em um vetor as médias das notas de cada usuário.
    for (j=0;j<n;j++){
        int  numerador=0, flag=0;
        for (k=0;k<i;k++){
            if (notas[j][k] != 0){
                numerador += notas[j][k];
                flag++;
            }
        }
        vm[j]= (double)numerador/(double)flag;
    }

    //Fazendo os últimos cálculos para obter a nota recomendada para o usuário
    for (j=0;j<tam;j++){
        double num = 0.00 , den = 0.00, notarecomendada = 0.00;
        for(k=0;k<n;k++){
            double similar = 0.00;
            if (lin0[j] != k) {
                similar = similaridade(lin0[j], k, notas);
                //Testando se a similaridade é menor que o limiar dado.
                if (similar<t) similar = 0.00;
            }
            if(notas[k][col0[j]] != 0){
            num += (similar*(notas[k][col0[j]]-vm[k]));
            den += similar;
            }
        }
        notarecomendada = vm[lin0[j]]+(num/den);

        if (fabs(den)<EPS){
            //Mostrando na tela DI caso haja dados insuficientes para o cálculo da nota.
            printf("DI ");
        }else{
            //Mostrando na tela a nota recomendada pelo programa ao usuário.
            printf("%.2lf ",notarecomendada);
        }

        //Quebra de linha.
        if(lin0[j]!=lin0[j+1]){
            printf("\n");
        }
    }

    //FIM

    }else{

}
    return 0;
}
