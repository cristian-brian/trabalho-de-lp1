# include <stdio.h>

# include <stdlib.h>

# include "funcoes.h"

# define  tam_pessoas 8

# define tam_conexões 10


int main (void) {

    int contador = 0;

    int pessoas [tam_pessoas] = {1, 2, 3, 4, 5, 6, 7, 8};

    int conexões [tam_conexões][2] = {{1,2}, {1, 3}, {1, 4},{1, 5}, {1, 6}, {1, 7}, {1, 8}, {2,3}, {2, 4}, {3,4}};

    int *relações;

    relações = (int*) malloc(tam_pessoas * sizeof (int));

    analise_relações(pessoas, tam_pessoas, conexões, tam_conexões, relações);

    ordenando_dados(pessoas, relações, tam_pessoas);

    // variavel de controle do problema

    int continuacao = 1;

    int analise = 1;

    int acesso_sobre_comunidades_base = 1, acesso_sobre_comunidades_comparacao = 1, start = 0, start_comparação = 0;

    int comparação = 0;

    int *comunidade_base, *comunidade_comparacao;

    int membros_da_comunidade_base = 0, membros_da_comunidade_comparação = 0;

    int pessoa_referencial_1, pessoa_referencial_3;;
    
    int *amigos_pessoa_referencial_1, *amigos_pessoa_referencial_3;

    int quantidade_de_amigos_pessoa_1, quantidade_de_amigos_pessoa_3;

    int pessoa_referencial_2, pessoa_referencial_4;
    
    int *amigos_pessoa_referencial_2, *amigos_pessoa_referencial_4;

    int quantidade_de_amigos_pessoa_2, quantidade_de_amigos_pessoa_4;

    int *cercando_amigos_comum_1, *cercando_amigos_comum_3;

    int total_membros_em_comum_1, total_membros_em_comum_3;

    int *cercando_amigos_comum_2, *cercando_amigos_comum_4;

    int total_membros_em_comum_2, total_membros_em_comum_4;

    int i; 

    int passo_base = 0;

    int verificação;


    while (continuacao) {

         while (acesso_sobre_comunidades_base == 1) {

            if (start == 0) {
                pessoa_referencial_1 = pessoas[passo_base]; 

                comunidade_base = NULL;

                membros_da_comunidade_base = 0;

                //add_comunidade(&comunidade_base, &membros_da_comunidade_base, pessoa_referencial_1);

            } else {
                free (amigos_pessoa_referencial_1);

                pessoa_referencial_1 = maior (cercando_amigos_comum_1);

            }
            
            add_comunidade(&comunidade_base, &membros_da_comunidade_base, pessoa_referencial_1);
            
            amigos_pessoa_referencial_1 = NULL;
            
            quantidade_de_amigos_pessoa_1 = 0;
            
            lista_de_amizades(pessoa_referencial_1, conexões, tam_conexões, &amigos_pessoa_referencial_1,&quantidade_de_amigos_pessoa_1);

            ordenando_lista_de_amigos(&amigos_pessoa_referencial_1, pessoas, relações, quantidade_de_amigos_pessoa_1, tam_pessoas);
            
            
            if (start == 1) {
                remover_membros_comunidade_lista_de_amigos(comunidade_base, membros_da_comunidade_base, amigos_pessoa_referencial_1, &quantidade_de_amigos_pessoa_1);
            
               analise =  analise_de_continuação_de_busca(amigos_pessoa_referencial_1, cercando_amigos_comum_1, quantidade_de_amigos_pessoa_1, total_membros_em_comum_1);
            
            }
            
            if (analise !=  1) {
                break;
            }


            pessoa_referencial_2 = maior (amigos_pessoa_referencial_1);

            add_comunidade(&comunidade_base, &membros_da_comunidade_base, pessoa_referencial_2);

            amigos_pessoa_referencial_2 = NULL;

            quantidade_de_amigos_pessoa_2 = 0;

            lista_de_amizades(pessoa_referencial_2, conexões, tam_conexões, &amigos_pessoa_referencial_2, &quantidade_de_amigos_pessoa_2);

            remover_membros_comunidade_lista_de_amigos(comunidade_base, membros_da_comunidade_base, amigos_pessoa_referencial_2,&quantidade_de_amigos_pessoa_2);
            

            analise = analise_de_continuação_de_busca (amigos_pessoa_referencial_1, amigos_pessoa_referencial_2, quantidade_de_amigos_pessoa_1, quantidade_de_amigos_pessoa_2);
            if (analise != 1) {

                break;
            }

            ordenando_lista_de_amigos(&amigos_pessoa_referencial_2, pessoas, relações, quantidade_de_amigos_pessoa_2, tam_pessoas);

            remover_membros_comunidade_lista_de_amigos(comunidade_base, membros_da_comunidade_base, amigos_pessoa_referencial_1, &quantidade_de_amigos_pessoa_1);

            cercando_amigos_comum_1 = NULL;

            total_membros_em_comum_1 = 0;

            analise_do_circulo_de_amizade(amigos_pessoa_referencial_1, amigos_pessoa_referencial_2, &cercando_amigos_comum_1, quantidade_de_amigos_pessoa_1, quantidade_de_amigos_pessoa_2, &total_membros_em_comum_1);

            if (total_membros_em_comum_1 == 0) {
                break;
            }

            ordenando_lista_de_amigos(&cercando_amigos_comum_1, pessoas, relações, total_membros_em_comum_1, tam_pessoas);

            start = 1;
        }
        /*
        
        if (comparação == 1) {
            pega_a_maior_comunidade(&comunidade_base, &comunidade_comparacao, membros_da_comunidade_base, membros_da_comunidade_comparação);
        }
        */

        verificação = eh_possivel_ter_uma_comunidade_maior(relações, pessoas, tam_pessoas, membros_da_comunidade_base, &passo_base);

        if (verificação != 1) {

            start_comparação = 0;

            acesso_sobre_comunidades_base = 0;

            acesso_sobre_comunidades_comparacao = 1;

            analise = 1;

            comparação = 1;
    }
    else {
        break;
    }

    while (acesso_sobre_comunidades_comparacao == 1) {
        if (start_comparação == 0) {
            pessoa_referencial_3 = pessoas[passo_base]; 

            comunidade_comparacao = NULL;

            membros_da_comunidade_comparação = 0;


            //add_comunidade(&comunidade_base, &membros_da_comunidade_base, pessoa_referencial_1);

        } else {
            free (amigos_pessoa_referencial_3);

            pessoa_referencial_3 = maior (cercando_amigos_comum_3);

        }
        
        add_comunidade(&comunidade_comparacao, &membros_da_comunidade_comparação, pessoa_referencial_3);
        
        amigos_pessoa_referencial_3 = NULL;
        
        quantidade_de_amigos_pessoa_3 = 0;
        
        lista_de_amizades(pessoa_referencial_3, conexões, tam_conexões, &amigos_pessoa_referencial_3,&quantidade_de_amigos_pessoa_3);

        ordenando_lista_de_amigos(&amigos_pessoa_referencial_3, pessoas, relações, quantidade_de_amigos_pessoa_3, tam_pessoas);
        
        
        if (start_comparação == 1) {
            remover_membros_comunidade_lista_de_amigos(comunidade_comparacao, membros_da_comunidade_comparação, amigos_pessoa_referencial_3, &quantidade_de_amigos_pessoa_3);
        
           analise =  analise_de_continuação_de_busca(amigos_pessoa_referencial_3, cercando_amigos_comum_3, quantidade_de_amigos_pessoa_3, total_membros_em_comum_3);
        
        }
        
        if (analise !=  1) {
            break;
        }


        pessoa_referencial_4 = maior (amigos_pessoa_referencial_3);

        add_comunidade(&comunidade_comparacao, &membros_da_comunidade_comparação, pessoa_referencial_4);

        amigos_pessoa_referencial_4= NULL;

        quantidade_de_amigos_pessoa_4 = 0;

        lista_de_amizades(pessoa_referencial_4, conexões, tam_conexões, &amigos_pessoa_referencial_4, &quantidade_de_amigos_pessoa_4);

        remover_membros_comunidade_lista_de_amigos(comunidade_comparacao, membros_da_comunidade_comparação, amigos_pessoa_referencial_2,&quantidade_de_amigos_pessoa_2);
        

        analise = analise_de_continuação_de_busca (amigos_pessoa_referencial_3, amigos_pessoa_referencial_4, quantidade_de_amigos_pessoa_4, quantidade_de_amigos_pessoa_4);
        if (analise != 1) {

            break;
        }

        ordenando_lista_de_amigos(&amigos_pessoa_referencial_4, pessoas, relações, quantidade_de_amigos_pessoa_4, tam_pessoas);

        remover_membros_comunidade_lista_de_amigos(comunidade_comparacao, membros_da_comunidade_comparação, amigos_pessoa_referencial_3, &quantidade_de_amigos_pessoa_3);

        cercando_amigos_comum_3 = NULL;

        total_membros_em_comum_3 = 0;

        analise_do_circulo_de_amizade(amigos_pessoa_referencial_3, amigos_pessoa_referencial_3, &cercando_amigos_comum_3, quantidade_de_amigos_pessoa_3, quantidade_de_amigos_pessoa_4, &total_membros_em_comum_3);

        if (total_membros_em_comum_3 == 0) {
            break;
        }

        ordenando_lista_de_amigos(&cercando_amigos_comum_3, pessoas, relações, total_membros_em_comum_3, tam_pessoas);

        start_comparação = 1;

    }



    verificação = eh_possivel_ter_uma_comunidade_maior(relações, pessoas, tam_pessoas, membros_da_comunidade_base, &passo_base);

    if (verificação != 1) {

        start = 0;

        acesso_sobre_comunidades_base = 1;

        acesso_sobre_comunidades_comparacao = 0;

        analise = 1;


        }else {
            break;
    }
/*
if (comparação == 1) {
    pega_a_maior_comunidade(&comunidade_comparacao, &comunidade_base, membros_da_comunidade_comparação, membros_da_comunidade_base);
}
*/
}

if (membros_da_comunidade_base >= membros_da_comunidade_comparação) {

    imprime_array(comunidade_base, membros_da_comunidade_base);
} else {
    
    imprime_array(comunidade_comparacao, membros_da_comunidade_comparação);

}

return 0;

}