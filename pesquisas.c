#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/*Função para contar o número de linhas de um arquivo.*/
int conta_linhas (FILE *arq) {
   int linhas = 0;
   if (arq == NULL) {
      return linhas; 
   }
   while (!feof(arq)) {
      char c;
      fscanf(arq, "%c", &c);
      if (c == '\n') {
      linhas++;
      }
   }
   rewind(arq);
   return (linhas-1);
}

/*Busca sequêncial (linear).*/
int busca_linear (char **dicionario, int linhas, char palavra[]) {

   for (int i = 0; i < linhas; i++) 
      if (strcmp(dicionario[i], palavra) == 0) {
         return i;}

   return (-1);
}

/*Busca binária iterativa.*/
int busca_binaria_itr (char **dicionario, int linhas, char palavra[]) {

   int min, max, meio;
   min = 0; max = linhas - 1;

   while (min <= max) {
      meio = (min + max)/2;

      if(strcmp(palavra, dicionario[meio]) == 0) {return meio;}
      else if (strcmp(palavra, dicionario[meio]) < 0) {
         max = meio - 1;
      }
      else // (strcmp(palavra, dicionario[meio] > 0))
         min = meio + 1;
   }

   return (-1);
}

/*Busca binária recursiva.*/
int busca_binaria_rec (char **dicionario, int esq, int dir, char palavra[]) {

   int meio;

   if (esq <= dir) {
   meio = (esq + dir) / 2;
   if (strcmp(palavra, dicionario[meio]) == 0) {return meio;}
   else if (strcmp(palavra, dicionario[meio]) < 0) 
      busca_binaria_rec(dicionario, esq, meio-1, palavra);
   else //(strcmp(palavra, dicionario[meio]) > 0)
      busca_binaria_rec(dicionario, meio+1, dir, palavra);
   }
   else {return (-1);}
}

/*Função principal.*/
int main (int argc, char *argv[]) {

   int nbuscas = 40000;

   int p;

   clock_t start, end;

   double elapsed_time;

   /*Abrindo o arquivo:*/
   FILE *arq = fopen("palavras.txt","r");

   /*Contando o número de linhas do arquivo:*/
   int linhas = conta_linhas(arq);
   
   /*Alocando memória para armazenar as palavras e p/ vetor auxiliar:*/
   char **dicionario = (char **)malloc(linhas * sizeof(char *));
   int i;
   for (i = 0; i < linhas; i++) {
      dicionario[i] = (char *)malloc(256 * sizeof(char));
   }

   /*Lendo as dicionario do arquivo:*/
   i = 0;
   while (!feof(arq)) {
      fscanf(arq, "%s", dicionario[i]);     
      i++;
   }

   /*Lendo a palavra a ser pesquisada:*/

   printf("Este programa pesquisara palavras no dicionario das seguintes formas: \n");
   printf("1) Busca Sequencial/Linear \n2) Pesquisa Binaria (Iterativa)\n3) Pesquisa Binaria (Recursiva)\n\n");
   
   printf("Pesquise uma palavra:\n>>> ");
   char palavra[256]; 
   scanf("%s", palavra);

   p = busca_binaria_rec (dicionario, 0, linhas-1, palavra);
   if (p != -1){
      printf("Achei a palavra %s no dicionario na posicao %d!\n\n", palavra, p);
   }
   else {
      printf("Nao achei a palavra %s no dicionario!\n\n", palavra);
   }

   start = clock();
   p = busca_linear (dicionario, linhas, palavra);
   end = clock();
   elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
   printf("Tempo da Busca Sequencial / Linear: %.3fs\n", elapsed_time);

   start = clock();
   p = busca_binaria_itr (dicionario, linhas, palavra);
   end = clock();
   elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
   printf("Tempo da Busca Binaria (Iterativa): %.3fs\n", elapsed_time);

   start = clock();
   p = busca_binaria_rec (dicionario, 0, linhas-1, palavra);
   end = clock();
   elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
   printf("Tempo da Busca Binaria (Recursiva): %.3fs\n", elapsed_time);

   printf("\n");

   printf("A seguir, serao pesquisadas 4 palavras 10.000 vezes (40.000 palavras) no dicionario...\n");

   /*Executando os algoritmos busca sequêncial:*/
   start = clock();
   for (i = 0; i < nbuscas; i++){

      if ((i%4) == 1) {strcpy (palavra, "ACADEMICO");}
      else if ((i%4) == 2) {strcpy (palavra, "FORNECEDOR");}
      else if ((i%4) == 3) {strcpy (palavra, "RODRIGO");}
      else {strcpy (palavra, "ZOOLOGIA");}

      p = busca_linear (dicionario, linhas, palavra);
      /*
      if (p != -1){
         printf("Achei a palavra %s no dicionario na posicao %d!\n\n", palavra, p);
      }
      else {
         printf("Nao achei a palavra %s no dicionario!\n\n", palavra);
      }
      */
   }   

   end = clock();
   elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
   printf("Tempo da Busca Sequencial / Linear: %.3fs\n", elapsed_time);
   /*------------------------------------------------*/
   /*Executando os algoritmo busca binária iterativo:*/
   start = clock();
   for (i = 0; i < nbuscas; i++){

      if ((i%4) == 1) {strcpy (palavra, "ACADEMICO");}
      else if ((i%4) == 2) {strcpy (palavra, "FORNECEDOR");}
      else if ((i%4) == 3) {strcpy (palavra, "RODRIGO");}
      else {strcpy (palavra, "ZOOLOGIA");}
      
      p = busca_binaria_itr (dicionario, linhas, palavra);
      /*
      if (p != -1){
         printf("Achei a palavra %s no dicionario na posicao %d!\n\n", palavra, p);
      }
      else {
         printf("Nao achei a palavra %s no dicionario!\n\n", palavra);
      }
      */
   }  
   end = clock();
   elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
   printf("Tempo da Busca Binaria (Iterativa): %.3fs\n", elapsed_time);
   /*------------------------------------------------*/
   /*Executando o algoritmo de busca binária recursivo:*/
   start = clock();
   for (i = 0; i < nbuscas; i++){

      if ((i%4) == 1) {strcpy (palavra, "ACADEMICO");}
      else if ((i%4) == 2) {strcpy (palavra, "FORNECEDOR");}
      else if ((i%4) == 3) {strcpy (palavra, "RODRIGO");} //ERRADO!
      else {strcpy (palavra, "ZOOLOGIA");}

      p = busca_binaria_rec (dicionario, 0, linhas-1, palavra);
      /*
      if (p != -1){
         printf("Achei a palavra %s no dicionario na posicao %d!\n\n", palavra, p);
      }
      else {
         printf("Nao achei a palavra %s no dicionario!\n\n", palavra);
      }
      */
   }   
   end = clock ();
   elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
   printf("Tempo da Busca Binaria (Recursiva): %.3fs\n\n", elapsed_time);
   /*------------------------------------------------*/

   /*Liberando a memória:*/
   for (i = 0; i < linhas; i++) {
      free(dicionario[i]);
   }
   free(dicionario);
   fclose(arq);
   return 0;
}

