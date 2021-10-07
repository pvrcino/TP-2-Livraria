#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include "tLivro.h"
#include "tAutor.h"

//função criada para organizar melhor o programa. Essa em específico possui o primeiro menu que aparecerá ao rodar o programa.
void menu0();

//função criada para caso o usuário escolha a opção 1 no menu0. Ela permite o cadastro de um livro no sistema
void cadastrarLivro();

//menu criado caso o usuário escolha a opcao 2 no menu0. Ela faz com que seja aberto um segundo menu, onde o usuário poderá pesquisar por um livro que ele deseja encontrar.
void menu_busca();

//função que apresenta o menu que aparece ao final de cada caso do menu_busca. Essa função permite que o usuário possa exlcluir um livro do sistema, caso seja da vontade dele.
void menu_final();

//função que apresenta o menu criado para o caso de o usuário escolher a opção "Exclusao" no "menu_final". Ao entrar na função, surge um novo menu na tela, em que o usuário pode escolher diferentes formas de excluir um livro do sistema.
void menu_exclusao();

//Função que finaliza o programa e fecha tudo que foi aberto durante a compilação do programa.
void finalizar();


//Função que aparece caso o usuário escolha a opção 1 do "menu_busca". Ela permite que o usuário encontre todos os livros que estão disponíveis na biblioteca e pertencem a um determinado autor.
void usuario_pesquisaAutor();

//Função que aparece caso o usuário escolha a opção 2 do "menu_busca". Ela permite que o usuário encontre todos os livros que estão disponíveis na biblioteca e possui um determinado título.
void usuario_pesquisaTitulo();

//Função que aparece caso o usuário escolha a opção 3 do "menu_busca". Ela permite que o usuário encontre todos os livros que estão disponíveis na biblioteca e possuem uma determinada nota.
void usuario_pesquisaNota();

//Função que aparece caso o usuário escolha a opção 4 do "menu_busca". Ela permite que o usuário encontre todos os livros que estão disponíveis na biblioteca e possuem uma determinada ID.
void usuario_pesquisaId();

//Função que é aberta caso o usuário escolha a opção 1 no "menu_exclusao". Ela permite que o usuário exclua o livro da biblioteca, retirando todas as cópias que ele possui no programa.
void usuario_confirmaExclusao(tLivro* livro);

//Função que aparece quando o usuário escolhe a opção 2 no "menu_exclusao". Ela permite que o usuário exclua apenas alguns exemplares do livro, retirando o livro por completo apenas quando a quantidade de exemplares acabar.
void atualizaExemplar(int qtd, tLivro *livro);

#endif