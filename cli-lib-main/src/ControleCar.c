#include "../include/controleCar.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "../include/cenario.h"

EstadoJogo inicializar_jogo() {
    EstadoJogo estado;
    estado.posicao = 5;  // Posição inicial
    estado.tempo_decorrido = 0;
    
    mostrar_menu_inicio(&estado.jogador);
    printf("Bem-vindo, %s!\n", estado.jogador.nome);
    printf("Controles: A (esquerda), D (direita), ESC (sair)\n");
    sleep(1);
    
    timerInit(0);  // Inicializa o timer
    return estado;
}

void executar_jogo_principal(EstadoJogo *estado) {
    char c;
    
    while (1) {
        system("clear");
        
        // Atualiza tempo
        estado->tempo_decorrido = getTimeDiff() / 1000.0f; // Converte para segundos
estado->tempo_decorrido = fmaxf(estado->tempo_decorrido, 0.0f); // Garante ≥ 0
   printf("Tempo: %02d:%02d\n",
           (int)(estado->tempo_decorrido) / 60,
           (int)estado->tempo_decorrido % 60); 

        
        desenhar_cenario(estado->posicao,estado->tempo_decorrido);

        if (read(STDIN_FILENO, &c, 1) == 1) {
            if (c == 'a' && estado->posicao > 0) estado->posicao--;
            if (c == 'd' && estado->posicao < 11) estado->posicao++;
            if (c == 27) break;  // ESC
        }

        usleep(100000);
    }
}

void finalizar_jogo(EstadoJogo *estado) {
    printf("\nTempo total de jogo: %.2f segundos\n", estado->tempo_decorrido);
    printf("Obrigado por jogar, %s!\n", estado->jogador.nome);
    timerDestroy();
}