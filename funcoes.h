// aqui vou definir minhas funções

# ifndef funcoes

# define funcoes

void analise_relações (int *array_base, int tam_array_base, int array_analise[][2], int tam_array_analise, int * relações);

void imprime_array (int * array, int tam );

void ordenando_dados (int *array_base, int *array_dados_relações, int tam);

void lista_de_amizades(int termo, int conexões[][2], int tam_coneções, int **lista, int *contador);

int maior (int * pessoas);

void add_comunidade (int **comunidade, int *pessoas_comunidade, int individuo);

int ordenando_lista_de_amigos (int **amigos, int *pessoas, int *relações, int tam_lista_amigos, int tam_pessoas);

void ordenação_simples (int *array, int tam);

void remover_membros_comunidade_lista_de_amigos(int *comunidade, int membros_comunidade, int *lista_de_amigos, int *tot_amigos );

void analise_do_circulo_de_amizade(int *lista1, int *lista2, int **lista_fusão, int tam_lista_01, int tam_lista_02, int *tam_lista_fusao);

int analise_de_continuação_de_busca (int *lista_amizades_1, int *lista_de_amigos_2, int tam_l1, int tam_l2);

int eh_possivel_ter_uma_comunidade_maior (int *relações, int *pessoas, int tam_relações, int totais_de_membros_da_comunidade, int *passo_base);





# endif