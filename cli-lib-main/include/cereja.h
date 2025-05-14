#ifndef CEREJA_H
#define CEREJA_H

#define MAX_CEREJAS 6

extern const int posicoes_x[MAX_CEREJAS];

typedef struct {
    int posicaoX;
    float posicaoY;
    float velocidade;
    int ativa;
} Cereja;

extern int multiplicador_score;
extern float tempo_multiplicador;

void inicializar_cerejas();
void spawnar_cerejas();
void atualizar_cerejas(float delta_time);
void desenhar_cerejas(int x_inicio, int y_inicio);
int verificar_colisao(int posicao_jogador, int y_carro_relativo);

#endif