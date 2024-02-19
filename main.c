//Trabalho final de Estruturas de Dados - INF01203
//Larissa Furtado Helfer (577752) e Luiz de Ramos(580136)
//Turma A - Professora Viviane Moreira
//Analisador de calorias

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "abp.h"        //TADS fornecidas pela professora
#include "avl.h"
#define maxLinha 500    //tamanho max pra linha lida no arquivo

int compAvl = 0;        //vaiaveis globais de comparações
int compAbp = 0;

int main(int argc, char *argv[]){
    NodoAvl *avl = inicializaAvl();         
    NodoAbp *abp = inicializaAbp();
    NodoAbp *abpData;
    char nome[maxnome] /*nome de alimento lido*/, buffer[maxLinha],/*buffer que armazena linha lida do arquivo*/ *token/*guarda informacao separada por ";" temporariamente*/;
    int caloria, ok/*necessasrio pra funcoes da avl*/, i, gramas, totalLinha;
    int calTotal = 0;   //calorias consumidas no dia
    int rot = 0; //total de rotacoes da avl
    FILE *in1;  //arquivos de entrada e saida
    FILE *in2;
    FILE *out;

    //setLocale(LC_ALL,"");
    
    if(argc != 4){      //verifica quantidade de parametros informados pelo usuario
        printf("Número incorreto de parâmetros.\n");
        return 1;
    }
    else{
        in1 = fopen(argv[1],"r");       //abre arquivo de entrada com dados
        if(!in1){
            printf("Erro na abertura do arquivo de dados.\n");
            return 1;
        }
        else{
            while(fgets(buffer, maxLinha, in1)){    //enquanto houverem linhas não nulas, pega a linha e processa os dados dela
                
                token = strtok(buffer,";");         //informacoes separadas por ";" separadas com strtok
                strcpy(nome,token);

                for(i = 0; i < (int)strlen(nome); i++){        //pega o primeiro token, que é o nome do alimento, e faz um toupper de todos seus caracteres, tornando o programa case insensitive
                    nome[i] = (char)toupper(nome[i]);
                }

                token = strtok(NULL,"\n");
                caloria = (int)atoi(token);                     //pega o proximo token, as calorias, e realiza um atoi(ele é pego como string)

                if(nome != NULL){                  //Apenas insere as informações nas arvores se conseguiu pegar o nome. 
                    avl = InsereAvl(avl,&ok,&rot,caloria,nome);
                    abp = insereAbp(abp, caloria, nome);
                }
            }
            printf("Arquivo %s processado.\n",argv[1]);
        }
    }
    fclose(in1);

    //Analise de calorias ingeridas no dia, e criacao de relatorio:

    in2 = fopen(argv[2],"r");       //abre arquivos de ingestao diaria de calorias e saida
    out = fopen(argv[3],"w");

    if(in2 == NULL){            //verifica se ambos foram abertos corretamente
        printf("Erro ao abrir arquivo de calorias ingeridas.\n");
        return 1;
    }
    if(out == NULL){
        printf("Erro ao abrir o arquivo de saida.\n");
        return 1;
    }

    fprintf(out,"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
    fprintf(out,"Calorias calculadas para %s usando a tabela %s:\n\n",argv[2],argv[1]);

    while(fgets(buffer, maxLinha, in2)){
                                                //escreve as informacoes no arquivo de saida, analisando as informacoes do arquivo de entrada linha a linha
                token = strtok(buffer,";");
                strcpy(nome,token);

                for(i = 0; i < (int)strlen(nome); i++){
                    nome[i] = (char)toupper(nome[i]);       //faz praticamente a mesma coisa que com o arquivo de dados, exceto que busca os alimentos nas arvores em vez de inseri-los
                }

                token = strtok(NULL,"\n");
                gramas = (int)atoi(token); 

                if(nome != NULL){
                    consultaAvl(avl,nome);          
                    abpData = consultaAbp(abp,nome);    //apenas as informacoes retornadas por consultaAbp sao usadas. ConsultaAvl ainda e chamada para atualizar valores de comparacoes e rotacoes

                    if(abpData){        //so prossegue se a informacao pega nao for nula
                        totalLinha = ((abpData->cal)*gramas)/100;       //atualiza a quantidade de calorias daquela linha
                        calTotal += totalLinha;                         //acumula calorias totais

                        fprintf(out,"%dg de %s (%d kcal por 100g) = %d kcal\n",gramas,nome,abpData->cal,totalLinha);
                    }
 
                }
        }
        fprintf(out,"\nCalorias totais ingeridas no dia: %d kcal\n",calTotal);

        fprintf(out,"\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

        //Estatisticas das estruturas de dados:

        fprintf(out,"-------------------ESTATISTICAS ABP-------------------\n");
        fprintf(out,"Numero de nodos: %d\n",contaNodo(abp));
        fprintf(out,"Altura: %d\n",alturaAbp(abp));
        fprintf(out,"Rotacoes: 0\n");
        fprintf(out,"Comparacoes: %d\n",compAbp);
        fprintf(out,"------------------------------------------------------\n\n");

        fprintf(out,"-------------------ESTATISTICAS AVL-------------------\n");
        fprintf(out,"Numero de nodos: %d\n",contaNodo(abp));
        fprintf(out,"Altura: %d\n",alturaAvl(avl));
        fprintf(out,"Rotacoes: %d\n",rot);
        fprintf(out,"Comparacoes: %d\n",compAvl);
        fprintf(out,"------------------------------------------------------\n\n");


        printf("Arquivo de saida %s criado.\n",argv[3]);

        fclose(out);
        fclose(in2);

        return 0;
}