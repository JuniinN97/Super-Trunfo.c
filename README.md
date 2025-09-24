#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura de uma carta
typedef struct {
    char nome[30];
    int ataque;
    int defesa;
    int inteligencia;
} Carta;

int main() {
    // Lista de cartas One Piece
    Carta cartas[5] = {
        {"Luffy",    95, 80, 70},
        {"Zoro",     90, 85, 60},
        {"Sanji",    85, 75, 75},
        {"Nami",     60, 65, 90},
        {"Chopper",  70, 70, 85}
    };

    srand(time(NULL));

    // Vetor para armazenar qual carta cada player recebe
    int cartasDistribuidas[5];
    int usados[5] = {0};

    // Sorteando cartas diferentes para cada player
    for (int i = 0; i < 5; i++) {
        int sorteada;
        do {
            sorteada = rand() % 5;
        } while (usados[sorteada] == 1);

        cartasDistribuidas[i] = sorteada;
        usados[sorteada] = 1;
    }

    // Nome dos players
    char *players[5] = {"Player1", "Player2", "Player3", "Player4", "Player5"};

    // Cada player escolhe um atributo
    int escolha[5];
    int valores[5];

    for (int i = 0; i < 5; i++) {
        int idx = cartasDistribuidas[i];
        printf("\n=== %s ===\n", players[i]);
        printf("Sua carta: %s\n", cartas[idx].nome);
        printf("1 - Ataque: %d\n", cartas[idx].ataque);
        printf("2 - Defesa: %d\n", cartas[idx].defesa);
        printf("3 - Inteligencia: %d\n", cartas[idx].inteligencia);

        printf("Escolha um atributo (1-3): ");
        scanf("%d", &escolha[i]);

        switch(escolha[i]) {
            case 1: valores[i] = cartas[idx].ataque; break;
            case 2: valores[i] = cartas[idx].defesa; break;
            case 3: valores[i] = cartas[idx].inteligencia; break;
            default:
                printf("Escolha inválida, será considerado 0!\n");
                valores[i] = 0;
        }
    }

    // Verificar quem venceu
    int maior = valores[0];
    int vencedor = 0;
    int empate = 0;

    for (int i = 1; i < 5; i++) {
        if (valores[i] > maior) {
            maior = valores[i];
            vencedor = i;
            empate = 0;
        } else if (valores[i] == maior) {
            empate = 1; // pelo menos dois players empataram
        }
    }

    printf("\n=== RESULTADO ===\n");
    for (int i = 0; i < 5; i++) {
        printf("%s jogou com %s (%d)\n", players[i], cartas[cartasDistribuidas[i]].nome, valores[i]);
    }

    if (empate) {
        printf("\nHouve um EMPATE!\n");
    } else {
        printf("\nO vencedor foi %s com a carta %s (%d)!\n",
               players[vencedor],
               cartas[cartasDistribuidas[vencedor]].nome,
               maior);
    }

    return 0;
}
