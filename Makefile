all:
	gcc -o pesquisas pesquisas.c
	gcc -o imagem imagem.c
clean:
	rm pesquisas imagem saida.pgm
