#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura que representa um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para remover o '\n' de strings lidas com fgets
void removerQuebraLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio *mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\nCadastro do Territorio %d:\n", i + 1);

        printf("Digite o nome do territorio: ");
        fgets((mapa + i)->nome, sizeof((mapa + i)->nome), stdin);
        removerQuebraLinha((mapa + i)->nome);

        printf("Digite a cor do exercito: ");
        fgets((mapa + i)->cor, sizeof((mapa + i)->cor), stdin);
        removerQuebraLinha((mapa + i)->cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &((mapa + i)->tropas));
        getchar(); // limpar buffer
    }
}

// Função para exibir os territórios
void exibirTerritorios(Territorio *mapa, int qtd) {
    printf("\n=== Territorios Cadastrados ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", (mapa + i)->nome);
        printf("Cor do exercito: %s\n", (mapa + i)->cor);
        printf("Quantidade de tropas: %d\n", (mapa + i)->tropas);
    }
    printf("-----------------------------\n");
}

// Função que simula o ataque entre dois territórios
void atacar(Territorio *atacante, Territorio *defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n[ERRO] Nao e possivel atacar um territorio da mesma cor!\n");
        return;
    }

    if (atacante->tropas <= 1) {
        printf("\n[ERRO] O atacante precisa de pelo menos 2 tropas para atacar!\n");
        return;
    }

    // Rolagem de dados (1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n>>> Ataque de %s (%s) contra %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: Atacante venceu a batalha!\n");

        // Defensor muda de dono e perde metade das tropas
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2; // metade das tropas do atacante
        atacante->tropas = atacante->tropas - defensor->tropas; // balanceia tropas

    } else {
        printf("Resultado: Defensor resistiu! O atacante perde 1 tropa.\n");
        atacante->tropas -= 1;
    }
}

// Função para liberar memória
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL)); // inicializa gerador de números aleatórios

    int qtd;
    printf("Digite a quantidade de territorios: ");
    scanf("%d", &qtd);
    getchar(); // limpar buffer

    // Alocação dinâmica de memória para os territórios
    Territorio *mapa = (Territorio *) calloc(qtd, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Cadastro inicial
    cadastrarTerritorios(mapa, qtd);
    exibirTerritorios(mapa, qtd);

    // Loop de ataques
    int opcao;
    do {
        printf("\nDeseja realizar um ataque? (1-Sim / 0-Nao): ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            int idxAtacante, idxDefensor;
            exibirTerritorios(mapa, qtd);

            printf("Escolha o numero do territorio atacante: ");
            scanf("%d", &idxAtacante);
            printf("Escolha o numero do territorio defensor: ");
            scanf("%d", &idxDefensor);
            getchar();

            if (idxAtacante < 1 || idxAtacante > qtd || idxDefensor < 1 || idxDefensor > qtd) {
                printf("\n[ERRO] Escolha invalida!\n");
                continue;
            }

            atacar(&mapa[idxAtacante - 1], &mapa[idxDefensor - 1]);
            exibirTerritorios(mapa, qtd);
        }
    } while (opcao != 0);

    liberarMemoria(mapa);
    printf("\nMemoria liberada. Fim do programa.\n");
    return 0;
}
