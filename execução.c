# include <stdio.h>

# include <stdlib.h>

void preenchendo_amizades (int *pessoas, int quantas_pessoas, int conexões[][2], int quantidade_de_conexões, int *amizades);

void imprimindo_um_vetor (int *array, int tamanho);


void ordenar_amizades_decrescente_e_em_relação_a_pessoas (int *array, int *array_base, int tamanho);


int main (void) {

    int pessoas[5] = {1, 2, 3, 4, 5};

    int conexões[6][2] = {{1,2},{1,3},{2,3},{2, 4},{3, 4},{4, 5}};

    // aqui vou ter criar um vetor que tenha a mesma quantidade de pessoas
    // esse array seria denomindado amizades e a soma dos seus elementos é 
    // dobro de conexões

    int *amizades;

    amizades = (int*) malloc (5 * sizeof (int));

    printf ("Imprimindo amizades\n");

    imprimindo_um_vetor(pessoas, 5);

    preenchendo_amizades(pessoas, 5, conexões, 6, amizades);

    printf("Imprimindo conexoes\n");

    imprimindo_um_vetor(amizades, 5);

    
    printf("\nImprimindo conexoes depois de ordenar\n");

    ordenar_amizades_decrescente_e_em_relação_a_pessoas(amizades, pessoas, 5);

    imprimindo_um_vetor(amizades, 5);

    printf ("Imprimindo pessoas em relacao a conexoes\n");

    imprimindo_um_vetor(pessoas, 5);

    int *comunidade_conectada;

    free (amizades);




    return 0;
}

void preenchendo_amizades (int *pessoas, int quantas_pessoas, int conexões[][2], int quantidade_de_conexões, int *amizades) {
    int i;

    int j; 

    int k;

    for (i = 0; i < quantas_pessoas; i ++) {
        amizades[i] = 0;
        for (j = 0; j < quantidade_de_conexões; j ++) {
            for (k = 0; k < 2; k ++) {
                if (pessoas[i] == conexões[j][k]) {
                    amizades[i] ++;
                }
            }
        }
    }
}

void imprimindo_um_vetor (int *array, int tamanho) {
    int i;

    for (i = 0; i < tamanho; i ++) {
        printf ("%d ", array[i]);
    }
    printf ("\n");
}

void ordenar_amizades_decrescente_e_em_relação_a_pessoas(int *array, int *array_base, int tamanho) {
    int i;

    int j;

    int aux;

    int aux_array_base;

    for (i = 0; i < tamanho; i ++) {
        for (j = i + 1; j < tamanho; j ++) {
            if (array[i] < array[j]) {

                aux = array[i];
                array[i] = array[j];
                array[j] = aux;

                aux_array_base= array_base[i];
                array_base[i] = array_base[j];
                array_base[j] = aux_array_base;
             }

        }
    }
}