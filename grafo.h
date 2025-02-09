typedef struct grafo Grafo;

// aqui basicamente criamos nosso grafo

struct  grafo
{
    int eh_ponderado;

    int n_vertices;

    int grau_max;

    int **arestas;

    float ** pesos;

    int *grau;

};

// aqui vamos criar um ponteiro para o nosso grafo

Grafo *cria_grafo (int n_vertices, int grau_max, int eh_ponderado) {
    // vamos alocar memória para esse ponteiro poder apontar

    // obs não entendi bem pqq o sizeof é do tamanho do grafo, mas bora ne
    Grafo *gr = (Grafo*) malloc (sizeof (Grafo));
    // quer dizer que o ponteiro foi criado com sucesso ( a afirmativa a baixo )
        if (gr != NULL) {
            gr -> n_vertices = n_vertices;
            gr -> grau_max = grau_max;
            gr -> eh_ponderado = (eh_ponderado != 0) ? 1 : 0;
            gr -> grau = (int *) calloc (n_vertices, sizeof(int) );
            gr -> arestas = (int **) malloc (n_vertices * sizeof (int*));
            for (int i = 0; i < n_vertices; i ++) {
                gr -> arestas[i] = (int*) malloc (n_vertices * sizeof (int));
                if (gr -> eh_ponderado) {
                    gr-> pesos = (float**) malloc (n_vertices* sizeof (float*));

                    for (int i = 0; i < n_vertices; i ++) {
                        gr-> pesos [i] = (float *) malloc (n_vertices * sizeof (float));
                    }
                }
            }
        }
        
        return gr;
    }

void libera_grafo (Grafo *gr) {
    int i; 
    if (gr != NULL) {
        for (i = 0; i < gr -> n_vertices; i ++ ) {
            free (gr ->arestas[i]);
        }
        free (gr -> arestas);

    if (gr -> eh_ponderado) {
        for (i = 0; i < gr -> n_vertices; i ++) {
            free (gr-> pesos [i]);
        }
        free (gr->pesos);
    }
    free (gr-> grau);
    free (gr);
    }
}


int insere_aresta (Grafo * gr, int orig, int dest, int eh_digrafo, float peso) {
    if (gr == NULL) {
        return 0;
    }
    if (orig < 0 || orig >= gr -> n_vertices)
        return 0;
    if (dest < 0 || dest >= gr -> n_vertices)
        return 0;

    gr -> arestas[orig][gr->grau[orig]] = dest;

    gr -> grau[orig] ++;

    if (eh_digrafo == 0) {
        insere_aresta (gr, dest, orig, 1, peso);
    }
    return 1;
}

int remove_aresta (Grafo * gr, int orig, int dest, int eh_digrafo) {
    if (gr == NULL) 
       return 0;
    if (orig < 0 || orig >= gr -> n_vertices)
        return 0;
    if (dest < 0 || dest >= gr -> n_vertices)
        return 0;
    
        
        int i = 0;
        
        while (i < gr->grau[orig] && gr->arestas[orig][i] != dest) 
        i ++;

        if (i == gr -> grau [orig]) 
        return 0;

    gr-> grau[orig] --;
    gr -> arestas[orig][i] = gr -> arestas[orig][gr-> grau[orig]];
    if (gr->eh_ponderado)
      gr->pesos[orig][i] = gr -> pesos[orig][gr->grau[orig]];

    if (eh_digrafo == 0)
    remove_aresta ( gr, orig, dest, 1);

    return 1;   
    
}