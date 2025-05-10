#ifndef TELA_H
#define TELA_H

// Declarações das funções de modo raw
void enable_raw_mode();
void disable_raw_mode();

typedef struct {
    char nome[21];
    int score;
} Jogador;

void mostrar_titulo();
void mostrar_menu_inicio(Jogador *jogador);

#endif