#include "../include/controleCar.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "../include/cenario.h"
#include "../include/cereja.h"
#include "../include/obstaculo.h"  // Inclua o cabeçalho dos obstáculos
#include "../include/screen.h"  // Certifique-se que esta linha existe
#include <string.h>

// Variáveis globais para controle do tempo
static float ultimo_spawn_cereja = 0.0f;
static float ultimo_spawn_obstaculo = 0.0f;
static int jogo_ativo = 1;  // Controle do estado do jogo

EstadoJogo inicializar_jogo() {
    EstadoJogo estado;
    estado.posicao = 3;  // Posição inicial centralizada (0-5)
    estado.tempo_decorrido = 0;
    estado.jogador.score = 0;
    
    Jogador jogador;
    mostrar_menu_inicio(&jogador);
    printf("Bem-vindo, %s!\n", jogador.nome);
    strcpy(estado.jogador.nome, jogador.nome);  
    printf("Controles: A (esquerda), D (direita), ESC (sair)\n");
    sleep(1);
    
    timerInit(0);  // Inicializa o timer
    ultimo_spawn_cereja = 0.0f;
    ultimo_spawn_obstaculo = 0.0f;
    jogo_ativo = 1;
    
    inicializar_cerejas();  // Inicializa o sistema de cerejas
    inicializar_obstaculos(); // Inicializa o sistema de obstáculos
    
    return estado;
}

void executar_jogo_principal(EstadoJogo *estado) {
    char tecla;
    float last_time = getTimeDiff()/1000.0f;
    
    while(jogo_ativo) {
        float current_time = getTimeDiff()/1000.0f;
        float delta_time = current_time - last_time;
        last_time = current_time;
        
        estado->tempo_decorrido = current_time;
        
        // Sistema de spawn de cerejas a cada 10 segundos
        if(current_time - ultimo_spawn_cereja >= 10.0f) {
            spawnar_cerejas();
            ultimo_spawn_cereja = current_time;
        }
        
        // Sistema de spawn de obstáculos a cada 5-8 segundos (aleatório)
        if(current_time - ultimo_spawn_obstaculo >= (5 + rand() % 4)) {
            spawnar_obstaculo(current_time);
            ultimo_spawn_obstaculo = current_time;
        }
        
        // Atualiza sistemas
        atualizar_cerejas(delta_time);
        atualizar_obstaculos(delta_time);
        
        // Verifica colisões
        if(verificar_colisao(estado->posicao, 7)) { // Colisão com cereja
            // Efeito de coleta já está implementado na função verificar_colisao
        }
        
        if(verificar_colisao_obstaculo(estado->posicao, 7)) { // Colisão com obstáculo
            jogo_ativo = 0; // Termina o jogo
            break;
        }
        
        // Atualiza pontuação
        estado->jogador.score = (int)(estado->tempo_decorrido * 
                                    (estado->tempo_decorrido < 15 ? 5 : 10)) *
                                    multiplicador_score;
        
        // Desenha o cenário (que já inclui cerejas e obstáculos)
        desenhar_cenario(estado->posicao, estado->tempo_decorrido, estado->jogador.score);
        
        if(read(STDIN_FILENO, &tecla, 1) == 1) {
            if((tecla == 'a' || tecla == 'A') && estado->posicao > 0) estado->posicao--;
            if((tecla == 'd' || tecla == 'D') && estado->posicao < 5) estado->posicao++;
            if(tecla == 27) break;  // ESC para sair
        }
        
        usleep(50000); // 50ms (20 FPS)
    }
    
    // Se o jogo terminou por colisão com obstáculo
    if(!jogo_ativo) {
        screenClear();
        printf("\n\n  GAME OVER!\n");
        printf("  Voce bateu em um tronco! 🪵\n");
        printf("  Pontuacao final: %d\n", estado->jogador.score);
        sleep(3);
    }
}

void finalizar_jogo(EstadoJogo *estado) {
    printf("\n");
    printf("\nTempo total de jogo: %.2f segundos\n", estado->tempo_decorrido);
    printf(" Sua pontuacao foi de: %03d\n", estado->jogador.score);
    printf("Obrigado por jogar, %s!\n", estado->jogador.nome);
    timerDestroy();
}