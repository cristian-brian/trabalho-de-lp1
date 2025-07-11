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
    int arestasFree = quantasMaiorVigilanteOlhando(p1, arestas, *numArestas), j = 0;
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

int main (void){

    // temos 5 pontos

    ponto *cameras = (ponto *) malloc ( 5 * sizeof (ponto));

    aresta *ruasVigiadas = (aresta*) malloc ( 6 * sizeof(aresta));

    int numRuas = 6, numCamera = 5;

    for ( int i = 0; i < numCamera; i++){
        cameras[i].coordenada = i;
    }

    for ( int i = 0; i < numRuas; i++){
        printf ("Digite as coordenadas das cameras que vigiam a mesma rua --> ");
        scanf ("%d %d", &ruasVigiadas[i].p1.coordenada, &ruasVigiadas[i].p2.coordenada);
    }

    ponto *resposta = (ponto *) malloc (3 * sizeof(ponto)); // botei 3 pqq ja sei que a resposta é 3, dps ver como ajeita

    int i = 0;

    while ( numRuas != 0 ){
        ponto a = maiorVigilante( cameras, numCamera, ruasVigiadas, numRuas);

        resposta[i++] = a;

        eliminarRuasVigiadas(a, ruasVigiadas, &numRuas);

        analisarCameras(cameras, &numCamera, ruasVigiadas, numRuas);

    }

    printf("Cameras com maior vigilancia em ordem:\n");

    for (int j = 0; j < i; j++) {
        printf("Camera coordenada: %d\n", resposta[j].coordenada);
    }

    free(cameras);
    free(ruasVigiadas);
    free(resposta);

    return 0;
}
