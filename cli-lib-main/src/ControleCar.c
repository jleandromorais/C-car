#include "../include/controleCar.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "../include/cenario.h"
#include "../include/cereja.h"

// Variável global para controle do tempo do spawn
static float ultimo_spawn = 0.0f;

EstadoJogo inicializar_jogo() {
    EstadoJogo estado;
    estado.posicao = 3;  // Posição inicial centralizada (0-5)
    estado.tempo_decorrido = 0;
    estado.jogador.score = 0;
    
    Jogador jogador;
    mostrar_menu_inicio(&jogador);
    printf("Bem-vindo, %s!\n", jogador.nome);
    printf("Controles: A (esquerda), D (direita), ESC (sair)\n");
    sleep(1);
    
    timerInit(0);  // Inicializa o timer
    ultimo_spawn = 0.0f;  // Reseta o temporizador de spawn
    inicializar_cerejas();  // Inicializa o sistema de cerejas
    
    return estado;
}

void executar_jogo_principal(EstadoJogo *estado) {
    char tecla;
    float last_time = getTimeDiff()/1000.0f;
    
    while(1) {
        float current_time = getTimeDiff()/1000.0f;
        float delta_time = current_time - last_time;
        last_time = current_time;
        
        estado->tempo_decorrido = current_time;
        
        // Sistema de spawn a cada 10 segundos
        if(current_time - ultimo_spawn >= 10.0f) {
            spawnar_cerejas();  // Chama sem parâmetros
            ultimo_spawn = current_time;
        }
        
        // Atualiza sistema de cerejas
        atualizar_cerejas(delta_time);
        
        // Verifica colisões
        if(verificar_colisao(estado->posicao, 7)) { // 7 é a linha Y do carro
            // Efeito de coleta já está implementado na função verificar_colisao
        }
        
        // Atualiza pontuação
        estado->jogador.score = (int)(estado->tempo_decorrido * 
                                    (estado->tempo_decorrido < 15 ? 5 : 10)) *
                                    multiplicador_score;
        
        desenhar_cenario(estado->posicao, estado->tempo_decorrido, estado->jogador.score);
        
        if(read(STDIN_FILENO, &tecla, 1) == 1) {
            if((tecla == 'a' || tecla == 'A') && estado->posicao > 0) estado->posicao--;
            if((tecla == 'd' || tecla == 'D') && estado->posicao < 5) estado->posicao++;
            if(tecla == 27) break;  // ESC para sair
        }
        
        usleep(50000); // 50ms (20 FPS)
    }
}

void finalizar_jogo(EstadoJogo *estado) {
    printf("\n");
    printf("\nTempo total de jogo: %.2f segundos\n", estado->tempo_decorrido);
    printf(" Sua pontuacao foi de: %03d\n", estado->jogador.score);
    printf("Obrigado por jogar, %s!\n", estado->jogador.nome);
    timerDestroy();
}