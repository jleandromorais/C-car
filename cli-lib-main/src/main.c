#include "../include/cenario.h"
#include "../include/tela.h"
#include "../include/timer.h"  // Adicione esta linha
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

static struct termios old_term;

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_term);
}

void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &old_term);
    struct termios raw = old_term;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
    enable_raw_mode();
    timerInit(0);  // Inicializa o timer começando em 0

    Jogador jogador;
    mostrar_menu_inicio(&jogador);

    printf("Bem-vindo, %s!\n", jogador.nome);
    printf("Controles: A (esquerda), D (direita), ESC (sair)\n");
    sleep(1);

    int pos = 5;
    char c;
    float tempo_decorrido = 0;  // Declara a variável do tempo

    while (1) {
        system("clear");
        
        // Atualiza o tempo decorrido (em segundos)
        tempo_decorrido = getTimeDiff() / 1000.0f;
        printf("Tempo: %02d:%05.2f\n", (int)tempo_decorrido / 60, fmod(tempo_decorrido, 60));  // Formato MM:SS.ss
        
        desenhar_cenario(pos);

        if (read(STDIN_FILENO, &c, 1) == 1) {
            if (c == 'a' && pos > 0) pos--;
            if (c == 'd' && pos < 11) pos++;
            if (c == 27) break;  // ESC
        }

        usleep(100000);  // 100ms de delay
    }

    disable_raw_mode();
    
    // Mostra o tempo final quando sair
    printf("\nTempo total de jogo: %.2f segundos\n", tempo_decorrido);
    printf("Obrigado por jogar, %s!\n", jogador.nome);
    
    timerDestroy();
    return 0;
}