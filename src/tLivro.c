 //pasta criada para organizar todas as funções que estão relacionadas aos livros da biblioteca.
#include "../headers/tLivro.h"

//struct que contém todas as informações necessárias para cadastrar e armazenar os livros no sistema.
struct tlivro {
  int id;
  char titulo[128];
  char editora[128];
  double valor;
  double nota;
  int ano;
  int unidades;

  tAutor* autores[60];
};

fptrPesquisa pesquisas[20] = {NULL}; //117-97

//variáveis globais que serão utilizadas em diversas funções.
tLivro** allLivros;
int allLivros_size;
int livrosCounter = 0;


//cria uma estrutura em formato de vetor com todos os livros.
void inicializarLivros(int size) {
  allLivros = realloc(allLivros, size*sizeof(struct tlivro));
  allLivros_size = size;
  if (allLivros == NULL) {
    allLivros = realloc(allLivros, size*sizeof(struct tlivro));
    for (int i = 0; i < size; i++) {
      allLivros[i] = NULL;
    }
  }
}

//função que procura uma id de um livro entre todas as que já foram cadastradas para descobrir qual é compatível com a que o usuário está buscando.
tLivro* getLivro(int id) {
  for (int i = 0; i < livrosCounter; i++){
    if (allLivros[i] == NULL) return NULL;
    if (allLivros[i]->id == id) {
      return allLivros[i];
    }
  }
  return NULL;
}


//função que procura um título de um livro entre todos as que já foram cadastrados para descobrir qual é compatível com o que o usuário está buscando.
tLivro* getLivroByTitulo(char* titulo) {
  tLivro* t = NULL;
  for(int i = 0; i < livrosCounter; i++){
    if (allLivros[i] == NULL) return NULL;
    if (strcmp(allLivros[i]->titulo, titulo) == 0) {
      t = allLivros[i];
    }
  }
  return t;
}

//função que retorna apenas o título do livro ao receber todas as suas informações por meio da struct tLivro.
char* getTitulo(tLivro* livro) {
  return livro->titulo;
}

//função que retorna apenas o autor do livro ao receber todas as suas informações por meio da struct tLivro.
tAutor** retorna_autores(tLivro* livro) {
  return livro->autores;
}

//função que retorna apenas a nota do livro ao receber todas as suas informações por meio da struct tLivro.
double retorna_nota(tLivro* livro) {
  return livro->nota;
}

//função que preenche um vetor com todos os livros de um autor
tLivro** pesquisaAutor(char* nomeAutor) {
  tLivro** livros = NULL;
  int i = 0,j = 0;
  tLivro* aux = allLivros[i];
  while (aux != NULL) {
    if (autorListContains(aux->autores, getAutor(nomeAutor))) {
      livros = realloc(livros, (j+2)*sizeof(struct tlivro));
      livros[j] = aux;
      livros[j+1] = NULL;
      j+=1;
    }
    aux = allLivros[i+1];
    i++;
  }
  return livros;
}

//função que procura uma id de um livro entre todas as que já foram cadastradas para descobrir qual é compatível com a que o usuário está buscando.
tLivro** pesquisaId(char* id) {
  int i_id = atoi(id);
  tLivro** livros;
  livros = malloc(sizeof(struct tlivro));
  tLivro* livro = getLivro(i_id);
  if (livro != NULL) {
    livros[0] = livro;
    return livros;
  }
  return NULL;
}

//função que procura uma nota de um livro entre todas as que já foram cadastradas para descobrir qual é compatível com a que o usuário está buscando.
tLivro** pesquisaNota(char* nota) {
  int i = 0,j = 0;
  double dnota = strtod(nota, NULL);
  tLivro** livros = NULL;
  tLivro* aux = NULL;

  for (i = 0; i<livrosCounter; i++) { 
    aux = allLivros[i];
    if (aux->nota == dnota) {
      livros = realloc(livros, (j+2)*sizeof(struct tlivro));
      livros[j] = aux;
      livros[j+1] = NULL;
      j+=1;
    }
  }
  return livros;
}

//função que procura um título de um livro entre todas as que já foram cadastradas para descobrir qual é compatível com a que o usuário está buscando.
tLivro** pesquisaTitulo(char* titulo) {
  tLivro** livros = NULL;

  int i = 0, j = 0, counter = 0;
  char compare[256];
  char convertedTitulo[256];
  
  strcpy(convertedTitulo, titulo);
  for(j = 0; convertedTitulo[j]; j++){
    convertedTitulo[j] = tolower(convertedTitulo[j]);
  }
  
  while (allLivros[i] != NULL) {
    strcpy(compare, allLivros[i]->titulo);
    for( j = 0; compare[j]; j++){
      compare[j] = tolower(compare[j]);
    }
    
    if (strstr(compare, convertedTitulo) != NULL) {
      livros = realloc(livros, (counter+2)*sizeof(struct tlivro));
      livros[counter] = allLivros[i];
      livros[counter+1] = NULL;
      counter++;
    }
    i++;
  }
  return livros;
}

//função que chama todos os livros.
tLivro** getAllLivros() {
  return allLivros;
}

//função que retorna apenas a editora do livro ao receber todas as suas informações por meio da struct tLivro.
char* retorna_editora(tLivro* livro) {
  return livro->editora;
}

//função que recebe a quantidade disponível para cadastro que um determinado livro possui e adiciona algumas unidades baseado no que o usuário pedir.
void adicionarUnidades(tLivro* livro, int units) {
  livro->unidades = livro->unidades + units;
}


//função que recebe a quantidade disponível para cadastro que um determinado livro possui e remove algumas unidades baseado no que o usuário pedir.
void removerUnidades(tLivro* livro, int units) {
  int i = 0;

  livro->unidades = livro->unidades - units;
  unlink("./db/livros.csv");

  FILE *temp;
  temp = fopen("./db/livros.csv", "w");
  fprintf(temp, "bookID,title,authors,average_rating,valor,publication_date,publisher,units");
  fclose(temp);

  while (allLivros[i] != NULL) {
    adicionarLivroFile(allLivros[i]);
    i++;
  }
}

//função que cadastra um livro no sistema.
tLivro* cadastrar_livro(int id, char titulo[], tAutor* autores[], char* editora, double valor, double nota, int ano) {
  tLivro* livro = getLivro(id);
  if (livro == NULL) {
    if (livrosCounter == allLivros_size) {
      inicializarLivros(livrosCounter + 1);
    }
    livro = (tLivro*) malloc(sizeof(struct tlivro));

    strcpy(livro->titulo, titulo);
    livro->id = id;
    livro->valor = valor;
    livro->nota = nota;
    livro->ano = ano;
    strcpy(livro->editora, editora);
    livro->unidades = 1;
    for (int i = 0; i < 60; i++) {
      livro->autores[i] = autores[i];
    }

    allLivros[livrosCounter] = livro;
    livrosCounter++;
  } else {
    adicionarUnidades(livro, 1);
  }
  return livro;
}

//função que exclui um livro da pasta "livros.csv"
void excluirLivro(tLivro* livro) {
  int i = 0, pos = -1;

  unlink("./db/livros.csv");

  FILE *temp;
  temp = fopen("./db/livros.csv", "w");
  fprintf(temp, "bookID,title,authors,average_rating,valor,publication_date,publisher,units");
  fclose(temp);

  while (allLivros[i] != NULL) {
    if (livro == allLivros[i]) {
      pos = i;
    } else {
      adicionarLivroFile(allLivros[i]);
    }

    if (i >= pos) {
      allLivros[i] = allLivros[i+1];
    }
    i++;
  }


  deletarLivro(livro);
  inicializarLivros(livrosCounter);
  
  livrosCounter--;
  allLivros_size--;

}

//função que atualiza o arquivo "books_-_books.csv" toda vez que um livro é cadastrado.
void adicionarLivroFile(tLivro* livro) {
  FILE *temp;
  temp = fopen("./db/livros.csv", "a");
  char aux_autores[1024] = "", data[30] = "1/01/", aux[10];
  int i = 0;

  tAutor* autor = retorna_autores(livro)[i];
  tAutor* autoraux;
  
  while (autor != NULL) {
    strcat(aux_autores, getNomeAutor(autor));
    i++;
    autoraux = retorna_autores(livro)[i];
    if (autoraux != NULL) {
      strcat(aux_autores, "/");
    }
    autor = autoraux;
  }
    
  sprintf(aux, "%d", livro->ano);
  strcat(data, aux);
  fprintf(temp, "\n%d,%s,%s,%.2lf,%.2lf,%s,%s,%d", livro->id, livro->titulo, aux_autores, livro->nota, livro->valor, data, livro->editora, getUnidades(livro));

  fclose(temp);
}

void deletarLivroFromList(tLivro* livro) {
  int pos = -1, i;
  for (i = 0; i < livrosCounter; i++) {
    if (allLivros[livrosCounter] == livro) {
      pos = i;
    }
    if (pos > i) {
      allLivros[livrosCounter] = allLivros[livrosCounter+1];
    }
  }
  livrosCounter--;
  inicializarLivros(livrosCounter);
}

//funcao que recebe um vetor de livros e deleta todos os livros presentes no vetor.
void deletarLivrosList(tLivro** livros) {
  int i = 0;
  tLivro *t = livros[i];
  tLivro *aux = livros[i+1];
  while(t != NULL){
    deletarLivro(t);
    if (i == (livrosCounter-1)) {
      break;
    }
    aux = livros[i+1];
    t = aux;
    i++;
  }
  free(livros);
}

//função que retorna apenas a id do livro ao receber todas as suas informações por meio da struct tLivro.
int getId(tLivro* t) {
  return t->id;
}

//deleta todos os livros cadastrados.
void deletarAllLivros() {
  deletarLivrosList(allLivros);
}

//deleta um livro cadastrado no sistema
void deletarLivro(tLivro* livro) {
  free(livro);
  livro = NULL;
}

//deleta um vetor de livros cadastrado no sistema
void deletarLivros(tLivro** livro) {
  free(livro);
  livro = NULL;
}

//função que retorna apenas o valor do livro ao receber todas as suas informações por meio da struct tLivro.
double getValorLivro(tLivro* livro) {
  return livro->valor;
}

//função que retorna apenas o ano de publicação do livro ao receber todas as suas informações por meio da struct tLivro.
int getAnoLivro(tLivro* livro) {
  return livro->ano;
}

//função que retorna apenas as unidades disponíveis do livro ao receber todas as suas informações por meio da struct tLivro.
int getUnidades(tLivro* livro) {
  return livro->unidades;
}


//função que preenche a tabela de dispersão
void inicializaPesquisa() {
  pesquisas['a'-97] = pesquisaAutor;
  pesquisas['t'-97] = pesquisaTitulo;
  pesquisas['n'-97] = pesquisaNota;
  pesquisas['i'-97] = pesquisaId;
}

//função auxiliar que retorna um vetor de tLivros dependendo do tipo de busca que foi informado na chamada da função.
tLivro** Pesquisa(char *valor, char TipoBusca) {
  return pesquisas[TipoBusca-97](valor);
}