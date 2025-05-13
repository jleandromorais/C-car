#include "../include/cereja.h"
#include "../include/screen.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Posições X pré-definidas (relativas ao início da pista)
const int posicoes_x[MAX_CEREJAS] = {4, 10, 17, 24, 30, 37};

float tempo_multiplicador = 0.0f;
Cereja cerejas[MAX_CEREJAS];
int multiplicador_score = 1;

void inicializar_cerejas() {
    srand(time(NULL));
    for(int i = 0; i < MAX_CEREJAS; i++) {
        // Corrigido: Usar MAX_CEREJAS em vez de NUM_FATXAS
        int pos = rand() % MAX_CEREJAS;
        cerejas[i].posicaoX = posicoes_x[pos];
        cerejas[i].ativa = 0;
        cerejas[i].posicaoY = 0;
        cerejas[i].velocidade = (rand() % 60)/100.0f + 0.2f;
    }
}

// Adicione no início do arquivo
float tempo_ultima_cereja = 0.0f;

// Substitua a função spawnar_cerejas por:
void spawnar_cerejas(void) {
    int coluna_livre = -1;
    
    // Encontra uma cereja inativa
    for(int i = 0; i < MAX_CEREJAS; i++) {
        if(!cerejas[i].ativa) {
            coluna_livre = i;
            break;
        }
    }
    
    if(coluna_livre != -1) {
        int pos = rand() % MAX_CEREJAS;  // Sorteia uma posição X válida
        cerejas[coluna_livre].posicaoX = posicoes_x[pos];
        cerejas[coluna_livre].posicaoY = 0;
        cerejas[coluna_livre].velocidade = 0.1f + (rand() % 40) / 100.0f;  // Velocidade entre 0.1 e 0.5
        cerejas[coluna_livre].ativa = 1;
    }
}

void atualizar_cerejas(float delta_time) {
    for(int i = 0; i < MAX_CEREJAS; i++) {
        if(cerejas[i].ativa) {
            cerejas[i].posicaoY += cerejas[i].velocidade * delta_time * 60;
            
            // Se cair abaixo da pista, desativa
            if(cerejas[i].posicaoY > 20) {
                cerejas[i].ativa = 0;
            }
        }
    }
}

void desenhar_cerejas(int x_inicio, int y_inicio) {
    for(int i = 0; i < MAX_CEREJAS; i++) {
        if(cerejas[i].ativa) {
            // Agora soma x_inicio para posicionar corretamente na pista
            screenGotoxy(x_inicio + cerejas[i].posicaoX, y_inicio + (int)cerejas[i].posicaoY);
            printf("\xF0\x9F\x8D\x92");
        }
    }
}

// Atualize verificar_colisao para usar coordenadas relativas
int verificar_colisao(int posicao_jogador, int y_carro_relativo) {
    int x_jogador = posicoes_x[posicao_jogador];
    
    for(int i = 0; i < MAX_CEREJAS; i++) {
        if(cerejas[i].ativa && 
           (int)cerejas[i].posicaoY == y_carro_relativo && 
           cerejas[i].posicaoX == x_jogador) 
        {
            cerejas[i].ativa = 0;
            multiplicador_score = 5;
            tempo_multiplicador = 10.0f;  // 10 segundos de duração
            return 1;  // Retorna verdadeiro para colisão
        }
    }
    return 0;
}