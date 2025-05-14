#ifndef RANKING_H
#define RANKING_H

#define ARQUIVO_RANKING "ranking.dat"
#define MAX_RANKING 10

typedef struct {
    char nome[20];
    int score;
} RankingEntry;

void salvar_score(const char *nome, int score);
void carregar_ranking(RankingEntry ranking[]);
void exibir_ranking();

#endif