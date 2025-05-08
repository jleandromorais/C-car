#include "../include/cenario.h"
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
    atexit(disable_raw_mode);

    int pos = 0;
    char c;
    
    printf("Controles: A (esquerda), D (direita), ESC (sair)\n");
    printf("Carro SEMPRE visível e passando por cima quando necessário!\n");
    sleep(1);

    while (1) {
        desenhar_cenario(pos);  // Agora passando o valor diretamente
        
        if (read(STDIN_FILENO, &c, 1) == 1) {
            if (c == 'a' && pos > 0) pos--;
            if (c == 'd' && pos < 11) pos++;
            if (c == 27) break;
        }
        
        usleep(100000);
    }
    
    printf("\nJogo encerrado!\n");
    return 0;
}