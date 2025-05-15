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

// Variáveis globais
static float ultimo_spawn_cereja = 0.0f;
static float ultimo_spawn_obstaculo = 0.0f;
static int jogo_ativo = 1;

EstadoJogo inicializar_jogo() {
    EstadoJogo estado;
    estado.posicao = 3;  // Posição central
    estado.tempo_decorrido = 0.0f;
    estado.jogador.score = 0;
    
    // Pega nome do jogador
    Jogador jogador;
    mostrar_menu_inicio(&jogador);
    strcpy(estado.jogador.nome, jogador.nome);
    
    printf("Controles: A (esquerda), D (direita), ESC (sair)\n");
    sleep(1);
    
    // Inicia sistemas
    timerInit(0);
    inicializar_cerejas();
    inicializar_obstaculos();
    
    return estado;
}

void executar_jogo_principal(EstadoJogo *estado) {
    char tecla;
    float last_time = getTimeDiff()/1000.0f;
    float pontos_acumulados = 0.0f; // Pontos fracionários
    
    while(jogo_ativo) {
        float current_time = getTimeDiff()/1000.0f;
        float delta_time = current_time - last_time;
        last_time = current_time;
        
        estado->tempo_decorrido = current_time;
        
        // Atualiza multiplicador
        if(multiplicador_score > 1) {
            tempo_multiplicador -= delta_time;
            if(tempo_multiplicador <= 0) {
                multiplicador_score = 1;
                tempo_multiplicador = 0.0f;
            }
        }
        
        // Spawn de itens
        if(current_time - ultimo_spawn_cereja >= 10.0f) {
            spawnar_cerejas();
            ultimo_spawn_cereja = current_time;
        }
        
        if(current_time - ultimo_spawn_obstaculo >= (5 + rand() % 4)) {
            spawnar_obstaculo(current_time);
            ultimo_spawn_obstaculo = current_time;
        }
        
        // Atualiza objetos
        atualizar_cerejas(delta_time);
        atualizar_obstaculos(delta_time);
        
        // Verifica colisões
        if(verificar_colisao(estado->posicao, 15)) {
            // Atualiza multiplicador ao pegar cereja
        }
        
        if(verificar_colisao_obstaculo(estado->posicao, 15)) {
            jogo_ativo = 0;
            break;
        }
        
        // Sistema de pontuação
        const float pontos_por_segundo = 10.0f;
        pontos_acumulados += delta_time * pontos_por_segundo * multiplicador_score;
        
        if(pontos_acumulados >= 1.0f) {
            int pontos_inteiros = (int)pontos_acumulados;
            estado->jogador.score += pontos_inteiros;
            pontos_acumulados -= pontos_inteiros;
        }
        
        // Desenha cena
        desenhar_cenario(estado->posicao, estado->tempo_decorrido, estado->jogador.score);
        
        // Mostra HUD
        screenSetColor(YELLOW, BLACK);
        screenGotoxy(1, 1);
        printf("Score: %lld | Multi: %dx", estado->jogador.score, multiplicador_score);
        
        if(multiplicador_score > 1) {
            screenSetColor(GREEN, BLACK);
            printf(" | Tempo: %.1fs", tempo_multiplicador);
        }
        screenSetNormal();
        
        // Controles
        if(read(STDIN_FILENO, &tecla, 1) == 1) {
            if((tecla == 'a' || tecla == 'A') && estado->posicao > 0) estado->posicao--;
            if((tecla == 'd' || tecla == 'D') && estado->posicao < 5) estado->posicao++;
            if(tecla == 27) break;
        }
        
        usleep(50000); // ~20 FPS
    }
    
    // Game Over
    if(!jogo_ativo) {
        screenClear();
        printf("\n\n  GAME OVER!\n");
        printf("  Pontuação final: %lld\n", estado->jogador.score);
        sleep(3);
    }
}

void finalizar_jogo(EstadoJogo *estado) {
    // 1. Salva a pontuação atual
    salvar_score(estado->jogador.nome, estado->jogador.score);

    // 2. Carrega o ranking atualizado
    RankingEntry ranking[MAX_RANKING];
    carregar_ranking(ranking);

    // 3. Limpa a tela e mostra cabeçalho
    screenClear();
    printf("\n  === RESULTADOS FINAIS ===\n");
    printf("  Jogador: %s\n", estado->jogador.nome);
    printf("  Tempo: %.2f segundos\n", estado->tempo_decorrido);
    printf("  Pontuação: %lld\n\n", estado->jogador.score);

    // 4. Mostra TOP 5 formatado corretamente
    screenSetColor(CYAN, BLACK);
    printf("  === TOP 5 RANKING ===\n");
    screenSetNormal();

    int posicao_jogador = -1;
    int ranking_valido = 0;
    int posicao_atual = 1; // Contador de posições válidas

    for(int i = 0; i < MAX_RANKING && ranking_valido < 5; i++) {
        // Pula entradas inválidas
        if(ranking[i].nome[0] == '\0' || ranking[i].score <= 0) continue;

        ranking_valido++;
        
        // Verifica se é a posição do jogador atual
        if(strcmp(ranking[i].nome, estado->jogador.nome) == 0 && 
           ranking[i].score == estado->jogador.score) {
            posicao_jogador = posicao_atual;
            screenSetColor(YELLOW, BLACK);
            printf("  > %d. %-15s %10lld pts <\n", posicao_atual, ranking[i].nome, ranking[i].score);
            screenSetNormal();
        } else {
            printf("    %d. %-15s %10lld pts\n", posicao_atual, ranking[i].nome, ranking[i].score);
        }
        
        posicao_atual++;
    }

    // 5. Mostra posição do jogador se não estiver no TOP 5
    if(posicao_jogador == -1) {
        // Encontra a posição real do jogador no ranking completo
        for(int i = 0; i < MAX_RANKING; i++) {
            if(strcmp(ranking[i].nome, estado->jogador.nome) == 0 && 
               ranking[i].score == estado->jogador.score) {
                posicao_jogador = i + 1;
                printf("\n  Sua posição no ranking geral: #%d\n", posicao_jogador);
                break;
            }
        }
    }

    // 6. Se não encontrou registros válidos
    if(ranking_valido == 0) {
        printf("  Nenhum recorde registrado ainda!\n");
    }

    // 7. Mostra mensagem de saída
    printf("\nPressione ENTER para sair...");
    fflush(stdout);
    
    // 8. Espera ENTER para sair
    int c;
    while((c = getchar()) != '\n' && c != EOF);
    getchar(); // Captura o ENTER
    
    timerDestroy();
}