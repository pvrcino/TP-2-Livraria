//pasta criada para chamar as funções existentes na pasta "tAutor.c"
#ifndef TAUTOR_H
#define TAUTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//struct com todas as informações necessárias para armazenar os autores dos livros.
typedef struct tautor tAutor;

//função que cadastra um autor no sistema por meio do nome.
tAutor* criarAutor(char nome[]);

//função que deleta um determinado autor cadastrado no sistema.
void deletarAutor(tAutor* autor);

//funcao que recebe um vetor de autores e deleta todos os clientes presentes no vetor.
void deletarAutorList(tAutor** autores);

//função que deleta um determinado vetor de autores cadastrado no sistema.
void deletarAutores(tAutor** autor);

//função que descobre o nome do autor ao chamar a struct inteira.
char* getNomeAutor(tAutor* autor);

//função que procura um autor entre todos os que já foram cadastrados para descobrir qual é compatível com o que o usuário está buscando.
tAutor* getAutor(char nome[]);

// função que retorna um vetor com todos os tAutores que possuem caracteres semelhantes.
tAutor** getAutores(char nome[]);

//transforma uma string com nomes de autores separados por "/" em um vetor de tAutores
void registrarAutores(char nomes[], tAutor** autores);

//função que deleta todos os autores do sistema.
void deletarAllAutores();

//verifica se existe um determinado autor escolhido pelo usuário dentro de um vetor de autores.
bool autorListContains(tAutor* autores[], tAutor* autor);

//função que cria uma estrutura em formato de vetor com todos os autores.
void inicializarAutores(int size);

#endif