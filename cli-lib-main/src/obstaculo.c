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

void spawnar_obstaculo(float tempo_decorrido) {
    int index_livre = -1;

    for (int i = 0; i < MAX_OBSTACULOS; i++) {
        if (!obstaculos[i].ativa) {
            index_livre = i;
            break;
        }
    }

    if (index_livre != -1) {
        int coluna = rand() % MAX_OBSTACULOS;

        float velocidade_base = 0.1f + (tempo_decorrido * 0.01f);
        if (velocidade_base > 2.0f) velocidade_base = 2.0f;

        obstaculos[index_livre].posicaoX = posicoes_x_obstaculos[coluna];
        obstaculos[index_livre].posicaoY = 0;
        obstaculos[index_livre].velocidade = velocidade_base;
        obstaculos[index_livre].ativa = 1;
    }

    // --- Após 40 segundos, chance de cair mais troncos
    if (tempo_decorrido > 40.0f) {
        int chance = rand() % 100; // 0 a 99

        // Chance de cair mais 1 tronco: começa em 20% e sobe até 80%
        int limite_chance = 20 + (int)((tempo_decorrido - 40.0f) * 1.5f);
        if (limite_chance > 80) limite_chance = 80;

        if (chance < limite_chance) {
            // Chama recursivamente pra spawnar outro tronco (se houver espaço)
            spawnar_obstaculo(tempo_decorrido);
        }
    }
}

void atualizar_obstaculos(float delta_time) {
    for(int i = 0; i < MAX_OBSTACULOS; i++) {
        if(obstaculos[i].ativa) {
            obstaculos[i].posicaoY += obstaculos[i].velocidade * delta_time * 60;

            // Se cair fora da tela
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
            return 1;  // Colisão detectada
        }
    }
    return 0;
}
