/*
    Aluno: Maurílio de Jesus Silveira
    Matrícula: 17/0152294
    Curso: Ciência da Computação Bacharelado
*/

#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*ALOCANDO A LISTA E COLOCANDO PRIMEIRO E FIM PARA NULL E QUANTIDADE PARA 0*/
t_lista* aloca_lista(){
    t_lista* lista = (t_lista*) malloc(sizeof(t_lista));

    lista->primeiro = NULL;
    lista->fim = NULL;
    lista->quantidade = 0;

    return lista;    
}

/*ALOCANDO O ELEMENTO E CHAMANDO FUNCAO PARA ALOCAR O PRODUTO*/
t_elemento* aloca_elemento(int codigo, char* nome, float preco, int quantidade){
    t_elemento* elemento = ((t_elemento*) malloc(sizeof(t_elemento)));

    elemento->produto = aloca_produto(codigo,nome,preco,quantidade);
    
    elemento->proximo = NULL;

    return elemento;    
}

/*ALOCANDO O PRODUTO TENDO TODOS OS DADOS COPIADOS E RETORNANDO O ENDERECO PARA O ELEMENTO*/
t_produto* aloca_produto(int codigo, char* nome, float preco, int quantidade){
    t_produto* produto = (t_produto*) malloc(sizeof(t_produto));
    produto->nome = (char*) malloc((strlen(nome)+1)*sizeof(char));
    
    produto->codigo = codigo;
    strcpy(produto->nome, nome);
    produto->preco = preco;
    produto->quantidade = quantidade;

    return produto;
}

/*FUNCAO QUE REMOVE TODOS OS ELEMENTO DA LISTA E LIBERANDO A MEMORIA DEPOIS DE REMOVER*/
void remove_lista(t_lista* lista){
    if(lista == NULL){
        mensagem_vazio();
        return;
    }

    /*REMOVENDO TODOS OS ELEMENTOS DA LISTA*/
    if(lista->quantidade > 0){
        do{
            t_elemento* remove_lista_inicio = lista->primeiro;

            lista->primeiro = remove_lista_inicio->proximo;

            free(remove_lista_inicio->produto->nome);
            free(remove_lista_inicio->produto);
            free(remove_lista_inicio);
            
            remove_lista_inicio = NULL;
            lista->quantidade --;
        }while(lista->primeiro != NULL);   

        free(lista);
        printf("Todos os produtos foram removidos com sucesso! \n");
    }else{
        if(lista->primeiro == NULL){     /* lista realmente vazia */
            mensagem_vazio();

        }else{                            /* erro, ponteiro != NULL */
            printf("ERRO! Quantidade de termos da lista\n");
            printf("nao correspondem com o contador <quantidade>");
            getchar();
        }
    }
}

/*FUNCAO QUE TEM COMO OBJETIVO CADASTRAR NOVOS PRODUTOS CHAMANDO A FUNCAO PARA ALOCAR UM NOVO ELEMENTO*/
int inserir(int posicao, int codigo, char* nome, float preco, int quantidade, t_lista* lista){
    if(lista == NULL){
        mensagem_vazio();
        return -1;
    }

    /*ALOCANDO O ELEMENTO QUANDO A LISTA ESTA VAZIA*/
    if(lista->quantidade == 0){
        t_elemento* aux_lista_vazia = aloca_elemento(codigo, nome, preco, quantidade);
        lista->primeiro = aux_lista_vazia;
        lista->fim = aux_lista_vazia;
        
        lista->quantidade ++;
    }else if(posicao == 0){
        /*O PRODUTO VAI SER ADICIONADO NO INICIO DA LISTA*/
        t_elemento* aux_inserir = aloca_elemento(codigo, nome, preco, quantidade);

        aux_inserir->proximo = lista->primeiro;
        lista->primeiro = aux_inserir;

        lista->quantidade ++;
    }else if((posicao > 0) && (posicao < lista->quantidade)){
        /*O PRODUTO VAI SER ADICIONANDO NO MEIO DA LISTA*/
        inserir_meio(posicao, codigo, nome, preco, quantidade, lista);
    }else{
        /*CASO EM QUE A POSICAO DO ELEMENTO E INVALIDA*/
        return -1;
    }

    return 1;
}

/*FUNCAO COM O OBJETIVO DE PRINTAR TODOS OS PRODUTOS NA TELA*/
void printa_lista(t_lista* lista){
    if(lista == NULL){
        mensagem_vazio();
        return;
    }

    printf("========================================\n");
    printf("\t TODOS OS PRODUTO EM ESTOQUE \t\n");
    printf("========================================\n");

    if(lista->quantidade > 0){
        t_elemento* aux_printa_lista = lista->primeiro;

        int id = 0;

        /*LOOP PARA PODER PRINTAR TODOS OS PRODUTOS NA TELA*/
        while(aux_printa_lista != NULL) {
            printf("====================================\n");
            printf("Id: %d \n", id);
            printf("Codigo: %d \n", aux_printa_lista->produto->codigo);
            printf("Nome: %s \n", aux_printa_lista->produto->nome);
            printf("Preco: %.2f \n", aux_printa_lista->produto->preco);
            printf("Quantidade: %d \n", aux_printa_lista->produto->quantidade);
            printf("====================================\n");
            aux_printa_lista = aux_printa_lista->proximo;

            id ++;
        }
    }else{
        mensagem_vazio();
    }
}

/*FUNCAO QUE PERCORRE TODAS A LISTA PARA IDENTIFICAR ONDE O NOVO PRODUTO VAI SER INSERIDO
CASO O USUARIO TENHA FORNECIDO UMA POSICAO QUE NAO SEJA NO INICIO*/
t_elemento* percorre_lista(int posicao, t_lista* lista){
    t_elemento* aux_percorre_lista = lista->primeiro;

    /* O >= FOI COLOCADO PARA VALIDAR QUANDO O ID NO PRODUTO SEJA 1 E O aux_anterior TENHA INVACADO ELA*/
    if((posicao >= 0) && (posicao <= lista->quantidade)){
        int i;
        
        for(i = 0; i < posicao; i++){
            aux_percorre_lista = aux_percorre_lista->proximo;
        }
        
        return aux_percorre_lista;
    }else{
        printf("O produto nao foi encontrado na lista! \n");
        printf("%d \n", posicao);
        return NULL;
    }
}

/*FUNCAO QUE TEM COMO OBJETIVO JUNTAMENTE COM A percorre_lista() ENCONTRAR ONDE O PRODUTO VAI SER 
INSERIDO CASO O USUARIO INFORME UMA POSICAO QUE NAO SEJA NO INICIO*/
void inserir_meio(int posicao, int codigo, char* nome, float preco, int quantidade, t_lista* lista){

    if((posicao > 0) && (posicao < lista->quantidade)){
        t_elemento* aux_atual = percorre_lista(posicao, lista);

        if(aux_atual != NULL){
            t_elemento* aux_anterior = percorre_lista(posicao-1, lista);

            t_elemento* elemento_meio = (t_elemento*) malloc(sizeof(t_elemento));

            elemento_meio->produto = aloca_produto(codigo,nome,preco,quantidade);
        
            elemento_meio->proximo = NULL;

            elemento_meio->proximo = aux_atual;
            aux_anterior->proximo = elemento_meio;

            lista->quantidade ++;

            return;
        }
    }else{
        printf("O produto nao foi encontrado na lista! \n");
        return;
    }
}

/*MENU DO PROGRAMA PARA UMA INTERACAO COM O USUARIO*/
void menu(t_lista* lista){
    int opcao;

    system(CLEAR);
    printf("====================================\n");
    printf("\t MERCADO IMPROVISO\t \n");
    printf("====================================\n");

    /*OPCOES DE ESCOLHA DO USUARIO*/
    printf("1 - ADICIONAR PRODUTO\n");
    printf("2 - VER PRODUTOS EM ESTOQUE\n");
    printf("3 - LIMPAR TODO O ESTOQUE\n");
    printf("4 - QUANTIDADE DE CODIGOS PAR\n");
    printf("5 - PRECO MEDIO DOS PRODUTOS\n");
    printf("6 - PRODUTO COM O MENOR VALOR\n");
    printf("7 - PRODUTO COM O MAIOR VALOR\n");
    printf("8 - ID DO PRODUTO MAIS CARO\n");
    printf("9 - VALOR TOTAL DE TODOS OS PRODUTOS\n");
    printf("10 - PESQUISAR PRODUTO PELO CODIGO\n");
    printf("\n");
    printf("0 - SAIR\n");
    printf("\n");
    printf("> ");
    scanf("%d",&opcao);
    resposta_menu(opcao, lista);
}

/*PEGANDO A RESPOSTA DO USUARIO E ENCAMINHANDO ELE PARA A DEVIDA FUNCAO*/
int resposta_menu(int opcao, t_lista* lista){
    system(CLEAR);

    int resposta;

    if((opcao < 0) || (opcao > 10)){
        printf("Opcao invalida! \n");
        getchar();
        getchar();
        menu(lista);
    }else if(opcao == 1){
        char nome[50];
        int posicao, codigo, quantidade;
        float preco;

        printf("========================================\n");
        printf("\t ADICIONANDO NOVO PRODUTO \t\n");
        printf("========================================\n");
        
        /*LENDO TODOS OS DADOS FORNECIDOS PELO USUARIO*/
        printf("Posicao: ");
        scanf("%d", &posicao);
        printf("Codigo: ");
        scanf("%d", &codigo);
        printf("Nome: ");
        scanf("%s", nome);
        printf("Preco: ");
        scanf("%f", &preco);
        printf("Quantidade: ");
        scanf("%d", &quantidade);

        /*CASO TODOS OS ELEMENTO TENHAM SIDO APAGADOS*/
        if (lista == NULL) {
            lista = aloca_lista();
        }
        resposta = inserir(posicao, codigo, nome, preco, quantidade, lista);

        system(CLEAR);

        /*VALIDANDO RESPOSTA DO USUARIO*/
        if(resposta == 1){
            printf("O produto foi adicionado com sucesso! \n");
            getchar();
            getchar();
            menu(lista);
        }else{
            printf("Posicao do produto inexistente! \n");
            printf("O produto nao foi adicionado! \n");
            printf("Tente novamente... \n");
            getchar();
            getchar();
            menu(lista);
        }
    }else if(opcao == 2){
        printa_lista(lista);
        getchar();
        getchar();
        menu(lista);
    }else if(opcao == 3){
        remove_lista(lista);
        lista = NULL;
        getchar();
        getchar();
        menu(lista);
    }else if(opcao == 4){
        int quantidade = quantidade_pares(lista);
        if(quantidade > 0){
            printf("Quantidade de codigos pares: %d \n", quantidade);
        }else{
            printf("Nenhum produto com codigo par cadastrado \n");
        }
        getchar();
        getchar();
        menu(lista);
    }else if(opcao == 5){
        int preco =(int) preco_medio(lista);
        if(preco > 0){
            printf("Preco medio dos produtos: R$%.d \n", preco);
        }else{
            printf("Nao existe nenhum produto cadastrado! \n");
            printf("Cadastre algum produto para ter acesso a essa funcionalidade... \n");
        }
        getchar();
        getchar();
        menu(lista);
    }else if(opcao == 6){
        menor_preco(lista);
        getchar();
        getchar();
        menu(lista);
    }else if(opcao == 7){
        maior_preco(lista);
        getchar();
        getchar();
        menu(lista);
    }else if(opcao == 8){
        id_maior_preco(lista);
        getchar();
        getchar();
        menu(lista);
    }else if(opcao == 9){
        valor_total(lista);
        getchar();
        getchar();
        menu(lista);
    }else if(opcao == 10){
        int cod_pesquisa;
        printf("Informe o codigo: ");
        scanf("%d", &cod_pesquisa);
        system(CLEAR);
        pesquisa_produto(cod_pesquisa, lista);
        getchar();
        getchar();
        menu(lista);
    }else if(opcao == 0) {
        printf("Saindo...");
        getchar();
        getchar();
        system(CLEAR);
    }

    return 0;
}

/*FUNCAO QUE VERIFICA QUANTOS PRODUTOS TEM CODIGOS PARES*/
int quantidade_pares(t_lista* lista){
    if(lista == NULL){
        mensagem_vazio();
        return 0;
    }

    printf("=========================================\n");
    printf("\t PRODUTOS COM CODIGOS PARES \t\n");
    printf("=========================================\n");

    int contador_par = 0;

    if(lista->quantidade > 0){
        t_elemento* aux_par = lista->primeiro;
        
        while(aux_par != NULL) {
            if(aux_par->produto->codigo % 2 == 0){
                contador_par ++;
            } 
            aux_par = aux_par->proximo;
        }
        return contador_par;
    }else{
        mensagem_vazio();
        return -1;
    }
}

/*FUNCAO QUE CALCULA O PRECO MEDIO DE TODOS OS PRODUTOS*/
int preco_medio(t_lista* lista){
    if(lista == NULL){
        mensagem_vazio();
        return 0;
    }

    printf("=========================================\n");
    printf("\t PRECO MEDIO DOS PRODUTOS \t\n");
    printf("=========================================\n");

    float preco_medio = 0.0;
    int contador = 0;

    if(lista->quantidade > 0){
        t_elemento* aux_preco = lista->primeiro;
        
        while(aux_preco != NULL) {
            preco_medio += aux_preco->produto->preco;
            contador ++;
            aux_preco = aux_preco->proximo;
        }

        return preco_medio/contador;
    }else{
        mensagem_vazio();
        return -1;
    }
}

/*FUNCAO QUE BUSCA O MENOS VALOR DE UM PRODUTO*/
int menor_preco(t_lista* lista){
    if(lista == NULL){
        mensagem_vazio();
        return 0;
    }

    float menor = 0.0;

    if(lista->quantidade > 0){
        t_elemento* aux_menor_preco = lista->primeiro;
        menor = aux_menor_preco->produto->preco;

        printf("====================================\n");
        printf("\t PRODUTO DE MENOR PRECO \t\n");
        printf("====================================\n");

        while(aux_menor_preco != NULL) {
            if(menor > aux_menor_preco->produto->preco){
                menor = aux_menor_preco->produto->preco;
                aux_menor_preco = aux_menor_preco->proximo;
            }else{
                aux_menor_preco = aux_menor_preco->proximo;
            }
        }

        printf("O valor do produto mais BARATO e: R$%.2f", menor);
    }else{
        mensagem_vazio();
    }

    return 0;
}

/*FUNCAO QUE BUSCA O MAIOR VALOR DE UM PRODUTO*/
int maior_preco(t_lista* lista){
    if(lista == NULL){
        mensagem_vazio();
        return 0;
    }

    float maior = 0.0;

    if(lista->quantidade > 0){
        t_elemento* aux_maior_preco = lista->primeiro;
        maior = aux_maior_preco->produto->preco;

        printf("====================================\n");
        printf("\t PRODUTO DE MAIOR PRECO \t\n");
        printf("====================================\n");

        while(aux_maior_preco != NULL) {
            if(maior < aux_maior_preco->produto->preco){
                maior = aux_maior_preco->produto->preco;
                aux_maior_preco = aux_maior_preco->proximo;
            }else{
                aux_maior_preco = aux_maior_preco->proximo;
            }
        }

        printf("O valor do produto mais CARO e: R$%.2f", maior);
    }else{
        mensagem_vazio();
    }

    return 0;
}

/*FUNCAO QUE BUSCA O ID DO PRODUTO DE MAIOR VALOR*/
int id_maior_preco(t_lista* lista){
    if(lista == NULL){
        mensagem_vazio();
        return 0;
    }

    float maior = 0.0;

    if(lista->quantidade > 0){
        t_elemento* aux_id_maior_preco = lista->primeiro;
        maior = aux_id_maior_preco->produto->preco;

        int id = 0;
        int aux_conta = 0;

        printf("============================================\n");
        printf("\t ID DO PRODUTO DE MAIOR PRECO \t\n");
        printf("============================================\n");

        while(aux_id_maior_preco != NULL) {
            if(maior < aux_id_maior_preco->produto->preco){
                maior = aux_id_maior_preco->produto->preco;
                aux_id_maior_preco = aux_id_maior_preco->proximo;
                id = aux_conta;
            }else{
                aux_id_maior_preco = aux_id_maior_preco->proximo;
            }
            aux_conta ++;
        }

        printf("O ID do produto mais CARO e: %d", id);
    }else{
        mensagem_vazio();
    }

    return 0;
}

/*FUNCAO QUE CALCULA O VALOR TOTAL DE TODOS OS PRODUTOS*/
int valor_total(t_lista* lista){
    if(lista == NULL){
        mensagem_vazio();
        return 0;
    }

    float total = 0.0;

    if(lista->quantidade > 0){
        t_elemento* total_preco = lista->primeiro;

        printf("====================================\n");
        printf("\t VALOR TOTAL DOS PRODUTOS \t\n");
        printf("====================================\n");

        while(total_preco != NULL) {
            total += total_preco->produto->preco;
            total_preco = total_preco->proximo;
        }

        printf("O valor total de todos os produtos é: R$%.2f", total);
    }else{
        mensagem_vazio();
    }

    return 0;
}

/*FUNCAO QUE TEM COMO OBJETICO BUSCAR E MOSTRAR O PRODUTO CADASTRADO COM O CODIGO INFORMADO*/
void pesquisa_produto(int codigo, t_lista* lista){
    if(lista == NULL){
        mensagem_vazio();
        return;
    }

    printf("====================================\n");
    printf("\t RESULTADO DA PESQUISA \t\n");
    printf("====================================\n");

    if(lista->quantidade > 0){
        t_elemento* pesquisa_lista = lista->primeiro;

        int id = 0;

        while(pesquisa_lista != NULL) {
            if(pesquisa_lista->produto->codigo == codigo){    
                printf("Id: %d \n", id);
                printf("Codigo: %d \n", pesquisa_lista->produto->codigo);
                printf("Nome: %s \n", pesquisa_lista->produto->nome);
                printf("Preco: %.2f \n", pesquisa_lista->produto->preco);
                printf("Quantidade: %d \n", pesquisa_lista->produto->quantidade);
                printf("====================================\n");
            }
            pesquisa_lista = pesquisa_lista->proximo;
            id ++;
        }
    }else{
        printf("Nao existe nenhum produto cadastrado com esse codigo! \n");
        printf("Tente novamente... \n");
    }
}

/*FUNCAO PARA PRINTAR UM ALERTA QUANDO O USUARIO ESTIVER TENTANDO ACESSAR A LISTA SEM TER 
NENHUM PRODUTO CADASTRADO NELA*/
void mensagem_vazio(){
    printf("Nao existe nenhum produto cadastrado! \n");
    printf("Cadastre algum produto para ter acesso a essa funcionalidade... \n");
}
