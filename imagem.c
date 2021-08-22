#include "imagem.h"

/*Alocando a estrutura da imagem.*/
Imagem* aloca_imagem (int nlin, int ncol) {
  int i;
  Imagem *img = (Imagem *)malloc(sizeof(Imagem)); 
  img->nlin = nlin;
  img->ncol = ncol;
  img->mat = (int **)malloc(ncol * sizeof(int *));
  for (i = 0; i < ncol; i++) {
    img->mat[i] = (int *)malloc(nlin * sizeof(int)); 
  }
  return img;
}

/*Liberando estruturas da imagem.*/
void desaloca_imagem (Imagem *img) {
  int i;
  for (i = 0; i < img->ncol; i++) {
    free(img->mat[i]);
  }
  free(img->mat);
  free(img);
}

/*Descreva o algoritmo e o efeito da computação abaixo. 
O que acontece quando o tamanho da janela é aumentado? */
Imagem* Processamento (Imagem *img, int tamanho_da_janela) {
  int i, j, k, l, p;
  Imagem *saida = aloca_imagem (img->nlin, img->ncol);
  int *vect = (int *)malloc(tamanho_da_janela * tamanho_da_janela * sizeof(int));
  int *aux = (int *)malloc(tamanho_da_janela * tamanho_da_janela * sizeof(int));
  for (i = tamanho_da_janela; i < (img->ncol - tamanho_da_janela); i++) {
    for (j = tamanho_da_janela; j < (img->nlin - tamanho_da_janela); j++) {
      for (k = -tamanho_da_janela/2, p = 0; k <= +tamanho_da_janela/2; k++) {
        for (l = -tamanho_da_janela/2; l <= +tamanho_da_janela/2; l++, p++) {
          vect[p] = img->mat[i + k][j + l];            
        } 
      }
      
      /*Descomente a linha abaixo e adicione o algoritmo de ordenação Merge-Sort aqui.*/
      //MergeSort (v, vaux, 0, (tamanho_da_janela*tamanho_da_janela)-1); 
    
      /*Preenchendo a imagem de saída:*/ 
      saida->mat[i][j] = vect[(tamanho_da_janela * tamanho_da_janela)/2];
    }
  }
  free(vect); 
  free(aux); 
  return saida;
}

int main (int argc, char *argv[]) {
  /**/
  printf("Lendo a imagem: Lena.pgm\n");	
  FILE *fin  = fopen("lena.pgm", "r");
  FILE *fout = fopen("saida.pgm", "w");
  int tamanho_da_janela = 3; /*Teste com tamanhos: 3, 5, 7, 9, ... (sempre ímpar)*/

  /*Lendo a imagem:*/
  int nlin, ncol, nlevels;
  char *type = (char *)malloc(sizeof(char));
  fscanf(fin, "%s", type);   
  fscanf(fin, "%d %d %d", &ncol, &nlin, &nlevels);   
  Imagem *iimg = aloca_imagem (nlin, ncol);
  int i, j;
  for (j = 0; j < iimg->nlin; j++) {
    for (i = 0; i < iimg->ncol; i++) {
      fscanf(fin, "%d", &(iimg->mat[i][j]));
    }
  } 
  fclose(fin); 

  /*Processando a imagem:*/
  Imagem *oimg = Processamento (iimg, tamanho_da_janela);
   
  /*Gravando a imagem com o resultado do processamento:*/
  fprintf(fout, "%s\n%d %d\n%d\n", type, oimg->ncol, oimg->nlin, nlevels);
  for (j = 0; j < oimg->nlin; j++) {
    for (i = 0; i < oimg->ncol; i++) {
      fprintf(fout, "%d ", oimg->mat[i][j]);
      if ( (j != 0) && ((j % 12) == 0) ) {
        fprintf(fout, "\n");
      }
    }
  }
  fclose(fout);
  printf("Escrevendo o resultado da filtragem na imagem: saida.pgm\n");	
  desaloca_imagem (iimg); 
  desaloca_imagem (oimg); 
  return 0;
}


