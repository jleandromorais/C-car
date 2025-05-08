#include "tela.h"
#include "screen.h"  // Incluir a biblioteca screen
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void mostrar_titulo() {
    screenClear();
    screenSetColor(YELLOW, BLACK);  // Configura cor para o título
    
    printf("\n\n");   
    printf("         XXXXX    XXXXX     XXXX     XXXXX       XXXX       XXXXX     \n");
    printf("            XX   XX   XX   XX       XX   XX      XX   X    XX   XX    \n");
    printf("            XX   XX   XX   XX       XX   XX      XX    X   XX   XX    \n");
    printf("            XX   XX   XX   XX       XX   XX      XX    X   XXXXXXX    \n");
    printf("            XX   XX   XX   XX  XX   XX   XX      XX    X   XX   XX    \n");
    printf("        X   XX   XX   XX   XX   X   XX   XX      XX   X    XX   XX    \n");
    printf("         XXXX     XXXXX     XXXX     XXXXX       XXXX      XX   XX    \n");
    printf("\n");    
    printf("              XXXXX      XX    XXXXX     XX      XX   XXXXXXX          \n");
    printf("              XX  XX     XX   XX   XX    XX      XX   XX               \n");
    printf("              XX   XX    XX   XX   XX    XX      XX   XX               \n");
    printf("              XX    XX   XX   XXXXXXX     XX    XX    XXXXX            \n");
    printf("              XX     XX  XX   XX   XX      XX  XX     XX               \n");
    printf("              XX      XX XX   XX   XX       XXXX      XX               \n");
    printf("              XX      XXXXX   XX   XX        XX       XXXXXXX          \n");
    
    screenSetNormal();  // Volta às cores normais
}

void mostrar_menu_inicio(Jogador *jogador) {
    screenInit(1);  // Inicializa a tela com bordas
    
    mostrar_titulo();
    
    screenSetColor(CYAN, BLACK);
    screenGotoxy(SCRSTARTX + 10, SCRENDY - 2);
    printf("PRESSIONE ESPAÇO PARA COMECAR");
    screenSetNormal();
    
    char c;
    while (1) {
        if (read(STDIN_FILENO, &c, 1) == 1 && c == ' ') {
            break;
        }
    }

    disable_raw_mode();
    
    screenClear();
    screenGotoxy(SCRSTARTX + 5, SCRSTARTY + 5);
    printf("NOME DO JOGADOR: ");
    
    fgets(jogador->nome, 50, stdin);
    jogador->nome[strcspn(jogador->nome, "\n")] = '\0';

    enable_raw_mode();
    screenClear();
}