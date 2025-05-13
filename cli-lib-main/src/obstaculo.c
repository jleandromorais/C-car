#include "../include/obstaculo.h"
#include "../include/screen.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Posições X pré-definidas (relativas ao início da pista)
const int posicoes_x_obstaculos[MAX_OBSTACULOS] = {4, 10, 17, 24, 30, 37};

Obstaculo obstaculos[MAX_OBSTACULOS];
float tempo_ultimo_obstaculo = 0.0f;

void inicializar_obstaculos() {
    srand(time(NULL));
    for(int i = 0; i < MAX_OBSTACULOS; i++) {
        int pos = rand() % MAX_OBSTACULOS;
        obstaculos[i].posicaoX = posicoes_x_obstaculos[pos];
        obstaculos[i].ativa = 0;
        obstaculos[i].posicaoY = 0;
        obstaculos[i].velocidade = (rand() % 80)/100.0f + 0.3f; // Mais rápido que cerejas
    }
}

void spawnar_obstaculo(void) {
    int coluna_livre = -1;
    
    // Encontra uma coluna disponível
    for(int i = 0; i < MAX_OBSTACULOS; i++) {
        if(!obstaculos[i].ativa) {
            coluna_livre = i;
            break;
        }
    }
    
    if(coluna_livre != -1) {
        obstaculos[coluna_livre].posicaoY = 0;
        obstaculos[coluna_livre].velocidade = 0.2f + (rand() % 60)/100.0f;
        obstaculos[coluna_livre].ativa = 1;
    }
}

void atualizar_obstaculos(float delta_time) {
    for(int i = 0; i < MAX_OBSTACULOS; i++) {
        if(obstaculos[i].ativa) {
            obstaculos[i].posicaoY += obstaculos[i].velocidade * delta_time * 60;
            
            // Se cair abaixo da pista, desativa
            if(obstaculos[i].posicaoY > 20) {
                obstaculos[i].ativa = 0;
            }
        }
    }
}

void desenhar_obstaculos(int x_inicio, int y_inicio) {
    for(int i = 0; i < MAX_OBSTACULOS; i++) {
        if(obstaculos[i].ativa) {
            screenGotoxy(x_inicio + obstaculos[i].posicaoX, y_inicio + (int)obstaculos[i].posicaoY);
            printf("\xF0\x9F\xAA\xB5"); // Emoji de tronco (🪵)
        }
    }
}

int verificar_colisao_obstaculo(int posicao_jogador, int y_carro_relativo) {
    int x_jogador = posicoes_x_obstaculos[posicao_jogador];
    
    for(int i = 0; i < MAX_OBSTACULOS; i++) {
        if(obstaculos[i].ativa && 
           (int)obstaculos[i].posicaoY == y_carro_relativo && 
           obstaculos[i].posicaoX == x_jogador) 
        {
            return 1;  // Retorna verdadeiro para colisão (fim de jogo)
        }
    }
    return 0;
}