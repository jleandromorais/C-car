
#include "ranking.h"
#include "screen.h"
#include "keyboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOP_LIMIT 20

void loadScores(PlayerScore scores[], int *count) {
    FILE *file = fopen("scores.txt", "r");
    if (!file) {
        return;
    }

    *count = 0;
    while (fscanf(file, "%20[^|] | %d\n", scores[*count].name, &scores[*count].score) == 2) {
        (*count)++;
        if (*count >= MAX_PLAYERS) break;
    }

    fclose(file);
}

void sortScores(PlayerScore scores[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (scores[i].score < scores[j].score) {
                PlayerScore temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }
}

void showRanking() {
    PlayerScore scores[MAX_PLAYERS];
    int count;
    int top;
    loadScores(scores, &count);
    screenClear();
    screenSetColor(WHITE, BLACK);

    screenDrawBorders();

    screenGotoxy(SCRSTARTX + 35, SCRSTARTY + 5);
    screenPrintCenter("=== RANKING 🏆 ===");

    if (count == 0) {
        screenGotoxy(SCRSTARTX + 29, SCRSTARTY + 12);
        screenPrintCenter("Nenhuma pontuação disponível.");
    } else {
        sortScores(scores, count);
        top = count < TOP_LIMIT ? count : TOP_LIMIT;

        for (int i = 0; i < top; i++) {
            screenGotoxy(SCRSTARTX + 29, SCRSTARTY + 12 + i);
            char rankingEntry[60];

            if (i == 0) {
                snprintf(rankingEntry, sizeof(rankingEntry), "%d. 🥇 %s- %d pontos", i + 1, scores[i].name, scores[i].score);
            } else if (i == 1) {
                snprintf(rankingEntry, sizeof(rankingEntry), "%d. 🥈 %s- %d pontos", i + 1, scores[i].name, scores[i].score);
            } else if (i == 2) {
                snprintf(rankingEntry, sizeof(rankingEntry), "%d. 🥉 %s- %d pontos", i + 1, scores[i].name, scores[i].score);
            } else {
                snprintf(rankingEntry, sizeof(rankingEntry), "%d. %s- %d pontos", i + 1, scores[i].name, scores[i].score);
            }

            screenPrintCenter(rankingEntry);
        }
    }

    screenGotoxy(SCRSTARTX + 20, SCRSTARTY + 14 + (top > 0 ? top : 1));
    screenPrintCenter("Pressione qualquer tecla para voltar ao menu principal.");
    screenUpdate();

    readch();
}
