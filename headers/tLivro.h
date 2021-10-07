//pasta criada para chamar as funções existentes na pasta "tLivro.c"
#ifndef TLIVRO_H
#define TLIVRO_H

#include "tAutor.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>

//struct que contém todas as informações necessárias para cadastrar e armazenar os livros no sistema.
typedef struct tlivro tLivro;

typedef tLivro**(*fptrPesquisa)(char*);

//função que cadastra um livro no sistema.
tLivro* cadastrar_livro(int id, char titulo[], tAutor* autores[], char* editora, double valor, double nota, int ano);

//função que retorna apenas a editora do livro ao receber todas as suas informações por meio da struct tLivro.
char* retorna_editora(tLivro* livro);

//função que retorna apenas a nota do livro ao receber todas as suas informações por meio da struct tLivro.
double retorna_nota(tLivro* livro);

//função que retorna apenas o autor do livro ao receber todas as suas informações por meio da struct tLivro.
tAutor** retorna_autores(tLivro* livro);

//deleta um livro cadastrado no sistema
void deletarLivro(tLivro* livro);

//deleta um vetor de livros cadastrado no sistema
void deletarLivros(tLivro** livro);

//funcao que recebe um vetor de livros e deleta todos os livros presentes no vetor.
void deletarLivrosList(tLivro* livros[]);

//deleta todos os livros cadastrados.
void deletarAllLivros();

//função que recebe a quantidade disponível para cadastro que um determinado livro possui e adiciona algumas unidades baseado no que o usuário pedir.
void adicionarUnidades(tLivro* livro, int units);

//função que atualiza o arquivo "books_-_books.csv" toda vez que um livro é cadastrado.
void adicionarLivroFile(tLivro* livro);

//função que recebe a quantidade disponível para cadastro que um determinado livro possui e remove algumas unidades baseado no que o usuário pedir.
void removerUnidades(tLivro* livro, int units);

//função que retorna apenas o título do livro ao receber todas as suas informações por meio da struct tLivro.
char* getTitulo(tLivro* livro);

//função que retorna apenas o valor do livro ao receber todas as suas informações por meio da struct tLivro.
double getValorLivro(tLivro* livro);

//função que retorna apenas o ano de publicação do livro ao receber todas as suas informações por meio da struct tLivro.
int getAnoLivro(tLivro* t);

//função que retorna apenas as unidades disponíveis do livro ao receber todas as suas informações por meio da struct tLivro.
int getUnidades(tLivro* livro);

//função que procura um título de um livro entre todos as que já foram cadastrados para descobrir qual é compatível com o que o usuário está buscando.
tLivro* getLivroByTitulo(char* titulo);

//função que procura uma id de um livro entre todas as que já foram cadastradas para descobrir qual é compatível com a que o usuário está buscando.
tLivro* getLivro(int id);

//função que chama todos os livros.
tLivro** getAllLivros();

//função que retorna apenas a id do livro ao receber todas as suas informações por meio da struct tLivro.
int getId(tLivro* t);

//cria uma estrutura em formato de vetor com todos os livros.
void inicializarLivros(int size);

//função que procura um título de um livro entre todas as que já foram cadastradas para descobrir qual é compatível com a que o usuário está buscando.
tLivro** pesquisaTitulo(char* titulo);

//função que exclui um livro da pasta "livros.csv"
void excluirLivro(tLivro* livro);

//função que preenche a tabela de dispersão
void inicializaPesquisa();

//função que preenche um vetor com todos os livros de um autor
tLivro** pesquisaAutor(char* nomeAutor);

//função auxiliar que retorna um vetor de tLivros dependendo do tipo de busca que foi informado na chamada da função.
tLivro** Pesquisa(char *valor, char TipoBusca);

#endif