# include <stdio.h>

# include <stdlib.h>

# include "grafo.h"


int main (void) {

// vou inicialmente criar um ponterio do tipo Grafo, isto, será um ponteri que aponta para o endereço de memória de um grafo e pode ter
// acesso ao seu conteúdo

Grafo *gr;

// no arquivo grafo.h criamos um ponterio para grafo que pega o numero de vertices, a quantidade max de ligações e se é ponderdo (ou seja se tem
// direção --> aqueles negócio de física);

gr = cria_grafo (5, 6, 0);

insere_aresta (gr, 1, 2, 0, 0);

insere_aresta (gr, 1, 3, 0, 0);

insere_aresta (gr, 2, 3, 0, 0);

insere_aresta (gr, 2, 4, 0, 0);

insere_aresta (gr, 3, 4, 0, 0);

insere_aresta (gr, 4, 5, 0, 0);




libera_grafo(gr);





    return 0;
}


