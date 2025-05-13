#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <time.h>

#define MAX_OBSTACULOS 6

typedef struct {
    int posicaoX;       // Posição horizontal na pista
    float posicaoY;     // Posição vertical atual
    int ativa;          // 0 = inativa, 1 = caindo
    float velocidade;   // Velocidade de queda
} Obstaculo;

extern Obstaculo obstaculos[MAX_OBSTACULOS];
extern float tempo_ultimo_obstaculo;

void inicializar_obstaculos(void);
void spawnar_obstaculo(void);
void atualizar_obstaculos(float delta_time);
void desenhar_obstaculos(int x_inicio, int y_inicio);
int verificar_colisao_obstaculo(int posicao_jogador, int y_carro);

#endif