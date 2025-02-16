# include <stdio.h>

# include <stdlib.h>

# include "funcoes.h"

# define  tam_pessoas 5

# define tam_conexões 6

int main (void) {

    /*   
    
    inicialmente vamos definir as pessoas e suas conexões
    a variável pessoas será do tipo int sendo organizada em forma de array
    seria interessante definir seu tamanho máximo com o define, pelo menos inicialmente

    */

    int pessoas [tam_pessoas] = {1, 2, 3, 4, 5};

    // conexões sempre tera como coluna 2, pois as relaçoes se dão de forma dois a dois 
    
    int conexões [tam_conexões][2] = {{1,2}, {1, 3}, {2, 3}, {2, 4}, {3, 4}, {4, 5}};

    /*
    
    agora precisamos contar quantas relações cada vértice possui
    vamos criar um ponteiro chamado relações e alocar memoria para 
    ele da mesma quantia de tam_pessoas já que se referem a elas

    */

    int *relações;

    relações = (int*) malloc(tam_pessoas * sizeof (int));

    // agora precisamos preencher relações -> fazer uma análise crítica 

    analise_relações(pessoas, tam_pessoas, conexões, tam_conexões, relações);
    
    /*
    
    agora o objetivo principal é ordernar o vetor 
    a fim de ter os termos que possuem mais ligações 
    primeiro
    
    */
   
   ordenando_dados(pessoas, relações, tam_pessoas);

   /*
   como ja temos todas as informações necesárias
   vamos começar a criação de nossa comunidade

   creio que serão necessárias tres estruturas
   1 -> A comunidade em Si
   2 -> Uma lista da possivel comunidade
   3 -> Uma lista para comparar caso não seja necessário (talvez isso seja desconsiderado)
   
   */

   /*
   as vezes para atingir um objetivo maior é preciso ir em uma direção não tão objetiva a 
   ele, mas que talvez seja crucial   
   
   */

   printf ("Imprima a pessoa com mais amizades --> ");

   int pessoa_com_mais_amigos;
   
   pessoa_com_mais_amigos = maior (pessoas);
   
   printf ("%d\n", pessoa_com_mais_amigos);

   int *comunidade;

   comunidade = NULL;

   int membros_da_comunidade = 0;

   printf ("Mostre como esta a comunidade agora --> ");

   add_comunidade(&comunidade, &membros_da_comunidade, pessoa_com_mais_amigos);

   imprime_array(comunidade, membros_da_comunidade);
   
   int * amigos_desse_individuo_maior;

   amigos_desse_individuo_maior = NULL;
   
   int total_amizades_do_maior = 0;

   printf ("Mostre as amizades dessa pessoa --> ");
   
   lista_de_amizades(pessoa_com_mais_amigos, conexões, tam_conexões,&amigos_desse_individuo_maior, &total_amizades_do_maior );
   
   imprime_array(amigos_desse_individuo_maior, total_amizades_do_maior);

   printf ("Mostrando a sequencia de qm tem mais amigos nessa lista --> ");

   ordenando_lista_de_amigos(&amigos_desse_individuo_maior, pessoas, relações,total_amizades_do_maior,tam_pessoas);

   imprime_array(amigos_desse_individuo_maior, total_amizades_do_maior);

   int segundo_cabeça = maior (amigos_desse_individuo_maior);

   printf ("A pessoa com mais amigos da lista do maior eh %d\n", segundo_cabeça);

   int * lista_de_amigos_segundo_cabeça;

   lista_de_amigos_segundo_cabeça = NULL;

   int total_amizades_segundo_cabeça = 0;

   printf ("Mostre as amizades dessa pessoa --> ");

   lista_de_amizades(segundo_cabeça, conexões, tam_conexões, &lista_de_amigos_segundo_cabeça, &total_amizades_segundo_cabeça );

   imprime_array(lista_de_amigos_segundo_cabeça, total_amizades_segundo_cabeça);

   remover_membros_comunidade_lista_de_amigos(comunidade, membros_da_comunidade, lista_de_amigos_segundo_cabeça, &total_amizades_segundo_cabeça);
   
   printf ("Eh possivel encontrar mais membros ???\n");

   int analise = analise_de_continuação_de_busca(amigos_desse_individuo_maior, lista_de_amigos_segundo_cabeça, total_amizades_do_maior, total_amizades_segundo_cabeça);

   if (analise == 1) {
    printf ("Sim!\n");
   }
   else{
    printf ("Nao!Comunidade encerrada!!\n");
   }

   printf ("Removendo os membros que ja se encontram na comunidade!!!\n");

   // printf ("total de amigos do segundo cabeca --> %d\n", total_amizades_segundo_cabeça);

   ordenando_lista_de_amigos(&lista_de_amigos_segundo_cabeça, pessoas, relações,total_amizades_segundo_cabeça,tam_pessoas);

   printf("Mostre a sequencia de qm tem mais amigos com essa pesssoa --> ");

   imprime_array(lista_de_amigos_segundo_cabeça, total_amizades_segundo_cabeça);

   add_comunidade(&comunidade, &membros_da_comunidade, segundo_cabeça);

   printf ("Mostre como esta a comunidade agora --> ");

   imprime_array(comunidade, membros_da_comunidade);

   printf ("Removendo o segundo cabeca da lista de amigos do maior, uma vez que faz parte da comunidade!!!\n");

   printf ("Segue a lista do maior atualizada --> ");

   remover_membros_comunidade_lista_de_amigos(comunidade, membros_da_comunidade, amigos_desse_individuo_maior, &total_amizades_do_maior);

   imprime_array(amigos_desse_individuo_maior, total_amizades_do_maior);

   int *lista_dos_membros_em_comum;

   int membros_em_comum = 0;

   lista_dos_membros_em_comum = NULL;

   printf ("Os membros em comum sao --> ");

   analise_do_circulo_de_amizade(amigos_desse_individuo_maior,lista_de_amigos_segundo_cabeça, &lista_dos_membros_em_comum,
   total_amizades_do_maior, total_amizades_segundo_cabeça, &membros_em_comum);

   imprime_array(lista_dos_membros_em_comum, membros_em_comum);

   printf ("Ordenando os membros em comum!!!\n");

   ordenando_lista_de_amigos(&lista_dos_membros_em_comum, pessoas, relações, membros_da_comunidade, tam_pessoas);

   printf("Depois de ordenar --> ");

   imprime_array(lista_de_amigos_segundo_cabeça, membros_em_comum);

   printf ("Temos que pegar o maior da lista fusao!!!\n");

   // ja da para rescrever alguns dados, ja que creio eu não terão mais tanta utilidade( ou posso ta enganado, vamos descobrir )

   pessoa_com_mais_amigos= maior(lista_dos_membros_em_comum);

   printf ("O maior que da lista eh de membros em comum eh %d\n", pessoa_com_mais_amigos);

   printf ("Mostre as amizades dessa pessoa --> ");

   free(amigos_desse_individuo_maior);

   amigos_desse_individuo_maior = NULL;

   total_amizades_do_maior = 0;

   lista_de_amizades(pessoa_com_mais_amigos, conexões, tam_conexões, &amigos_desse_individuo_maior, &total_amizades_do_maior);

   imprime_array(amigos_desse_individuo_maior, total_amizades_do_maior);

   remover_membros_comunidade_lista_de_amigos(comunidade, membros_da_comunidade, amigos_desse_individuo_maior, &total_amizades_do_maior);

   ordenando_lista_de_amigos(&amigos_desse_individuo_maior, pessoas, relações, total_amizades_do_maior, tam_pessoas);

   printf ("Analisando lista apos remover membros da comunidade --> ");

   imprime_array(amigos_desse_individuo_maior, total_amizades_do_maior);

   add_comunidade(&comunidade, &membros_da_comunidade, pessoa_com_mais_amigos);

   printf ("Eh possivel encontrar mais membros ??\n");

   analise = analise_de_continuação_de_busca(lista_dos_membros_em_comum, amigos_desse_individuo_maior, membros_em_comum, total_amizades_do_maior);

   if (analise == 1) {
    printf ("Sim! Ainda tem membros! Tudo certo!!\n");
   }
   else{
    printf ("Nao!Comunidade encerrada!!\n");
   }
    printf ("Comunidade final ficou --> ");

    imprime_array(comunidade, membros_da_comunidade);

    int passo_base = 0;

    int checagem;

    int teste_final = 0;

    teste_final = eh_possivel_ter_uma_comunidade_maior(relações, pessoas, tam_pessoas, membros_da_comunidade, &checagem, &passo_base);

    if (teste_final == 1) {
        printf ("Maior comunidade possivel!\n");
    }
    else {
        printf ("Ainda eh possivel ter uma maior!");
    }
    
    return 0;
}