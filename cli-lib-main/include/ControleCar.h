#ifndef CONTROLE_CAR_H
#define CONTROLE_CAR_H

#include "../include/tela.h"
#include "../include/timer.h"

typedef struct {
    int posicao;
    float tempo_decorrido;
    Jogador jogador;
    Jogador score;
} EstadoJogo;


EstadoJogo inicializar_jogo();
void executar_jogo_principal(EstadoJogo *estado);
void finalizar_jogo(EstadoJogo *estado);

#endif