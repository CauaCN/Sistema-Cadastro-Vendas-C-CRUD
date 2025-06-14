
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cliente {
  char nome[50];
  char sexo[10];
  int idade;
};
typedef struct Cliente cliente;

struct Venda {
  cliente consumidor;
  int qtdItens;
  char unidade[10];
  float valorTotal;
}; // a estrutura cliente está dentro da venda
typedef struct Venda venda;

int menuPrincipal();
int valida(
    int x); // função para validar a entrada de numeros inteiros e positivos
int desejaRepetir();

int contarVendasAbaixoDe(float valor);
int contarVendasCom3Itens();
int contarVendasUnidadeB();
int contarCompradoresHomens();
void calcularTotalPorSexo(float *totalN, float *totalM);
int contarTotalItensVendidos();
void calcularTotalEMediaVendas(float *vendaTotal, float *mediaVendas);
float encontrarCompraMaisBarataMulher();
void exibirVendasClienteMaiorNome();
void exibirVendasClienteMaisNovo();
void buscaCliente(char busca[100]);
void deletaCliente();
void alterarCliente();

int main() {
  int opcao = -1; // iniciar o while com um valor diferente de 0 para nao sair
                  // do programa
  int qtd;
  venda *ptrvenda;
  FILE *fptr;

  while (opcao != 0) {
    opcao = menuPrincipal();

    char busca[50];
    char linha[200];
    int encontrado = 0;

    switch (opcao) {
    case 1: {
      system("clear");
      while (1) {
        printf("Quantidade de vendas a cadastrar: ");
        scanf("%d", &qtd);
        system("clear");

        ptrvenda = (venda *)malloc(qtd * sizeof(venda));
        if (ptrvenda == NULL) {
          printf("ERRO: Memoria Insuficiente\n");
        }
        getchar();

        fptr = fopen("loja.txt", "a");
        if (fptr == NULL) {
          printf("ERRO: Nao foi possivel abrir o arquivo\n");
          exit(1);
        }

        for (int i = 0; i < qtd; i++) {
          // nome
          do {
            printf("Nome do cliente: ");
            fgets(ptrvenda[i].consumidor.nome,
                  sizeof(ptrvenda[i].consumidor.nome), stdin);
            ptrvenda[i]
                .consumidor.nome[strcspn(ptrvenda[i].consumidor.nome, "\n")] =
                0;
            if (strlen(ptrvenda[i].consumidor.nome) <= 3) {
              printf("\nDigite um nome maior que 3 letras\n\n");
            }
          } while (strlen(ptrvenda[i].consumidor.nome) <= 3);
          for (int j = 0; ptrvenda[i].consumidor.nome[j] != '\0'; j++) {
            ptrvenda[i].consumidor.nome[j] =
                toupper(ptrvenda[i].consumidor.nome[j]);
          }
          fprintf(fptr, "%s\n", ptrvenda[i].consumidor.nome);

          // sexo
          do {
            printf("Sexo do cliente (M/F/N): ");
            fgets(ptrvenda[i].consumidor.sexo,
                  sizeof(ptrvenda[i].consumidor.sexo), stdin);
            ptrvenda[i]
                .consumidor.sexo[strcspn(ptrvenda[i].consumidor.sexo, "\n")] =
                0;
            ptrvenda[i].consumidor.sexo[0] =
                toupper(ptrvenda[i].consumidor.sexo[0]);
            if ((strcmp(ptrvenda[i].consumidor.sexo, "M") != 0) &&
                (strcmp(ptrvenda[i].consumidor.sexo, "F") != 0) &&
                (strcmp(ptrvenda[i].consumidor.sexo, "N") != 0)) {
              printf("\nERRO: Sexo invÃ¡lido.\n\n");
            } else {
              break;
            }
          } while (1);
          fprintf(fptr, "Sexo do cliente: %s\n", ptrvenda[i].consumidor.sexo);

          // idade
          do {
            printf("Idade do cliente: ");
            scanf("%d", &ptrvenda[i].consumidor.idade);
            if (valida(ptrvenda[i].consumidor.idade) == 0) {
              printf("\nERRO: Numero invalido\n\n");
            } else {
              break;
            }
          } while (1);
          getchar();
          fprintf(fptr, "Idade do cliente: %d\n", ptrvenda[i].consumidor.idade);

          // qtd itens
          do {
            printf("Quantidade de itens: ");
            scanf("%d", &ptrvenda[i].qtdItens);
            if (valida(ptrvenda[i].qtdItens) == 0) {
              printf("\nERRO: Numero invÃ¡lido\n\n");
            } else {
              break;
            }
          } while (1);
          getchar();
          fprintf(fptr, "Quantidade de itens: %d\n", ptrvenda[i].qtdItens);

          // unidade comercial
          do {
            printf("Unidade comercial da venda: (A/B/C)");
            fgets(ptrvenda[i].unidade, sizeof(ptrvenda[i].unidade), stdin);
            ptrvenda[i].unidade[strcspn(ptrvenda[i].unidade, "\n")] = 0;
            ptrvenda[i].unidade[0] = toupper(ptrvenda[i].unidade[0]);
            if ((strcmp(ptrvenda[i].unidade, "A") != 0) &&
                (strcmp(ptrvenda[i].unidade, "B") != 0) &&
                (strcmp(ptrvenda[i].unidade, "C") != 0)) {
              printf("\nERRO: Unidade comercial invÃ¡lida.\n\n");
            } else {
              break;
            }
          } while (1);
          fprintf(fptr, "Unidade comercial da venda: %s\n",
                  ptrvenda[i].unidade);

          printf("Valor total da venda: ");
          scanf("%f", &ptrvenda[i].valorTotal);
          fprintf(fptr, "Valor total da venda: %.2f\n\n",
                  ptrvenda[i].valorTotal);

          getchar();
          system("clear");
          printf("Informacoes cadastradas com sucesso!\n\n");
          printf("Pressione Enter para continuar...");
          while (getchar() != '\n')
            ; // espera o usuario apertar enter
          system("clear");
        }

        fclose(fptr);

        if (!desejaRepetir()) {
          break;
        }
      }
      break;
    }

    case 2: {
      while (1) {
        system("clear");
        fptr = fopen("loja.txt", "r");
        if (fptr == NULL) {
          printf("ERRO: Não foi possivel abrir o arquivo\n");
          return 1;
        }

        printf("Nome a ser pesquisado: ");
        fgets(busca, sizeof(busca), stdin);
        busca[strcspn(busca, "\n")] = '\0';
        system("clear");
        for (int i = 0; busca[i] != '\0'; i++) {
          busca[i] = toupper(busca[i]);
        }

        qtd = 0;
        encontrado = 0;

        // apontar quantas vezes o cliente aparece no arquivo
        while (fgets(linha, sizeof(linha), fptr)) {
          linha[strcspn(linha, "\n")] = '\0';
          if (strcmp(busca, linha) == 0) {
            encontrado = 1;
            qtd++;
          }
        }
        printf("\n");
        if (!encontrado) {
          printf("Nenhum cliente encontrado com o nome '%s' :( \n", busca);
          fclose(fptr);
          printf("\nPressione Enter para continuar...");
          while (getchar() != '\n')
            ;
          system("clear");

          char resp[10];
          printf("\nRepetir operação? (S/N): ");
          fgets(resp, sizeof(resp), stdin);
          if (toupper(resp[0]) == 'N') {
            system("clear");
            break;
          }
          continue;
          system("clear");
        }

        // aloca vetor para armazenar os valores totais das compras
        float *valorTotalCompras = (float *)malloc(qtd * sizeof(float));
        int *qtdItens = (int *)malloc(qtd * sizeof(int));
        char *unidadeLoja = (char *)malloc(qtd * sizeof(char));
        if (valorTotalCompras == NULL) {
          printf("ERRO: Memoria insuficiente\n");
          fclose(fptr);
          break;
        }

        rewind(fptr);
        int index = 0;
        int lendoCliente = 0;

        while (fgets(linha, sizeof(linha), fptr)) {
          linha[strcspn(linha, "\n")] = '\0';

          if (strcmp(busca, linha) == 0) {
            lendoCliente = 1;
            continue;
          }

          if (lendoCliente) {
            sscanf(linha, "Quantidade de itens: %d", &qtdItens[index]);
            sscanf(linha, "Unidade comercial da venda: %c",
                   &unidadeLoja[index]);

            if (sscanf(linha, "Valor total da venda: %f",
                       &valorTotalCompras[index]) == 1) {
              index++;
              lendoCliente = 0;
            }
          }
        }

        // mostra os resultados
        float somaTotal = 0;
        for (int i = 0; i < qtd; i++) {

          printf("Valor total da compra %d: R$ %.2f\n", i + 1,
                 valorTotalCompras[i]);
          somaTotal += valorTotalCompras[i];
          printf("Quantidade de itens da compra %d: %d\n", i + 1, qtdItens[i]);
          printf("Unidade da compra %d: %c\n", i + 1, unidadeLoja[i]);
          printf("\n");
        }
        printf("Total gasto pelo cliente %s: R$ %.2f\n", busca, somaTotal);

        free(valorTotalCompras);
        free(qtdItens);
        free(unidadeLoja);
        fclose(fptr);

        printf("\nPressione Enter para continuar...");
        while (getchar() != '\n')
          ;
        system("clear");
        char resp[10];
        printf("\nRepetir operação? (S/N): ");
        fgets(resp, sizeof(resp), stdin);
        if (toupper(resp[0]) == 'N') {
          system("clear");
          break;
        }
        system("clear");
      }
      break;
    }

    case 3: {
      system("clear");
      float valor;
      char resp;

      printf("\nValor para filtrar vendas abaixo: ");
      scanf("%f", &valor);
      getchar();
      system("clear");

      printf("\nQuantidade de vendas abaixo de R$ %.2f: %d", valor,
             contarVendasAbaixoDe(valor));
      printf("\nQuantidade de vendas com exatos 3 itens: %d",
             contarVendasCom3Itens());
      printf("\nQuantidade de vendas na unidade B: %d", contarVendasUnidadeB());
      printf("\nQuantidade de compradores homens: %d",
             contarCompradoresHomens());

      float totalN = 0, totalM = 0;
      calcularTotalPorSexo(&totalN, &totalM);
      printf("\nTotal comprado por quem nC#o informou sexo: R$ %.2f", totalN);
      printf("\nTotal comprado por homens: R$ %.2f", totalM);

      printf("\nTotal de itens vendidos: %d", contarTotalItensVendidos());

      float vendaTotal = 0, mediaVendas = 0;
      calcularTotalEMediaVendas(&vendaTotal, &mediaVendas);
      printf("\nTotal das vendas: R$ %.2f", vendaTotal);
      printf("\nMC)dia das vendas: R$ %.2f", mediaVendas);

      printf("\nCompra mais barata feita por mulher: R$ %.2f",
             encontrarCompraMaisBarataMulher());
      exibirVendasClienteMaiorNome();
      exibirVendasClienteMaisNovo();

      printf("\nDeseja voltar ao menu? (S/N)");
      scanf(" %c", &resp);
      if (resp == 'S' || resp == 's') {
        system("clear");
        break;
      }

      else {
        system("clear");
        printf("\nPrograma finalizado...\n");
        return 0;
      }
    }

    case 4: {
      char resp;
      while (1) {
        deletaCliente();
        system("clear");
        printf("\nRepetir operação? (S/N)");
        scanf(" %c", &resp);
        getchar();
        if (resp == 'N' || resp == 'n') {
          system("clear");
          break;
        }
        system("clear");
      }
    }
    case 5: {
      char resp;
      while (1) {
        alterarCliente();
        system("clear");
        printf("\nRepetir operação? (S/N)");
        scanf(" %c", &resp);
        getchar();
        if (resp == 'N' || resp == 'n') {
          system("clear");
          break;
        }
        system("clear");
      }
    }
    }
  }
  system("clear");
  printf("\nPrograma finalizado...\n");
  free(ptrvenda);
  return 0;
}

int menuPrincipal() {
  int opcao;

  printf("=====================================\n");
  printf("           MENU PRINCIPAL            \n");
  printf("=====================================\n");
  printf("\n");
  printf("[1] - Cadastrar Novas Vendas\n");
  printf("[2] - Consultar Venda Específica\n");
  printf("[3] - Ver Todas as Vendas\n");
  printf("[4] - Deletar Cadastro\n");
  printf("[5] - Alterar Cadastro\n");
  printf("[0] - Sair\n");
  printf("\n=====================================\n");
  printf("\nDigite a opção desejada: ");
  scanf("%d", &opcao);
  getchar();

  return opcao;
}

void buscaCliente(char busca[100]) {
  FILE *fptr = fopen("loja.txt", "r");
  if (fptr == NULL) {
    printf("ERRO: Nao foi possivel abrir o arquivo\n");
    return;
  }

  char linha[100];
  int encontrado = 0;
  int imprimir = 0;

  printf("\nResultados para '%s':\n", busca);

  while (fgets(linha, sizeof(linha), fptr)) {
    linha[strcspn(linha, "\n")] = '\0';

    if (strcmp(busca, linha) == 0) {
      encontrado = 1;
      printf("\nCliente encontrado:\n");
      printf("Nome do cliente: %s\n", busca);
      do {
        fgets(linha, sizeof(linha), fptr);
        printf("%s", linha);
        imprimir++;
      } while (imprimir < 5);
      imprimir = 0;
    }
  }

  if (encontrado == 0) {
    printf("Nenhum cliente encontrado com o nome '%s'\n", busca);
  }

  fclose(fptr);
}

int valida(int x) {
  if (x > 0) {
    return 1;
  }
  return 0;
}

int desejaRepetir() {
  char resp[10];
  while (1) {
    printf("\nDeseja repetir a operação? (S/N)\n");
    fgets(resp, sizeof(resp), stdin);
    resp[strcspn(resp, "\n")] = 0;
    if (toupper(resp[0]) == 'S') { // toupper para M/m
      system("clear");
      return 1;
    }
    if (toupper(resp[0]) == 'N') {
      system("clear");
      return 0;
    } else {
      printf("\nERRO: Opção inválida.\n");
    }
  }
}

int contarVendasAbaixoDe(float valor) {
  FILE *fptr = fopen("loja.txt", "r");
  if (fptr == NULL) {
    printf("ERRO: Não foi possível abrir o arquivo\n");
    return -1;
  }

  int qtdVendas = 0;
  char linha[200];
  while (fgets(linha, sizeof(linha), fptr)) {
    float valorVenda;
    if (sscanf(linha, "Valor total da venda: %f", &valorVenda) == 1) {
      if (valorVenda < valor)
        qtdVendas++;
    }
  }
  rewind(fptr);
  fclose(fptr);
  return qtdVendas;
}

int contarVendasCom3Itens() {
  FILE *fptr = fopen("loja.txt", "r");
  if (fptr == NULL)
    return -1;

  int qtdEspecifica = 0;
  char linha[200];
  while (fgets(linha, sizeof(linha), fptr)) {
    int qtdItens;
    if (sscanf(linha, "Quantidade de itens: %d", &qtdItens) == 1) {
      if (qtdItens == 3)
        qtdEspecifica++;
    }
  }
  rewind(fptr);
  fclose(fptr);
  return qtdEspecifica;
}

int contarVendasUnidadeB() {
  FILE *fptr = fopen("loja.txt", "r");
  if (fptr == NULL)
    return -1;

  int qtdUnidade = 0;
  char linha[200];
  while (fgets(linha, sizeof(linha), fptr)) {
    char unidade;
    if (sscanf(linha, "Unidade comercial da venda: %c", &unidade) == 1) {
      if (unidade == 'B')
        qtdUnidade++;
    }
  }
  rewind(fptr);
  fclose(fptr);
  return qtdUnidade;
}

int contarCompradoresHomens() {
  FILE *fptr = fopen("loja.txt", "r");
  if (fptr == NULL)
    return -1;

  int qtdHomens = 0;
  char linha[200];
  while (fgets(linha, sizeof(linha), fptr)) {
    char sexo;
    if (sscanf(linha, "Sexo do cliente: %c", &sexo) == 1) {
      if (sexo == 'M')
        qtdHomens++;
    }
  }
  rewind(fptr);
  fclose(fptr);
  return qtdHomens;
}

void calcularTotalPorSexo(float *totalN, float *totalM) {
  FILE *fptr = fopen("loja.txt", "r");
  if (fptr == NULL)
    return;

  char linha[200];
  int sexoN = 0, sexoM = 0;
  float valorVenda;

  while (fgets(linha, sizeof(linha), fptr)) {
    if (strstr(linha, "Sexo do cliente: N"))
      sexoN = 1;
    else if (strstr(linha, "Sexo do cliente: M"))
      sexoM = 1;

    if ((sexoN || sexoM) && strstr(linha, "Valor total da venda:")) {
      sscanf(linha, "Valor total da venda: %f", &valorVenda);
      if (sexoN) {
        *totalN += valorVenda;
        sexoN = 0;
      } else if (sexoM) {
        *totalM += valorVenda;
        sexoM = 0;
      }
    }
  }
  rewind(fptr);
  fclose(fptr);
}

int contarTotalItensVendidos() {
  FILE *fptr = fopen("loja.txt", "r");
  if (fptr == NULL)
    return -1;

  int qtdTotal = 0;
  char linha[200];
  while (fgets(linha, sizeof(linha), fptr)) {
    int qtdItens;
    if (sscanf(linha, "Quantidade de itens: %d", &qtdItens) == 1) {
      qtdTotal += qtdItens;
    }
  }
  rewind(fptr);
  fclose(fptr);
  return qtdTotal;
}

void calcularTotalEMediaVendas(float *vendaTotal, float *mediaVendas) {
  FILE *fptr = fopen("loja.txt", "r");
  if (fptr == NULL)
    return;

  char linha[200];
  int qtdV = 0;
  float valorVenda;

  while (fgets(linha, sizeof(linha), fptr)) {
    if (sscanf(linha, "Valor total da venda: %f", &valorVenda) == 1) {
      *vendaTotal += valorVenda;
      qtdV++;
    }
  }
  *mediaVendas = *vendaTotal / qtdV;
  rewind(fptr);
  fclose(fptr);
}

float encontrarCompraMaisBarataMulher() {
  FILE *fptr = fopen("loja.txt", "r");
  if (fptr == NULL)
    return -1;

  char linha[200];
  int sexoF = 0;
  float compraBarata = 0;

  while (fgets(linha, sizeof(linha), fptr)) {
    float compra;
    if (strstr(linha, "Sexo do cliente: F"))
      sexoF = 1;
    if (sexoF && strstr(linha, "Valor total da venda:")) {
      sscanf(linha, "Valor total da venda: %f", &compra);
      if (compraBarata > compra || compraBarata == 0) {
        compraBarata = compra;
      }
      sexoF = 0;
    }
  }
  rewind(fptr);
  fclose(fptr);
  return compraBarata;
}

void exibirVendasClienteMaiorNome() {
  FILE *fptr = fopen("loja.txt", "r");
  if (fptr == NULL)
    return;

  char linha[200], maiorNome[50];
  int tamMaior = 0;

  while (fgets(linha, sizeof(linha), fptr)) {
    linha[strcspn(linha, "\n")] = 0;
    if (strlen(linha) > tamMaior && (!strstr(linha, ":"))) {
      tamMaior = strlen(linha);
      strcpy(maiorNome, linha);
    }
  }
  rewind(fptr);
  printf("\n");
  printf("\nVenda(s) do cliente com maior nome: \n");
  while (fgets(linha, sizeof(linha), fptr)) {
    linha[strcspn(linha, "\n")] = 0;
    if (strcmp(linha, maiorNome) == 0) {
      printf("\nNome do cliente: %s\n", linha);
      for (int i = 0; i < 5; i++) {
        if (fgets(linha, sizeof(linha), fptr)) {
          printf("%s", linha);
        }
      }
      printf("\n");
    }
  }
  rewind(fptr);
  fclose(fptr);
}

void exibirVendasClienteMaisNovo() {
  FILE *fptr = fopen("loja.txt", "r");
  if (fptr == NULL)
    return;

  char linha[200], maisNovo[50], nome[50];
  int menorIdade = 0, imprimir = 0;

  while (fgets(linha, sizeof(linha), fptr)) {
    linha[strcspn(linha, "\n")] = 0;
    if (!strstr(linha, ":"))
      strcpy(nome, linha);
    if (strstr(linha, "Idade do cliente:")) {
      int idade;
      sscanf(linha, "Idade do cliente: %d", &idade);
      if (idade < menorIdade || menorIdade == 0) {
        menorIdade = idade;
        strcpy(maisNovo, nome);
      }
    }
  }
  rewind(fptr);
  printf("\nVenda(s) do cliente mais novo:\n");
  while (fgets(linha, sizeof(linha), fptr)) {
    linha[strcspn(linha, "\n")] = 0;
    if (!strstr(linha, ":") && strcmp(linha, maisNovo) == 0) {
      imprimir = 1;
      printf("\nNome do cliente: %s\n", linha);
    } else if (imprimir == 1 && strstr(linha, ":")) {
      printf("%s\n", linha);
    } else if (!strstr(linha, ":")) {
      imprimir = 0;
    }
  }
  fclose(fptr);
}

void deletaCliente() {
  system("clear");
  FILE *arqOriginal;
  FILE *arqTmp;
  arqOriginal = fopen("loja.txt", "r");
  arqTmp = fopen("tmp.txt", "w");
  if (arqOriginal == NULL || arqTmp == NULL) {
    printf("Não foi possivel abrir o arquivo\n");
    return;
  }

  char busca[100];
  char linha[500];
  int encontrado = 0;
  printf("Cliente a ser deletado: ");
  fgets(busca, sizeof(busca), stdin);
  busca[strcspn(busca, "\n")] = '\0';
  for (int i = 0; busca[i] != '\0'; i++) {
    busca[i] = toupper(busca[i]);
  }

  while (fgets(linha, sizeof(linha), arqOriginal)) {
    linha[strcspn(linha, "\n")] = '\0';
    if (strcmp(busca, linha) == 0) {
      for (int i = 0; i < 6; i++) {
        fgets(linha, sizeof(linha), arqOriginal);
      }
      encontrado = 1;
    } else {
      fprintf(arqTmp, "%s\n", linha);
    }
  }

  fclose(arqOriginal);
  fclose(arqTmp);

  remove("loja.txt");
  rename("tmp.txt", "loja.txt");

  if (encontrado == 0) {
    printf("Cliente não encontrado.\n");
  } else {
    printf("Deletado com sucesso.\n");
  }
  printf("\nPressione Enter para continuar...\n");
  while (getchar() != '\n')
    ;
}
void alterarCliente() {
  system("clear");
  FILE *arqOriginal = fopen("loja.txt", "r");
  FILE *arqTmp = fopen("tmp.txt", "w");
  if (!arqOriginal || !arqTmp) {
    printf("Erro ao abrir os arquivos.\n");
    return;
  }

  char busca[100], linha[500];
  int encontrado = 0, contador = 1;

  printf("Nome do cliente a alterar: ");
  fgets(busca, sizeof(busca), stdin);
  busca[strcspn(busca, "\n")] = '\0';
  for (int i = 0; busca[i]; i++) busca[i] = toupper(busca[i]);

  while (fgets(linha, sizeof(linha), arqOriginal)) {
    linha[strcspn(linha, "\n")] = '\0';

    if (strcmp(busca, linha) == 0) {
      printf("\n--- Cadastro de Venda %d ---\n", contador++);
      encontrado = 1;

      // Nome
      printf("Nome original: %s\n", linha);
      char nomeNovo[100];
      do {
        printf("Novo nome do cliente: ");
        fgets(nomeNovo, sizeof(nomeNovo), stdin);
        nomeNovo[strcspn(nomeNovo, "\n")] = '\0';
        if (strlen(nomeNovo) <= 3) {
          printf("Digite um nome maior que 3 letras\n");
          continue;
        }
        for (int i = 0; nomeNovo[i]; i++) nomeNovo[i] = toupper(nomeNovo[i]);
        break;
      } while (1);
      fprintf(arqTmp, "%s\n", nomeNovo);

      // Sexo
      fgets(linha, sizeof(linha), arqOriginal);
      linha[strcspn(linha, "\n")] = '\0';
      const char *p = strstr(linha, ": ");
      printf("Sexo original: %s\n", p ? p + 2 : "");
      char sexo[10];
      do {
        printf("Novo sexo (M/F/N): ");
        fgets(sexo, sizeof(sexo), stdin);
        sexo[strcspn(sexo, "\n")] = '\0';
        sexo[0] = toupper(sexo[0]);
      } while (strcmp(sexo, "M") != 0 && strcmp(sexo, "F") != 0 && strcmp(sexo, "N") != 0);
      fprintf(arqTmp, "Sexo do cliente: %s\n", sexo);

      // Idade
      fgets(linha, sizeof(linha), arqOriginal);
      linha[strcspn(linha, "\n")] = '\0';
      p = strstr(linha, ": ");
      printf("Idade original: %s\n", p ? p + 2 : "");
      int idade;
      do {
        printf("Nova idade: ");
        if (scanf("%d", &idade) != 1 || !valida(idade)) {
          printf("ERRO: Idade inválida.\n");
          while (getchar() != '\n');
        } else {
          while (getchar() != '\n');
          break;
        }
      } while (1);
      fprintf(arqTmp, "Idade do cliente: %d\n", idade);

      // Itens
      fgets(linha, sizeof(linha), arqOriginal);
      linha[strcspn(linha, "\n")] = '\0';
      p = strstr(linha, ": ");
      printf("Quantidade original: %s\n", p ? p + 2 : "");
      int itens;
      do {
        printf("Nova quantidade de itens: ");
        if (scanf("%d", &itens) != 1 || !valida(itens)) {
          printf("ERRO: Quantidade inválida.\n");
          while (getchar() != '\n');
        } else {
          while (getchar() != '\n');
          break;
        }
      } while (1);
      fprintf(arqTmp, "Quantidade de itens: %d\n", itens);

      // Unidade
      fgets(linha, sizeof(linha), arqOriginal);
      linha[strcspn(linha, "\n")] = '\0';
      p = strstr(linha, ": ");
      printf("Unidade original: %s\n", p ? p + 2 : "");
      char unidade[10];
      do {
        printf("Nova unidade (A/B/C): ");
        fgets(unidade, sizeof(unidade), stdin);
        unidade[strcspn(unidade, "\n")] = '\0';
        unidade[0] = toupper(unidade[0]);
      } while (strcmp(unidade, "A") != 0 && strcmp(unidade, "B") != 0 && strcmp(unidade, "C") != 0);
      fprintf(arqTmp, "Unidade comercial da venda: %s\n", unidade);

      // Valor
      fgets(linha, sizeof(linha), arqOriginal);
      linha[strcspn(linha, "\n")] = '\0';
      p = strstr(linha, ": ");
      printf("Valor original: %s\n", p ? p + 2 : "");
      float valor;
      do {
        printf("Novo valor: ");
        if (scanf("%f", &valor) != 1) {
          printf("ERRO: Valor inválido.\n");
          while (getchar() != '\n');
        } else {
          while (getchar() != '\n');
          break;
        }
      } while (1);
      fprintf(arqTmp, "Valor total da venda: %.2f\n", valor);

    } else {
      fprintf(arqTmp, "%s\n", linha);
    }
  }

  fclose(arqOriginal);
  fclose(arqTmp);
  remove("loja.txt");
  rename("tmp.txt", "loja.txt");

  printf(encontrado ? "Alteração concluída com sucesso.\n" : "Cliente não encontrado.\n");
  printf("\nPressione Enter para continuar...\n");
  while (getchar() != '\n');
}

