#include "../headers/Menu.h"

//função criada para organizar melhor o programa. Essa em específico possui o primeiro menu que aparecerá ao rodar o programa.
void menu0() {
  int num;
  do {
    //a primeira coisa que aparece na tela quando o programa roda.
    printf ("1- Cadastrar Livro\n");
    printf ("2- Buscar Livro\n");
    printf ("0- Sair\n");

    //é necessário escolher uma das opções dentre as existentes acima, escolhendo um número de 1 a 3 para selecionar a opção desejada.
    scanf("%i", &num);

    //switch case criado para que o programa realize diferentes ações dependendo da opção escolhida pelo usuário.
    switch(num){
      //se o usuario escolher a opcao "cadastrar livro".
      case 1:
        cadastrarLivro();
        break;
      //se o usuario escolher a opcao "buscar livro".
      case 2:
        system("clear");
        menu_busca();
        break; 
      //se o usuario escolher a opcao "sair".
      case 0:
        finalizar();
        break;
      //se o usuario escolher uma opcao diferente das disponiveis para escolha.
      default:
        system("clear");
        printf("Opcao invalida.\n\n");
        menu0();
        break;
    }

  }
  while(num != 0);
}

//função criada para caso o usuário escolha a opção 1 no menu0. Ela permite o cadastro de um livro no sistema
void cadastrarLivro(){
  system("clear");

  int qnt, id, ano, qntAutores, n, i, dia, mes;
  char aux_autor[512], aux_editora[128], titulo[128];
  tAutor* autores[60] = {NULL};
  double nota,valor;

  printf("Título: ");
  scanf("\n%[^\n]", titulo);

  printf("ID: ");
  scanf("%d", &id);

  if (getLivro(id) != NULL) {
    system("clear");
    printf("Já existe um livro com esse ID!\nTitulo: %s\n\n", getTitulo(getLivro(id)));
    menu0();
  } else {
    printf("Autores: ");
    scanf("%d", &qntAutores);
    for (i = 0; i < qntAutores; i++) {
      scanf("\n%[^\n]", aux_autor);
      autores[i] = criarAutor(aux_autor);
    }

    printf("Nota: ");
    scanf("%lf", &nota);

    printf("Valor: ");
    scanf("%lf", &valor);

    printf("Data de Publicação: ");
    scanf("%d/%d/%d", &dia, &mes, &ano);

    printf("Editora: ");
    scanf("\n%[^\n]", aux_editora);

    printf("Quantidade de exemplares: ");
    scanf("%d", &qnt);

    system("clear");

    tLivro *l = cadastrar_livro(id, titulo, autores, aux_editora, valor,nota,ano);
    adicionarUnidades(l, qnt-1);
    adicionarLivroFile(l);
    printf("Livro cadastrado com sucesso!\n\n");

    printf ("1- Voltar\n");
    printf ("2- Sair\n");

    while (n!= 2) {
      scanf("%i", &n);
      switch(n){
        case 1:
          system("clear");
          menu0();
          break;
        case 2:
          finalizar();
          break;
        default:
          system("clear");
          printf("Opcao invalida.\n\n");
          cadastrarLivro();
          break;
      };
    }
  }

}

//menu criado caso o usuário escolha a opcao 2 no menu0. Ela faz com que seja aberto um segundo menu, onde o usuário poderá pesquisar por um livro que ele deseja encontrar.
void menu_busca(){
  int n;
  //esse menu aparecerá sempre que a opção escolhida no switch case logo abaixo for diferente de 5.
  do{
    //função usada para limpar a tela
    //o que aparece na tela ao se escolher menu2.
    printf ("1- Pesquisar Por Autor\n");
    printf ("2- Pesquisar Por Título\n");
    printf ("3- Pesquisar Por Nota\n");
    printf ("4- Pesquisar Por ID\n");
    printf ("9- Voltar\n");
    printf ("0- Sair\n");

    //é necessário escolher uma das opções dentre as existentes acima, escolhendo um número de 1 a 4 para selecionar a opção desejada. 
    scanf("%d", &n);

    //switch case criado para que o programa realize diferentes ações dependendo da opção escolhida pelo usuário.
    switch(n){
      //caso o usuario escolha "pesquisar por autor".
      case 1:
        system("clear");
        usuario_pesquisaAutor();
        break;
      //caso o usuario escolha "pesquisar por titulo".
      case 2:
        system("clear");
        usuario_pesquisaTitulo();
        break;
      //caso o usuario escolha "pesquisar por nota".
      case 3:
        system("clear");
        usuario_pesquisaNota();
        break;
      //caso o usuario escolha "pesquisar por id".
      case 4:
        system("clear");
        usuario_pesquisaId();
        break;
      //caso o usuario escolha "voltar".
      case 9:
        system("clear");
        menu0();
        break;
      //caso o usuario escolha "sair".
      case 0:
        finalizar();
        break;
      //caso o usuario não escolha nenhuma das opcoes disponíveis
      default:
        system("clear");
        printf("Opcao invalida.\n\n");
        menu_busca();
        break;

    };
  }
  while(n!=5);
}

//função que apresenta o menu que aparece ao final de cada caso do menu_busca. Essa função permite que o usuário possa exlcluir um livro do sistema, caso seja da vontade dele.
void menu_final(){
  int n;
  printf("1 - Exclusao\n");
  printf("9 - Voltar\n");
  printf("0 - Sair\n");

  scanf("%i", &n);

//switch case criado para que o programa realize diferentes ações dependendo da opção escolhida pelo usuário.
  switch(n){
    //caso o usuário escolha a opcao "Exclusao".
    case 1:
    system("clear");
    menu_exclusao();
    break;

    //caso o usuário escolha a opcao "Voltar".
    case 9:
    system("clear");
    menu0();
    break;

    //caso o usuário escolha a opcao "Sair".
    case 0:
    finalizar();
    break;
    
    //caso o usuario não escolha nenhuma das opcoes disponíveis
    default:
      system("clear");
      printf("Opcao invalida.\n\n");
      menu_final();
      break;
  }
}

//função que apresenta o menu criado para o caso de o usuário escolher a opção "Exclusao" no "menu_final". Ao entrar na função, surge um novo menu na tela, em que o usuário pode escolher diferentes formas de excluir um livro do sistema.
void menu_exclusao(){
  int n, id, j = 0;
  tLivro* livro;

  printf("Informe o ID a ser excluído: ");
  scanf("%i", &id);
  livro = getLivro(id);

  printf("Titulo: %s\n", getTitulo(livro));
  printf("Autores: ");
  tAutor* autor = retorna_autores(livro)[j];
  tAutor* aux;
  while (autor != NULL) {
    printf("%s", getNomeAutor(autor));
    j++;
    aux = retorna_autores(livro)[j];
    if (aux != NULL) {
      printf(", ");
    }
    autor = aux;
  }
  printf("\nEditora: %s\n", retorna_editora(livro));
  printf("Exemplares: %d\n", getUnidades(livro));
  printf("Ano: %d\n", getAnoLivro(livro));
  printf("\n\n");

  printf ("1- Deletar o livro\n");
  printf ("2- Atualizar o numero de exemplares\n");
  printf ("9- Voltar\n");
  printf ("0- Sair\n");
  
  scanf("%d", &n);

//switch case criado para que o programa realize diferentes ações dependendo da opção escolhida pelo usuário.
  switch(n){
  //caso o usuário escolha a opção "Deletar o livro".
    case 1:
      usuario_confirmaExclusao(livro);
      break;
  
  // caso o usuário escolha a opção "Atualizar o número de exemplares".
    case 2:
      system("clear");
      atualizaExemplar(getUnidades(livro), livro);
      break;

  //caso o usuário escolha a opção "Voltar".
    case 9:
      system("clear");
      menu0();
      break;

  //caso o usuário escolha a opção "Sair".
    case 0:
      finalizar();
      break;

    //caso o usuario não escolha nenhuma das opcoes disponíveis
    default:
      system("clear");
      printf("Opcao invalida.\n\n");
      menu_exclusao();
      break;

  }
}

//Função que finaliza o programa e fecha tudo que foi aberto durante a compilação do programa.
void finalizar() {
  system("clear");
  printf("Programa finalizado!");

  deletarAllLivros();
  deletarAllAutores();
  exit(EXIT_SUCCESS);
}

//Função que aparece caso o usuário escolha a opção 1 do "menu_busca". Ela permite que o usuário encontre todos os livros que estão disponíveis na biblioteca e pertencem a um determinado autor.
void usuario_pesquisaAutor() {
  char shortName[128];
  int i = 0, j = 0;
  
  system("clear");
  printf("Autor do livro: ");
  scanf("\n%[^\n]", shortName);

  tAutor** autores = getAutores(shortName);
  system("clear");

  tLivro** livros = NULL;
  if (autores == NULL) {
    system("clear");
    printf("Livro não encontrado!\n\n");
    menu_busca();
  } else {
    tAutor* aux = autores[i];
    while (aux != NULL) {
      printf("Autor do livro: %s\n\n", getNomeAutor(aux));

      livros = Pesquisa(getNomeAutor(aux), 'a');
      tLivro* livro = livros[j];
      while (livro != NULL) {
        printf("Titulo %d: %s\n", j+1, getTitulo(livro));
        printf("ID %d: %d\n", j+1, getId(livro));
        printf("Editora %d: %s\n", j+1, retorna_editora(livro));
        printf("Nota %d: %.2lf\n", j+1, retorna_nota(livro));
        printf("Exemplares %d: %d\n", j+1, getUnidades(livro));
        printf("Ano %d: %d\n", j+1, getAnoLivro(livro));

        printf("\n");
        livro = livros[j+1];
        j++;
      }
      j = 0;
      printf("\n");
      deletarLivros(livros);
      aux = autores[i+1];
      i++;
    }
    deletarAutores(autores);
    menu_final();
  }
}

//Função que aparece caso o usuário escolha a opção 2 do "menu_busca". Ela permite que o usuário encontre todos os livros que estão disponíveis na biblioteca e possui um determinado título.
void usuario_pesquisaTitulo(){
  int i = 0, j = 0;

  system("clear");
  printf("Titulo do Livro: ");
  char titulo[256];
  scanf("\n%[^\n]", titulo);
  tLivro** livros = Pesquisa(titulo, 't');
  printf("\n");
  if (livros == NULL) {
    system("clear");
    printf("Livro não encontrado!\n\n");
    menu_busca();
  } else {
    tLivro* t = livros[i];
    while (t != NULL) {
      printf("\n");
      printf("Titulo %d: %s\n", i+1, getTitulo(t));
      printf("ID %d: %d\n", i+1, getId(t));
      printf("Autores %d: ", i+1);
      j=0;
      tAutor* autor = retorna_autores(t)[j];
      tAutor* aux;
      while (autor != NULL) {
        printf("%s", getNomeAutor(autor));
        j++;
        aux = retorna_autores(t)[j];
        if (aux != NULL) {
          printf(", ");
        }
        autor = aux;
      }
      printf("\nEditora %d: %s\n", i+1, retorna_editora(t));
      printf("Nota %d: %.2lf\n", i+1, retorna_nota(t));
      printf("Exemplares %d: %d\n", i+1, getUnidades(t));
      printf("Ano %d: %d\n", i+1, getAnoLivro(t));
      t = livros[i+1];
      i++;
    }
    printf("\n\n");
    deletarLivros(livros);
    menu_final();
  }
}

//Função que aparece caso o usuário escolha a opção 3 do "menu_busca". Ela permite que o usuário encontre todos os livros que estão disponíveis na biblioteca e possuem uma determinada nota.
void usuario_pesquisaNota(){
  int i = 0, j = 0;

  system("clear");
  printf("Nota do Livro: ");
  char nota[10];
  scanf("\n%[^\n]", nota);
  tLivro** livros = Pesquisa(nota, 'n');
  printf("\n");
  if (livros == NULL) {
    system("clear");
    printf("Livro não encontrado!\n\n");
    menu_busca();
  } else {
    tLivro* t = livros[i];
    while (t != NULL) {
      printf("\n");
      printf("Titulo %d: %s\n", i+1, getTitulo(t));
      printf("ID %d: %d\n", i+1, getId(t));
      printf("Autores %d: ", i+1);
      j=0;
      tAutor* autor = retorna_autores(t)[j];
      tAutor* aux;
      while (autor != NULL) {
        printf("%s", getNomeAutor(autor));
        j++;
        aux = retorna_autores(t)[j];
        if (aux != NULL) {
          printf(", ");
        }
        autor = aux;
      }
      printf("\nEditora %d: %s\n", i+1, retorna_editora(t));
      printf("Nota %d: %.2lf\n", i+1, retorna_nota(t));
      printf("Exemplares %d: %d\n", i+1, getUnidades(t));
      printf("Ano %d: %d\n", i+1, getAnoLivro(t));
      t = livros[i+1];
      i++;
    }
    printf("\n\n");
    deletarLivros(livros);
    menu_final();
  }
}

//Função que aparece caso o usuário escolha a opção 4 do "menu_busca". Ela permite que o usuário encontre todos os livros que estão disponíveis na biblioteca e possuem uma determinada ID.
void usuario_pesquisaId(){
  int j = 0;

  printf("ID do Livro: ");
  char id[10];
  scanf("\n%[^\n]", id);
  tLivro** livros = Pesquisa(id, 'i');
  printf("\n");
  if (livros == NULL) {
    system("clear");
    printf("Livro não encontrado!\n\n");
    menu_busca();
  } else {
    tLivro* t = livros[0];
    printf("\n");
    printf("Titulo: %s\n", getTitulo(t));
    printf("Autores: ");
    tAutor* autor = retorna_autores(t)[j];
    tAutor* aux;
    while (autor != NULL) {
      printf("%s", getNomeAutor(autor));
      j++;
      aux = retorna_autores(t)[j];
      if (aux != NULL) {
        printf(", ");
      }
      autor = aux;
    }
    printf("\nEditora: %s\n", retorna_editora(t));
    printf("Exemplares: %d\n", getUnidades(t));
    printf("Ano: %d\n\n", getAnoLivro(t));
    deletarLivros(livros);
    menu_final();
  }
}

//Função que é aberta caso o usuário escolha a opção 1 no "menu_exclusao". Ela permite que o usuário exclua o livro da biblioteca, retirando todas as cópias que ele possui no programa.
void usuario_confirmaExclusao(tLivro* livro) {
  int n = -1;
  system("clear");
  printf("Tem certeza de que deseja deletar o livro de ID: %d?\n\n", getId(livro));
  //switch case criado para que o programa realize diferentes ações dependendo da opção escolhida pelo usuário.
  printf ("1- SIM\n");
  printf ("2- NAO\n");
  scanf("%d", &n);
  switch(n){
    case 1:
      system("clear");
      excluirLivro(livro);
      printf("Livro deletado com sucesso!\n\n");
      menu0();
      break;
    case 2:
      system("clear");
      printf("Livro não foi deletado!\n\n");
      menu0();
      break;
    default:
      usuario_confirmaExclusao(livro);
      break;
  }
}

//Função que aparece quando o usuário escolhe a opção 2 no "menu_exclusao". Ela permite que o usuário exclua apenas alguns exemplares do livro, retirando o livro por completo apenas quando a quantidade de exemplares acabar.
void atualizaExemplar(int qtd, tLivro *livro){
  int unid, exemplar;
  
  printf("Informe a quantidade de exemplares a ser excluidas: ");
  scanf("%d", &qtd);

  unid = getUnidades(livro);

  exemplar = unid - qtd;

  if (exemplar == 0){
    system("clear");
    excluirLivro(livro);
    printf("O livro foi deletado, pois atingiu 0 exemplares.\n\n");
    menu0();
  }

  else if (exemplar > 0){
    system("clear");
    printf("Foram excluídos %d exemplares.\n\n", qtd);
    removerUnidades(livro, qtd);
    menu0();
  }

  else{
    system("clear");
    printf("Opcao Invalida.\n\n");
    menu0();
  }
}