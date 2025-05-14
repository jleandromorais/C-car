#ifndef TELA_H
#define TELA_H

typedef struct {
    char nome[21];
    int score;
} Jogador;

// Funções de controle do terminal
void enable_raw_mode();
void disable_raw_mode();

// Funções de interface
void mostrar_titulo();
void mostrar_menu_inicio(Jogador *jogador);

#endif