#ifndef _ex02_h_
#define _ex02_h_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Definição de uma imagem.*/
typedef struct _imagem {
  int nlin;   /*Número de linhas da imagem.*/
  int ncol;   /*Número de colunas da imagem.*/
  int **mat;  /*Matriz para armazenar os pixels.*/
} Imagem;  

Imagem* aloca_imagem (int nlin, int ncol);

void desaloca_imagem (Imagem *img);

Imagem* Processamento (Imagem *img, int tamanho_da_janela);

#endif

