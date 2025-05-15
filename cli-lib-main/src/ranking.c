#include "ranking.h"
#include "screen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Adicione este protótipo se mostrar_titulo() não estiver declarado
void mostrar_titulo(void);

void salvar_score(const char *nome, long long score) {  // Alterado para long long
    if (score <= 0 || score > 1000000) {
        return;
    }

    RankingEntry entry;
    strncpy(entry.nome, nome, 20);
    entry.nome[19] = '\0';
    entry.score = score;

    FILE *arquivo = fopen(ARQUIVO_RANKING, "ab");
    if (arquivo) {
        fwrite(&entry, sizeof(RankingEntry), 1, arquivo);
        fclose(arquivo);
    }
}

void sanitarizar_ranking() {
    FILE *file = fopen(ARQUIVO_RANKING, "rb+");
    if (file) {
        RankingEntry ranking[MAX_RANKING];
        
        size_t lidos = fread(ranking, sizeof(RankingEntry), MAX_RANKING, file);
        
        for (size_t i = 0; i < lidos; i++) {  // Alterado para size_t
            int nome_valido = 1;
            for (size_t j = 0; j < sizeof(ranking[i].nome); j++) {  // Alterado para size_t
                if (!isprint((unsigned char)ranking[i].nome[j]) && ranking[i].nome[j] != '\0') {
                    nome_valido = 0;
                    break;
                }
            }
            
            if (!nome_valido || ranking[i].score < 0 || ranking[i].score > 1000000) {
                memset(&ranking[i], 0, sizeof(RankingEntry));
            }
        }
        
        rewind(file);
        fwrite(ranking, sizeof(RankingEntry), MAX_RANKING, file);
        fclose(file);
    }
}

void carregar_ranking(RankingEntry ranking[]) {
    memset(ranking, 0, MAX_RANKING * sizeof(RankingEntry));

    FILE *arquivo = fopen(ARQUIVO_RANKING, "rb");
    if (!arquivo) return;

    fseek(arquivo, 0, SEEK_END);
    long file_size = ftell(arquivo);
    rewind(arquivo);

    if (file_size > (long)(MAX_RANKING * sizeof(RankingEntry)) || file_size <= 0) {
        fclose(arquivo);
        return;
    }

    int count = 0;
    RankingEntry temp;
    
    while (fread(&temp, sizeof(RankingEntry), 1, arquivo) == 1 && count < MAX_RANKING) {
        int nome_valido = 1;
        for (size_t i = 0; i < sizeof(temp.nome); i++) {  // Alterado para size_t
            if (!isprint((unsigned char)temp.nome[i]) && temp.nome[i] != '\0') {
                nome_valido = 0;
                break;
            }
        }

        if (nome_valido && 
            temp.score > 0 && 
            temp.score <= 1000000 && 
            strlen(temp.nome) > 0 && 
            strlen(temp.nome) < 50) {
            
            ranking[count++] = temp;
        }
    }
    fclose(arquivo);

    for (int i = 1; i < count; i++) {
        RankingEntry key = ranking[i];
        int j = i - 1;
        
        while (j >= 0 && ranking[j].score < key.score) {
            ranking[j + 1] = ranking[j];
            j--;
        }
        ranking[j + 1] = key;
    }
}

void exibir_ranking() {
    system("clear");
    mostrar_titulo();
    
    RankingEntry ranking[MAX_RANKING] = {0};
    carregar_ranking(ranking);

    screenSetColor(CYAN, BLACK);
    printf("\n  === TOP 10 SCORES ===\n\n");
    screenSetNormal();

    for (int i = 0; i < MAX_RANKING; i++) {
        if (ranking[i].score > 0) {
            screenSetColor(YELLOW, BLACK);
            printf("  %2d. ", i+1);
            screenSetColor(WHITE, BLACK);
            printf("%-20s ", ranking[i].nome);
            screenSetColor(GREEN, BLACK);
            printf("%5lld pts\n", ranking[i].score);  // Alterado para %lld
            screenSetNormal();
        } else {
            screenSetColor(DARKGRAY, BLACK);
            printf("  %2d. ---\n", i+1);
            screenSetNormal();
        }
    }

    printf("\n");
    screenSetColor(BLUE, BLACK);
    printf("Pressione Enter para voltar...");
    screenSetNormal();
    fflush(stdout);
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    while (getchar() != '\n');
}

void resetar_ranking() {
    FILE *arquivo = fopen(ARQUIVO_RANKING, "wb");
    if (arquivo) {
        RankingEntry ranking_zerado[MAX_RANKING] = {0};
        fwrite(ranking_zerado, sizeof(RankingEntry), MAX_RANKING, arquivo);
        fclose(arquivo);
    }
}