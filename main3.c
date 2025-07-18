# include <stdio.h>
# include <stdlib.h>

struct Ponto{
    int coordenada;
};

typedef struct Ponto ponto;

struct Aresta {
    ponto p1;
    ponto p2;
};

typedef struct Aresta aresta;

ponto maiorVigilante ( ponto * pontos, int numPontos, aresta *arestas, int numArestas){ 
    int contador, maior = 0;
    ponto maiorPonto;
    for ( int i = 0; i < numPontos; i++){ 
        contador = 0;        
        for ( int j = 0; j < numArestas; j++){
            if ( pontos[i].coordenada == arestas[j].p1.coordenada || pontos[i].coordenada == arestas[j].p2.coordenada){
                contador ++;
            }
        }
        if ( contador > maior ){
            maior = contador;
            maiorPonto = pontos[i];
        }
    }
    return maiorPonto;
}

int temMaiorVigilante (ponto p1, aresta a1){
    return ( p1.coordenada == a1.p1.coordenada || p1.coordenada == a1.p2.coordenada);
}

int quantasMaiorVigilanteOlhando(ponto p1, aresta *arestas, int numArestas){
    int contador = 0;
    for ( int i = 0; i < numArestas; i++){
        contador += temMaiorVigilante(p1, arestas[i]);
    }
    return contador;
}

void eliminarRuasVigiadas(ponto p1, aresta *arestas, int *numArestas){ 
    int j = 0;
    for ( int i = 0; i < *numArestas; i++ ){
        if ( !temMaiorVigilante( p1, arestas[i])){
            arestas[j++] = arestas [i];            
        }
    }
    *numArestas = j;
}

void analisarCameras (ponto *pontos, int *numPontos, aresta *arestas, int numArestas){
    int k = 0;
    for ( int i = 0; i < *numPontos; i++ ){
        for ( int j = 0; j < numArestas; j++){
            if ( pontos[i].coordenada == arestas[j].p1.coordenada || pontos[i].coordenada == arestas[j].p2.coordenada){
                pontos[k++] = pontos[i];
                break;
            }
        }
    }
    *numPontos = k;
}

void addCamera(ponto **cameras, ponto a, int *tamAtual) {
    (*tamAtual)++;
    ponto *temp = realloc(*cameras, (*tamAtual) * sizeof(ponto)); 

    if (temp == NULL) {
        printf("Erro ao realocar memoria\n");
    }

    *cameras = temp;
    (*cameras)[(*tamAtual) - 1] = a; 
}

void exibirResultados (FILE *ptr, ponto *pontos, int tamPontos){

    int static i = 0;   

    if ( i == tamPontos){
        i = 0;
        fprintf (ptr, "Foram necesarias %d cameras\n\n", tamPontos);
    } else {
        fprintf(ptr, "Camera coordenada: %d\n", pontos[i].coordenada);
        i++;
        exibirResultados (ptr, pontos, tamPontos);
    }
}


int main (int argc, char *argv[]){

    const char *arquivo = argv[1];

    int numRuas, numCamera;
    FILE *ptr;

    if ( (ptr = fopen(arquivo, "r")) == NULL){ 
        printf ("Arquivo não pode ser aberto");
        return 0;
    } else {
        fscanf(ptr, "%d %d", &numCamera, &numRuas); 
    }

    ponto *cameras = (ponto *) malloc ( numCamera * sizeof (ponto));
    aresta *ruasVigiadas = (aresta*) malloc ( numRuas * sizeof(aresta));

    for ( int i = 0; i < numCamera; i++){
        cameras[i].coordenada = i;
    }

    for ( int i = 0; i < numRuas; i++){
        fscanf (ptr, "%d %d", &ruasVigiadas[i].p1.coordenada, &ruasVigiadas[i].p2.coordenada);
    }

    fclose(ptr);

    ponto *resposta = NULL; 
    int totalCameras = 0;   

    while ( numRuas != 0 ){
        ponto a = maiorVigilante( cameras, numCamera, ruasVigiadas, numRuas);

        addCamera(&resposta, a, &totalCameras);

        eliminarRuasVigiadas(a, ruasVigiadas, &numRuas);

        analisarCameras(cameras, &numCamera, ruasVigiadas, numRuas);
    }

    FILE *ptr2;

    ptr2 = fopen("saida.txt", "a+");

    if (ptr2 == NULL) {
    printf("Erro ao abrir arquivo de saida\n");
    return 1;
    }

    exibirResultados(ptr2, resposta, totalCameras);

    fclose(ptr2);

    free(cameras);
    free(ruasVigiadas);
    free(resposta);

    return 0;
}
