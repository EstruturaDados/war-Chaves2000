#include <stdio.h>
#include <string.h>

// Definição da estrutura Territorio
// Cada território terá um nome, uma cor do exército e a quantidade de tropas
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Vetor de structs para armazenar até 5 territórios
    struct Territorio territorios[5];
    int i;

    printf("=== Cadastro de Territorios do Jogo WAR ===\n\n");

    // Laço para cadastro dos 5 territórios
    for (i = 0; i < 5; i++) {
        printf("Cadastro do territorio %d:\n", i + 1);

        printf("Digite o nome do territorio: ");
        scanf(" %29[^\n]", territorios[i].nome); // lê até 29 caracteres (evita estouro)

        printf("Digite a cor do exercito: ");
        scanf(" %9s", territorios[i].cor); // lê até 9 caracteres (sem espaços)

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    // Exibição dos dados cadastrados
    printf("\n=== Territorios Cadastrados ===\n\n");
    for (i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }

    return 0;
}