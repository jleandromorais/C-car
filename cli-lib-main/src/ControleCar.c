#include "../include/controleCar.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "../include/cenario.h"
#include "../include/cereja.h"
#include "../include/obstaculo.h"
#include "../include/screen.h"
#include "../include/ranking.h"
#include <string.h>

// Variáveis globais para controle do tempo
static float ultimo_spawn_cereja = 0.0f;
static float ultimo_spawn_obstaculo = 0.0f;
static int jogo_ativo = 1;

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
    
    timerInit(0);
    ultimo_spawn_cereja = 0.0f;
    ultimo_spawn_obstaculo = 0.0f;
    jogo_ativo = 1;
    
    inicializar_cerejas();
    inicializar_obstaculos();
    
    return estado;
}

void executar_jogo_principal(EstadoJogo *estado) {
    char tecla;
    float last_time = getTimeDiff()/1000.0f;
    float tempo_base_pontuacao = 0.0f;
    
    while(jogo_ativo) {
        float current_time = getTimeDiff()/1000.0f;
        float delta_time = current_time - last_time;
        last_time = current_time;
        
        estado->tempo_decorrido = current_time;
        tempo_base_pontuacao += delta_time;
        
        // Atualiza multiplicador
        if(multiplicador_score > 1) {
            tempo_multiplicador -= delta_time;
            if(tempo_multiplicador <= 0) {
                multiplicador_score = 1;
                tempo_multiplicador = 0.0f;
            }
        }
        
        // Sistema de spawn de cerejas
        if(current_time - ultimo_spawn_cereja >= 10.0f) {
            spawnar_cerejas();
            ultimo_spawn_cereja = current_time;
        }
        
        // Sistema de spawn de obstáculos
        if(current_time - ultimo_spawn_obstaculo >= (5 + rand() % 4)) {
            spawnar_obstaculo(current_time);
            ultimo_spawn_obstaculo = current_time;
        }
        
        // Atualiza sistemas
        atualizar_cerejas(delta_time);
        atualizar_obstaculos(delta_time);
        
        // Verifica colisões
        if(verificar_colisao(estado->posicao, 7)) {
            // Feedback já é mostrado na função verificar_colisao
        }
        
        if(verificar_colisao_obstaculo(estado->posicao, 7)) {
            jogo_ativo = 0;
            break;
        }
        
        // Calcula pontuação
        estado->jogador.score = (int)(tempo_base_pontuacao * 5) * multiplicador_score;
        
        // Desenha o cenário
        desenhar_cenario(estado->posicao, estado->tempo_decorrido, estado->jogador.score);
        
        // Mostra multiplicador atual
        screenSetColor(YELLOW, BLACK);
        screenGotoxy(1, 1);
        printf("Multi: %dx | ", multiplicador_score);
        screenSetNormal();
        
        // Tempo restante do multiplicador
        if(multiplicador_score > 1) {
            screenSetColor(GREEN, BLACK);
            printf("Tempo: %.1fs", tempo_multiplicador);
            screenSetNormal();
        }
        
        // Controles
        if(read(STDIN_FILENO, &tecla, 1) == 1) {
            if((tecla == 'a' || tecla == 'A') && estado->posicao > 0) estado->posicao--;
            if((tecla == 'd' || tecla == 'D') && estado->posicao < 5) estado->posicao++;
            if(tecla == 27) break;  // ESC para sair
        }
        
        usleep(50000); // 50ms (20 FPS)
    }
    
    // Tela de Game Over
    if(!jogo_ativo) {
        screenClear();
        printf("\n\n  GAME OVER!\n");
        printf("  Voce bateu em um tronco! 🪵\n");
        printf("  Pontuacao final: %d\n", estado->jogador.score);
        sleep(3);
    }
}

void finalizar_jogo(EstadoJogo *estado) {
    // Salva a pontuação
    salvar_score(estado->jogador.nome, estado->jogador.score);

    // Limpa a tela e mostra informações finais
    system("clear");
    printf("\n\n  ===== FIM DE JOGO =====\n");
    printf("\n  Jogador: %s\n", estado->jogador.nome);
    printf("  Tempo total: %.2f segundos\n", estado->tempo_decorrido);
    printf("  Pontuação final: %d pontos\n\n", estado->jogador.score);
    
    // Mostra ranking
    RankingEntry ranking[MAX_RANKING];
    carregar_ranking(ranking);
    
    int posicao_jogador = -1;
    for(int i = 0; i < MAX_RANKING; i++) {
        if(strcmp(ranking[i].nome, estado->jogador.nome) == 0 && 
           ranking[i].score == estado->jogador.score) {
            posicao_jogador = i + 1;
            break;
        }
    }
    
    if(posicao_jogador != -1) {
        printf("  🏆 Posição no ranking: #%d 🏆\n\n", posicao_jogador);
    }
    
    // Mostra top 5
    screenSetColor(CYAN, BLACK);
    printf("  === TOP 5 ===\n");
    screenSetNormal();
    
    for(int i = 0; i < 5; i++) {
        if(ranking[i].score > 0) {
            if(i == posicao_jogador-1) {
                screenSetColor(YELLOW, BLACK);
                printf("  > %2d. %-20s %5d pts <\n", i+1, ranking[i].nome, ranking[i].score);
                screenSetNormal();
            } else {
                printf("    %2d. %-20s %5d pts\n", i+1, ranking[i].nome, ranking[i].score);
            }
        }
    }
    
    printf("\n");
    screenSetColor(BLUE, BLACK);
    printf("Pressione Enter para sair...");
    screenSetNormal();
    fflush(stdout);
    
    // Limpa buffer e espera Enter
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    while(getchar() != '\n');
    
    timerDestroy();
}