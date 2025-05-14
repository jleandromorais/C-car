#include "ranking.h"
#include "screen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void salvar_score(const char *nome, int score) {
    RankingEntry entry;
    strncpy(entry.nome, nome, 20);
    entry.nome[19] = '\0'; // Garante terminação nula
    entry.score = score;

    FILE *arquivo = fopen(ARQUIVO_RANKING, "ab");
    if(arquivo) {
        fwrite(&entry, sizeof(RankingEntry), 1, arquivo);
        fclose(arquivo);
    }
}

void carregar_ranking(RankingEntry ranking[]) {
    // Inicializa o array
    memset(ranking, 0, MAX_RANKING * sizeof(RankingEntry));
    
    FILE *arquivo = fopen(ARQUIVO_RANKING, "rb");
    if(!arquivo) return;

    RankingEntry temp;
    int count = 0;
    
    // Lê todas as entradas do arquivo
    while(fread(&temp, sizeof(RankingEntry), 1, arquivo) && count < MAX_RANKING * 2) {
        // Adiciona apenas se tiver score válido
        if(temp.score > 0) {
            // Mantém apenas as MAX_RANKING melhores entradas na memória
            if(count < MAX_RANKING) {
                ranking[count++] = temp;
            } else {
                // Encontra o menor score no ranking atual
                int menor_idx = 0;
                for(int i = 1; i < MAX_RANKING; i++) {
                    if(ranking[i].score < ranking[menor_idx].score) {
                        menor_idx = i;
                    }
                }
                // Substitui se o novo score for maior
                if(temp.score > ranking[menor_idx].score) {
                    ranking[menor_idx] = temp;
                }
            }
        }
    }
    fclose(arquivo);

    // Ordena o ranking (bubble sort melhorado)
    for(int i = 0; i < MAX_RANKING-1; i++) {
        for(int j = 0; j < MAX_RANKING-i-1; j++) {
            if(ranking[j].score < ranking[j+1].score) {
                RankingEntry temp = ranking[j];
                ranking[j] = ranking[j+1];
                ranking[j+1] = temp;
            }
        }
    }
}

void exibir_ranking() {
    system("clear");
    mostrar_titulo(); // Reutiliza a função de título do jogo
    
    RankingEntry ranking[MAX_RANKING] = {0};
    carregar_ranking(ranking);

    screenSetColor(CYAN, BLACK);
    printf("\n  === TOP 10 SCORES ===\n\n");
    screenSetNormal();

    for(int i = 0; i < MAX_RANKING; i++) {
        if(ranking[i].score > 0) {
            screenSetColor(YELLOW, BLACK);
            printf("  %2d. ", i+1);
            screenSetColor(WHITE, BLACK);
            printf("%-20s ", ranking[i].nome);
            screenSetColor(GREEN, BLACK);
            printf("%5d pts\n", ranking[i].score);
            screenSetNormal();
        } else {
            printf("  %2d. ---\n", i+1);
        }
    }

    printf("\n");
    screenSetColor(BLUE, BLACK);
    printf("Pressione Enter para voltar...");
    screenSetNormal();
    fflush(stdout);
    
    // Limpa o buffer de entrada antes de esperar
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    while(getchar() != '\n'); // Espera Enter
}