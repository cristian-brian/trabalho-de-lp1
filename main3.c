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

int quantasMaiorVigilante(ponto p1, aresta *arestas, int numArestas){
    int contador = 0;
    for ( int i = 0; i < numArestas; i++){
        contador += temMaiorVigilante(p1, arestas[i]);
    }
    return contador;
}


/*

void eliminarRuasVigiadas(ponto p1, aresta *arestas, int numArestas){
    for ( int i = 0; i < numArestas; i++ ){
        for ( int j = i + 1; j < numArestas - 1; j++){
            if ( p1.coordenada == arestas[])
        }
    }
}

*/
int main (void){

    // temos 5 pontos

    ponto *cameras = (ponto *) malloc ( 5 * sizeof (ponto));

    aresta *ruasVigiadas = (aresta*) malloc ( 6 * sizeof(aresta));

    for ( int i = 0; i < 5; i++){
        cameras[i].coordenada = i;
    }

    for ( int i = 0; i < 6; i++){
        printf ("Digite as coordenadas das cameras que vigiam a mesma rua --> ");
        scanf ("%d %d", &ruasVigiadas[i].p1.coordenada, &ruasVigiadas[i].p2.coordenada);
    }
    ponto p4 = maiorVigilante(cameras, 5, ruasVigiadas, 6);

    printf ("%d\n", p4.coordenada);


    return 0;
}