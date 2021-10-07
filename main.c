#include <stdio.h>
#include "headers/Menu.h"

void leLivros();

int main() {
  inicializaPesquisa();
  inicializarLivros(11000);
  inicializarAutores(4000);
  leLivros();

  system("clear");

  menu0();
  
  finalizar();
}

//Função criada para ler todas as informações do arquivo livros.csv".
void leLivros() {
  char linha[1024], temp_titulo[256], temp_id[15], temp_autores[768], temp_nota[10], temp_valor[20], temp_data[20], temp_editora[128], temp_units[10];

  tAutor* autores[60] = {NULL};

  int i = -1, trash, ano;
  FILE *temp;

  //comando para abrir o arquivo "livros.csv".
  temp = fopen("db/livros.csv", "r");

  //verificando abertura do arquivo
  if (temp == NULL) {
    printf("Erro ao abrir o arquivo /db/livros.csv");
  }

  //enquanto o arquivo não acabar, o programa deverá ler o que está escrito nele.
  while (!feof(temp)) {
    fscanf(temp, "%[^\n]\n", linha);
    if (i >= 0) {

      int j = 0;
      while (autores[j] != NULL) {
        autores[j] = NULL;
        j++;
      }
      //em cada linha do arquivo, o programa separa em partes, de acordo com sua utilidade.
      sscanf(linha, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", temp_id, temp_titulo, temp_autores, temp_nota, temp_valor,temp_data, temp_editora, temp_units);
      sscanf(temp_data, "%d/%d/%d", &trash, &trash, &ano);

      registrarAutores(temp_autores, autores);

      tLivro* livro = cadastrar_livro(atoi(temp_id), temp_titulo, autores, temp_editora, atof(temp_valor),atof(temp_nota), ano);

      adicionarUnidades(livro, atoi(temp_units)-1);

    }
    i=0;
  }
  //fechando o arquivo "livros.csv".
  fclose(temp);
}