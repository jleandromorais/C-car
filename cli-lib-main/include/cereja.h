#ifndef CEREJA_H
#define CEREJA_H

#include <time.h>

#define MAX_CEREJAS 6
#define DURACAO_MULTIPLICADOR 10

// Posições X das faixas (relativas ao início da pista)

typedef struct {
    int posicaoX;       // Posição horizontal na pista
    float posicaoY;     // Posição vertical atual
    int ativa;          // 0 = inativa, 1 = caindo
    time_t coleta_time; // Quando foi coletada
    float velocidade;   // Velocidade de queda (0.3 a 0.8)
} Cereja;

extern const int posicoes_x[MAX_CEREJAS];
extern Cereja cerejas[MAX_CEREJAS];
extern int multiplicador_score;
// Adicione no cabeçalho
extern float tempo_ultima_cereja;

// Protótipos das funções
void inicializar_cerejas(void);
void spawnar_cerejas(void);
void atualizar_cerejas(float delta_time);
void desenhar_cerejas(int x_inicio, int y_inicio);
int verificar_colisao(int posicao_jogador, int y_carro);

#endif