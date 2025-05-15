#ifndef RANKING_H
#define RANKING_H

typedef struct {
    char nome[20];
    long long score;  // Alterado para long long
} RankingEntry;

#define MAX_RANKING 10
#define ARQUIVO_RANKING "ranking.dat"

// Atualize a assinatura para usar long long
void salvar_score(const char *nome, long long score);
void carregar_ranking(RankingEntry ranking[]);
void exibir_ranking();
void resetar_ranking();
void sanitarizar_ranking();

#endif