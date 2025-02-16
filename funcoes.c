# include <stdio.h>

# include <stdlib.h>

# include "funcoes.h"


void analise_relações (int *array_base, int tam_array_base, int array_analise[][2], int tam_array_analise, int *relações) {
    int i;

    int j; 

    int k;

    for ( i = 0; i < tam_array_base; i ++) {
        relações[i] = 0;
        for (j = 0; j < tam_array_analise; j ++) {
            for (k = 0; k < 2; k ++) {
                if (array_base[i] == array_analise[j][k]) {
                    relações[i] ++;
                }
            }
        }
    }
}

void imprime_array (int * array, int tam ) {
    int i;

    for (i = 0; i < tam; i ++)
    {
        printf ("%d ", array[i]);
    }
    printf ("\n");
}

void ordenando_dados (int *array_base, int *array_dados_relações, int tam) {
    int i;

    int j;

    int aux_relação;

    int aux_base;

    for ( i = 0; i < tam; i ++ ) {
        for ( j = i + 1; j < tam; j ++) {
            if (array_dados_relações[i] < array_dados_relações[j]) {
                aux_relação = array_dados_relações[i];
                array_dados_relações[i] = array_dados_relações[j];
                array_dados_relações[j] = aux_relação;

                aux_base = array_base[i];
                array_base[i] = array_base[j];
                array_base[j] = aux_base;

            }
        }
    }
}

void ordenação_simples (int *array, int tam){
    int i;

    int j;

    int aux;

    for (i = 0; i < tam; i ++) {
        for (j = i + 1; j < tam; j ++) {
            if (array[i] < array[j]){
                aux = array[i];
                array[i] = array[j];
                array[j]= aux;

            }
        }
    }
}


void lista_de_amizades(int termo, int conexões[][2], int tam_coneções, int **lista, int *contador) {

    int i;

    int contador_base = 0;

    int *array_temporario;

    *lista = NULL;

    for (i = 0; i < tam_coneções; i ++) {
        if (termo == conexões[i][0]) {
            contador_base ++;
            array_temporario = (int *) realloc (*lista, contador_base * sizeof(int));
            if (array_temporario == NULL) {
                printf ("Deu ruim");
            }
            *lista = array_temporario;
            (*lista)[contador_base -1] = conexões[i][1];   
        }
        if (termo == conexões[i][1]) {
            contador_base ++;
            array_temporario = (int *) realloc (*lista, contador_base * sizeof(int));
            if (array_temporario == NULL) {
                printf ("Deu ruim");
            }
            *lista = array_temporario;
            (*lista)[contador_base -1] = conexões[i][0];
        }
    }

    *contador = contador_base;
}

int maior (int * pessoas) {
    // como ja ta ordenado o maior eh o primeiro 
    return pessoas[0];
}

void add_comunidade (int **comunidade, int *pessoas_comunidade, int individuo) {
    (*pessoas_comunidade)++; 

    int *array_base = realloc(*comunidade, (*pessoas_comunidade) * sizeof(int));
    if (array_base == NULL) {
        printf("Erro na realocação de memória.\n");
    }

    *comunidade = array_base; // Atualiza a referência do ponteiro
    (*comunidade)[(*pessoas_comunidade) - 1] = individuo;
}


int ordenando_lista_de_amigos (int **amigos, int *pessoas, int *relações, int tam_lista_amigos, int tam_pessoas){


    int i;

    int j;

    int var = -1;

    int *array;

    int *array_2;

    array = (int*) malloc(tam_pessoas*sizeof(int));

    array_2 = (int*) malloc(tam_pessoas*sizeof(int));

    if (array == NULL || array_2 == NULL){
        printf ("Deu ruim");
    }

    for (i = 0; i < tam_pessoas; i ++) {
        array[i]= pessoas[i];
    }

    for (i = 0; i < tam_pessoas; i ++) {
        array_2[i]= relações[i];
    }


    for (i = 0; i < tam_pessoas; i ++){
        for (j = 0; j < tam_lista_amigos; j ++) {
            if (array[i] == (*amigos)[j]) {
                var += 1;
            }
        }
        if (var == -1) {
            array[i] = 0;
            array_2[i] = 0;
        }
    }

    ordenando_dados(array, array_2, tam_pessoas);

    int *temporario;

    temporario = (int*) realloc(array, tam_lista_amigos*sizeof(int));


    *amigos = temporario;
}

void remover_membros_comunidade_lista_de_amigos(int *comunidade, int membros_comunidade, int *lista_de_amigos, int *tot_amigos ){
    int i;

    int j;

    int contagem_de_remoção = 0;

    for ( i = 0; i < membros_comunidade; i ++ ) {
        for ( j = 0; j < *tot_amigos; j ++) {
            if (comunidade[i] == lista_de_amigos[j]){
                lista_de_amigos[j] = 0;
                contagem_de_remoção ++;
                
            }
        }
    }
    ordenação_simples(lista_de_amigos, (*tot_amigos));

    int k = 0;

    while (k < contagem_de_remoção){
        (*tot_amigos) --;
        k ++;
    }
}

void analise_do_circulo_de_amizade(int *lista1, int *lista2, int **lista_fusão, int tam_lista_01, int tam_lista_02, int *tam_lista_fusao) {
    int i;

    int j;

    *lista_fusão = NULL;

    int *array_temporario;

    int contador = 0;

    for (i = 0; i < tam_lista_01; i ++) {
        for ( j = 0; j < tam_lista_02; j ++) {
            if (lista1[i] == lista2[j]) {
                contador ++;
                array_temporario = (int*) realloc (*lista_fusão, contador * sizeof(int));
                if (array_temporario == NULL) {
                    printf ("Falha na fusao de dados (obtencao)");
                }
                *lista_fusão = array_temporario;
                (*lista_fusão)[contador - 1] = lista1[i];
            }
        }
    }

    *tam_lista_fusao = contador;
}

int analise_de_continuação_de_busca (int *lista_amizades_1, int *lista_de_amigos_2, int tam_l1, int tam_l2) {

    int i;

    int j;

    for (i = 0; i < tam_l1; i ++) {
        for (j = 0; j < tam_l2; j ++) {
            if (lista_amizades_1[i] == lista_de_amigos_2[j] ){
                return 1;
            }
        }
    }
    return 0; 

}

int eh_possivel_ter_uma_comunidade_maior (int *relações, int *pessoas, int tam_relações, int totais_de_membros_da_comunidade, int *checagem, int *passo_base) {

    int i;

    *checagem = 0;

    for (i = *passo_base; i < tam_relações; i ++) {
        if (relações[i] > (totais_de_membros_da_comunidade -1)){
            *checagem = pessoas[i];
            return -1;
        }
    }
    return 1;

}







