#include "../include/cenario.h"
#include "../include/tela.h"
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
    raw.c_lflag &= ~(ECHO | ICANON);  // Desabilita o modo canônico e o eco
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
    enable_raw_mode();

    Jogador jogador;
    mostrar_menu_inicio(&jogador);  // Correto: passar ponteiro

    printf("Bem-vindo, %s!\n", jogador.nome);
    printf("Controles: A (esquerda), D (direita), ESC (sair)\n");
    sleep(1);

    int pos = 5;  // posição inicial do jogador
    char c;

    while (1) {
        system("clear");  // ou system("cls") no Windows
        desenhar_cenario(pos);

        if (read(STDIN_FILENO, &c, 1) == 1) {
            if (c == 'a' && pos > 0) pos--;
            if (c == 'd' && pos < 11) pos++;
            if (c == 27) break;  // ESC
        }

        usleep(100000);
    }

    disable_raw_mode();

    printf("\nObrigado por jogar, %s!\n", jogador.nome);
    return 0;
}
