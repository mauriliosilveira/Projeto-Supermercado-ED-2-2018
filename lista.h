/*
    Aluno: Maurílio de Jesus Silveira
    Matrícula: 17/0152294
    Curso: Ciência da Computação Bacharelado
*/

#ifndef __LISTA_H__
#define __LISTA_H__

#ifdef _WIN32
    #define CLEAR "cls"
#else   
    #define CLEAR "clear"
#endif

/*ESTRUTURA DO PRODUTO*/
typedef struct{
    int codigo;
    char* nome;
    float preco;
    int quantidade;
} t_produto;

/*ESTRUTURA DO ELEMENTO*/
typedef struct elemento{
    t_produto* produto;
    struct elemento* proximo;
} t_elemento;

/*ESTRUTURA DA LISTA*/
typedef struct{
    t_elemento* primeiro;
    t_elemento* fim;
    int quantidade;
} t_lista;


t_lista* aloca_lista(); /*ALOCANDO A LISTA*/

t_produto* aloca_produto(int codigo, char* nome, float preco, int quantidade); /*ALOCANDO O PRODUTO*/

t_elemento* aloca_elemento(int codigo, char* nome, float preco, int quantidade); /*ALOCANDO O ELEMENTO*/

void remove_lista(t_lista* lista); /*REMOVENDO TODOS OS PRODUTOS*/

int inserir(int posicao, int codigo, char* nome, float preco, int quantidade, t_lista* lista); /*INSERINDO NOVOS PRODUTOS*/

void printa_lista(t_lista* lista); /*PRINTANDO TODOS OS PRODUTOS NA TELA*/

t_elemento* percorre_lista(int posicao, t_lista* lista); /*PERCORRENDO A LISTA PARA VERIFICAR ONDE O PRODUTO VAI SER INSERIDO*/

void inserir_meio(int posicao, int codigo, char* nome, float preco, int quantidade, t_lista* lista); /*INSERINDO O PRODUTO NA POSICAO INFORMADA E DIFERENTE DE DA INICIAL*/

void menu(t_lista* lista); /*INTERACAO COM O USUARIO*/

int resposta_menu(int opcao, t_lista* lista); /*RESPOSTA DA INTERACAO COM O USUARIO*/

int quantidade_pares(t_lista* lista); /*PEGANDO A QUANTIDADE DE PRODUTOS COM CODIGOS PARES*/

int preco_medio(t_lista* lista); /*CALCULANDO O PRECO MEDIO DOS PRODUTOS*/

void mensagem_vazio(); /*MENSAGEM DE ALERTA AO USUARIO QUANDO TENTA ACESSAR ALGUMA FUNCAO SEM NENHUM PRODUTO*/

int menor_preco(t_lista* lista);/*PEGANDO O VALOR DO PRODUTO MAIS BARATO*/

int maior_preco(t_lista* lista); /*PEGANDO O VALOR DO PRODUTO MAIS CARO*/

int id_maior_preco(t_lista* lista); /*PEGANDO O ID DO PRODUTO MAIS CARO*/

int valor_total(t_lista* lista);/*CALCULANDO O VALOR TOTAL DOS PRODUTOS*/

void pesquisa_produto(int codigo, t_lista* lista); /*PESQUISANDO PRODUTO PELO CODIGO*/

#endif