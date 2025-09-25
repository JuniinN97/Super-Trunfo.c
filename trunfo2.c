#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_CARTAS 10

typedef struct {
    char nome[30];
    int ataque;
    int defesa;
    int inteligencia;
} Carta;

void mostrarCarta(Carta c) {
    printf("\n=== %s ===\n", c.nome);
    printf("1 - Ataque: %d\n", c.ataque);
    printf("2 - Defesa: %d\n", c.defesa);
    printf("3 - Inteligência: %d\n", c.inteligencia);
}

int comparar(Carta c1, Carta c2, int atributo) {
    int v1, v2;
    if (atributo == 1) { v1 = c1.ataque; v2 = c2.ataque; }
    else if (atributo == 2) { v1 = c1.defesa; v2 = c2.defesa; }
    else { v1 = c1.inteligencia; v2 = c2.inteligencia; }

    if (v1 > v2) return 1;
    if (v2 > v1) return 2;
    return 0; // empate
}

// IA: escolhe o atributo mais forte da carta
int escolhaComputador(Carta c) {
    if (c.ataque >= c.defesa && c.ataque >= c.inteligencia) return 1;
    if (c.defesa >= c.ataque && c.defesa >= c.inteligencia) return 2;
    return 3;
}

int main() {
    srand(time(NULL));

    // 10 cartas de Dragon Ball Z
    Carta cartas[TOTAL_CARTAS] = {
        {"Goku SSJ", 95, 85, 80},
        {"Vegeta SSJ", 92, 83, 82},
        {"Gohan", 88, 80, 90},
        {"Frieza", 85, 70, 85},
        {"Cell Perfeito", 90, 86, 84},
        {"Majin Buu", 89, 87, 78},
        {"Piccolo", 82, 88, 86},
        {"Trunks", 87, 75, 83},
        {"Android 17", 84, 82, 79},
        {"Android 18", 83, 81, 80}
    };

    // embaralhar
    for (int i = 0; i < TOTAL_CARTAS; i++) {
        int j = rand() % TOTAL_CARTAS;
        Carta tmp = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = tmp;
    }

    // dividir entre jogador e computador
    int qtd1 = TOTAL_CARTAS / 2;
    int qtd2 = TOTAL_CARTAS / 2;
    Carta jogador1[30], computador[30];

    for (int i = 0; i < qtd1; i++) jogador1[i] = cartas[i];
    for (int i = 0; i < qtd2; i++) computador[i] = cartas[qtd1 + i];

    int vez = 1; // começa humano
    int rodada = 1;

    printf("===== SUPER TRUNFO DRAGON BALL Z =====\n");

    while (qtd1 > 0 && qtd2 > 0) {
        printf("\n--- Rodada %d ---\n", rodada++);

        Carta c1 = jogador1[0];
        Carta c2 = computador[0];

        int escolha;
        if (vez == 1) {
            printf("\nSua vez!\n");
            mostrarCarta(c1);
            printf("Escolha atributo: ");
            scanf("%d", &escolha);
        } else {
            escolha = escolhaComputador(c2);
            printf("\nComputador escolheu o atributo %d da carta %s\n", escolha, c2.nome);
        }

        printf("\nVocê jogou: %s\n", c1.nome);
        printf("Computador jogou: %s\n", c2.nome);

        int vencedor = comparar(c1, c2, escolha);

        if (vencedor == 1) {
            printf("Você venceu a rodada!\n");
            // jogador1 leva cartas
            for (int i = 1; i < qtd1; i++) jogador1[i-1] = jogador1[i];
            jogador1[qtd1-1] = c1;
            jogador1[qtd1] = c2;
            qtd1++;
            for (int i = 1; i < qtd2; i++) computador[i-1] = computador[i];
            qtd2--;
            vez = 1;
        } else if (vencedor == 2) {
            printf("Computador venceu a rodada!\n");
            for (int i = 1; i < qtd2; i++) computador[i-1] = computador[i];
            computador[qtd2-1] = c2;
            computador[qtd2] = c1;
            qtd2++;
            for (int i = 1; i < qtd1; i++) jogador1[i-1] = jogador1[i];
            qtd1--;
            vez = 2;
        } else {
            printf("Empate! Cada um mantém sua carta.\n");
            for (int i = 1; i < qtd1; i++) jogador1[i-1] = jogador1[i];
            jogador1[qtd1-1] = c1;
            for (int i = 1; i < qtd2; i++) computador[i-1] = computador[i];
            computador[qtd2-1] = c2;
        }

        printf("Cartas restantes: Você = %d | Computador = %d\n", qtd1, qtd2);
    }

    if (qtd1 == 0) printf("\n=== Computador venceu o jogo! ===\n");
    else printf("\n=== Você venceu o jogo! ===\n");

    return 0;
}

