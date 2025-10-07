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

// --- Funções auxiliares ---
void removerQuebraLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

// --- Cadastro e exibição de territórios ---
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

void exibirTerritorios(Territorio *mapa, int qtd) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", (mapa + i)->nome);
        printf("Cor do exercito: %s\n", (mapa + i)->cor);
        printf("Quantidade de tropas: %d\n", (mapa + i)->tropas);
    }
    printf("-----------------------------\n");
}

// --- Sistema de missões ---
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

void exibirMissao(char *missao, int jogador) {
    printf("\nMissao do Jogador %d: %s\n", jogador, missao);
}

// Verificação simples de missão
int verificarMissao(char *missao, Territorio *mapa, int qtd, char *corJogador) {
    int contador = 0;

    // Exemplo 1: "Conquistar 3 territorios"
    if (strstr(missao, "Conquistar 3 territorios")) {
        for (int i = 0; i < qtd; i++)
            if (strcmp(mapa[i].cor, corJogador) == 0)
                contador++;
        if (contador >= 3)
            return 1;
    }

    // Exemplo 2: "Eliminar cor vermelha"
    if (strstr(missao, "Eliminar cor vermelha")) {
        int existeVermelho = 0;
        for (int i = 0; i < qtd; i++)
            if (strcmp(mapa[i].cor, "vermelha") == 0)
                existeVermelho = 1;
        if (!existeVermelho)
            return 1;
    }

    // Exemplo 3: "Conquistar 2 territorios seguidos"
    if (strstr(missao, "Conquistar 2 territorios seguidos")) {
        for (int i = 0; i < qtd - 1; i++)
            if (strcmp(mapa[i].cor, corJogador) == 0 &&
                strcmp(mapa[i + 1].cor, corJogador) == 0)
                return 1;
    }

    // Exemplo 4: "Ter pelo menos 15 tropas"
    if (strstr(missao, "Ter pelo menos 15 tropas")) {
        int total = 0;
        for (int i = 0; i < qtd; i++)
            if (strcmp(mapa[i].cor, corJogador) == 0)
                total += mapa[i].tropas;
        if (total >= 15)
            return 1;
    }

    // Exemplo 5: "Dominar todos os territorios"
    if (strstr(missao, "Dominar todos os territorios")) {
        for (int i = 0; i < qtd; i++)
            if (strcmp(mapa[i].cor, corJogador) != 0)
                return 0;
        return 1;
    }

    return 0; // missão não cumprida
}

// --- Função de ataque ---
void atacar(Territorio *atacante, Territorio *defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n[ERRO] Nao e possivel atacar um territorio da mesma cor!\n");
        return;
    }

    if (atacante->tropas <= 1) {
        printf("\n[ERRO] O atacante precisa de pelo menos 2 tropas para atacar!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n>>> Ataque de %s (%s) contra %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: Atacante venceu a batalha!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= defensor->tropas;
    } else {
        printf("Resultado: Defensor resistiu! O atacante perde 1 tropa.\n");
        atacante->tropas -= 1;
    }
}

// --- Liberação de memória ---
void liberarMemoria(Territorio *mapa, char *missaoJogador1, char *missaoJogador2) {
    free(mapa);
    free(missaoJogador1);
    free(missaoJogador2);
}

// --- Função principal ---
int main() {
    srand(time(NULL));

    int qtd;
    printf("Digite a quantidade de territorios: ");
    scanf("%d", &qtd);
    getchar();

    // Alocação dinâmica dos territórios
    Territorio *mapa = (Territorio *)calloc(qtd, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Cadastro dos territórios
    cadastrarTerritorios(mapa, qtd);
    exibirTerritorios(mapa, qtd);

    // --- Missões pré-definidas ---
    char *missoes[] = {
        "Conquistar 3 territorios",
        "Eliminar cor vermelha",
        "Conquistar 2 territorios seguidos",
        "Ter pelo menos 15 tropas",
        "Dominar todos os territorios"
    };
    int totalMissoes = 5;

    // --- Atribuição dinâmica das missões ---
    char *missaoJogador1 = (char *)malloc(100 * sizeof(char));
    char *missaoJogador2 = (char *)malloc(100 * sizeof(char));

    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    printf("\n--- Missoes Sorteadas ---\n");
    exibirMissao(missaoJogador1, 1);
    exibirMissao(missaoJogador2, 2);

    // --- Loop de jogo ---
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

            // --- Verificação de missões ---
            if (verificarMissao(missaoJogador1, mapa, qtd, mapa[idxAtacante - 1].cor)) {
                printf("\n🎯 O Jogador 1 cumpriu sua missao: %s\n", missaoJogador1);
                break;
            }
            if (verificarMissao(missaoJogador2, mapa, qtd, mapa[idxAtacante - 1].cor)) {
                printf("\n🎯 O Jogador 2 cumpriu sua missao: %s\n", missaoJogador2);
                break;
            }
        }
    } while (opcao != 0);

    liberarMemoria(mapa, missaoJogador1, missaoJogador2);
    printf("\nMemoria liberada. Fim do jogo.\n");
    return 0;
}