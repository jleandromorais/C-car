#include "../include/cereja.h"
#include "../include/screen.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

const int posicoes_x[MAX_CEREJAS] = {4, 10, 17, 24, 30, 37};
Cereja cerejas[MAX_CEREJAS];
int multiplicador_score = 1;
float tempo_multiplicador = 0.0f;

void inicializar_cerejas() {
    srand(time(NULL));
    for(int i = 0; i < MAX_CEREJAS; i++) {
        int pos = rand() % MAX_CEREJAS;
        cerejas[i].posicaoX = posicoes_x[pos];
        cerejas[i].ativa = 0;
        cerejas[i].posicaoY = 0;
        cerejas[i].velocidade = (rand() % 60)/100.0f + 0.2f;
    }
}

void spawnar_cerejas() {
    int coluna_livre = -1;
    
    for(int i = 0; i < MAX_CEREJAS; i++) {
        if(!cerejas[i].ativa) {
            coluna_livre = i;
            break;
        }
    }
    
    if(coluna_livre != -1) {
        int pos = rand() % MAX_CEREJAS;
        cerejas[coluna_livre].posicaoX = posicoes_x[pos];
        cerejas[coluna_livre].posicaoY = 0;
        cerejas[coluna_livre].velocidade = 0.08f + (rand() % 40) / 100.0f;
        cerejas[coluna_livre].ativa = 1;
    }
}

void atualizar_cerejas(float delta_time) {
    for(int i = 0; i < MAX_CEREJAS; i++) {
        if(cerejas[i].ativa) {
            cerejas[i].posicaoY += cerejas[i].velocidade * delta_time * 60;
            
            if(cerejas[i].posicaoY > 20) {
                cerejas[i].ativa = 0;
            }
        }
    }
}

void desenhar_cerejas(int x_inicio, int y_inicio) {
    for(int i = 0; i < MAX_CEREJAS; i++) {
        if(cerejas[i].ativa) {
            screenGotoxy(x_inicio + cerejas[i].posicaoX, y_inicio + (int)cerejas[i].posicaoY);
            printf("\xF0\x9F\x8D\x92"); // Emoji de cereja
        }
    }
}

int verificar_colisao(int posicao_jogador, int y_carro_relativo) {
    int x_jogador = posicoes_x[posicao_jogador];
    
    for(int i = 0; i < MAX_CEREJAS; i++) {
        if(cerejas[i].ativa && 
           (int)cerejas[i].posicaoY == y_carro_relativo && 
           cerejas[i].posicaoX == x_jogador) 
        {
            cerejas[i].ativa = 0;
            multiplicador_score += 5;
            tempo_multiplicador = 10.0f;
            
            // Feedback visual
            screenSetColor(GREEN, BLACK);
            printf(" +5x! ");
            screenSetNormal();
            fflush(stdout);
            
            return 1;
        }
    }
    return 0;
}