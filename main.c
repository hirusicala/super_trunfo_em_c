#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CARTAS 100

typedef struct {
    char estado[50];
    int codigo;
    char nomeCidade[100];
    int populacao;
    double pib;
    double area;
    int pontosTuristicos;
    double densidadePopulacional;
    double pibPerCapita;
} Carta;

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void cadastrarCarta(Carta cartas[], int *totalCartas);
void exibirCartas(Carta cartas[], int totalCartas);
void salvarCartasEmArquivo(Carta cartas[], int totalCartas);
void excluirCarta(Carta cartas[], int *totalCartas);
void importarCartasDeArquivo(Carta cartas[], int *totalCartas);

int main() {
    Carta cartas[MAX_CARTAS];
    int totalCartas = 0;
    int opcao;

    importarCartasDeArquivo(cartas, &totalCartas);

    do {
        limparTela();
        printf("\n=== SUPER TRUNFO: CIDADES ===\n");
        printf("1. Cadastrar carta\n");
        printf("2. Listar cartas\n");
        printf("3. Excluir carta\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpar \n

        switch (opcao) {
            case 1:
                limparTela();
                cadastrarCarta(cartas, &totalCartas);
                break;
            case 2:
                limparTela();
                exibirCartas(cartas, totalCartas);
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 3:
                limparTela();
                excluirCarta(cartas, &totalCartas);
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida.\n");
                printf("Pressione Enter para continuar...");
                getchar();
        }
    } while (opcao != 0);

    return 0;
}

void cadastrarCarta(Carta cartas[], int *totalCartas) {
    if (*totalCartas >= MAX_CARTAS) {
        printf("Limite de cartas atingido.\n");
        return;
    }

    Carta nova;

    printf("Estado: ");
    fgets(nova.estado, sizeof(nova.estado), stdin);
    nova.estado[strcspn(nova.estado, "\n")] = '\0';

    printf("Codigo da Cidade: ");
    scanf("%d", &nova.codigo);
    getchar();

    printf("Nome da cidade: ");
    fgets(nova.nomeCidade, sizeof(nova.nomeCidade), stdin);
    nova.nomeCidade[strcspn(nova.nomeCidade, "\n")] = '\0';

    printf("Populacao: ");
    scanf("%d", &nova.populacao);

    printf("PIB: ");
    scanf("%lf", &nova.pib);

    printf("Area (km²): ");
    scanf("%lf", &nova.area);

    printf("Numero de pontos turisticos: ");
    scanf("%d", &nova.pontosTuristicos);
    getchar();

    nova.densidadePopulacional = nova.populacao / nova.area;
    nova.pibPerCapita = nova.pib / nova.populacao;

    cartas[*totalCartas] = nova;
    (*totalCartas)++;

    salvarCartasEmArquivo(cartas, *totalCartas);

    printf("Carta cadastrada com sucesso!\n");
}

void exibirCartas(Carta cartas[], int totalCartas) {
    if (totalCartas == 0) {
        printf("Nenhuma carta cadastrada.\n");
        return;
    }
    
	int i;
    for (i = 0; i < totalCartas; i++) {
        printf("\n=== Carta %d ===\n", i + 1);
        printf("Estado: %s\n", cartas[i].estado);
        printf("Codigo: %d\n", cartas[i].codigo);
        printf("Cidade: %s\n", cartas[i].nomeCidade);
        printf("Populacao: %d\n", cartas[i].populacao);
        printf("PIB: %.2lf\n", cartas[i].pib);
        printf("Area: %.2lf km²\n", cartas[i].area);
        printf("Pontos Turisticos: %d\n", cartas[i].pontosTuristicos);
        printf("Densidade Populacional: %.2lf hab/km²\n", cartas[i].densidadePopulacional);
        printf("PIB per capita: %.2lf\n", cartas[i].pibPerCapita);
    }
}

void salvarCartasEmArquivo(Carta cartas[], int totalCartas) {
    FILE *arquivo = fopen("cartas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar.\n");
        return;
    }
    
	int i;
    for (i = 0; i < totalCartas; i++) {
        fprintf(arquivo, "%s|%d|%s|%d|%.2lf|%.2lf|%d|%.2lf|%.2lf\n",
            cartas[i].estado,
            cartas[i].codigo,
            cartas[i].nomeCidade,
            cartas[i].populacao,
            cartas[i].pib,
            cartas[i].area,
            cartas[i].pontosTuristicos,
            cartas[i].densidadePopulacional,
            cartas[i].pibPerCapita
        );
    }

    fclose(arquivo);
}

void importarCartasDeArquivo(Carta cartas[], int *totalCartas) {
    FILE *arquivo = fopen("cartas.txt", "r");
    if (arquivo == NULL) {
        return;
    }

    while (fscanf(arquivo, "%49[^|]|%d|%99[^|]|%d|%lf|%lf|%d|%lf|%lf\n",
                  cartas[*totalCartas].estado,
                  &cartas[*totalCartas].codigo,
                  cartas[*totalCartas].nomeCidade,
                  &cartas[*totalCartas].populacao,
                  &cartas[*totalCartas].pib,
                  &cartas[*totalCartas].area,
                  &cartas[*totalCartas].pontosTuristicos,
                  &cartas[*totalCartas].densidadePopulacional,
                  &cartas[*totalCartas].pibPerCapita) == 9) {
        (*totalCartas)++;
    }

    fclose(arquivo);
}

void excluirCarta(Carta cartas[], int *totalCartas) {
    if (*totalCartas == 0) {
        printf("Nenhuma carta cadastrada para excluir.\n");
        return;
    }

    char nomeBusca[100];
    int codigoBusca;

    printf("Digite o nome da cidade da carta que deseja excluir: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    printf("Digite o codigo da cidade: ");
    scanf("%d", &codigoBusca);
    getchar();
    
	int i;
    for (i = 0; i < *totalCartas; i++) {
        if (strcmp(cartas[i].nomeCidade, nomeBusca) == 0 && cartas[i].codigo == codigoBusca) {
            char confirmacao;
            printf("Deseja realmente excluir a carta \"%s\" (codigo %d)? (s/n): ", nomeBusca, codigoBusca);
            scanf(" %c", &confirmacao);
            getchar();

            if (confirmacao == 's' || confirmacao == 'S') {
            	int j;
            	
                for (j = i; j < *totalCartas - 1; j++) {
                    cartas[j] = cartas[j + 1];
                }
                (*totalCartas)--;
                salvarCartasEmArquivo(cartas, *totalCartas);
                printf("Carta excluida com sucesso.\n");
            } else {
                printf("Exclusao cancelada.\n");
            }
            return;
        }
    }

    printf("Carta com nome \"%s\" e codigo %d nao encontrada.\n", nomeBusca, codigoBusca);
}