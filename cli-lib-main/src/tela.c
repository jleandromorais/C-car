#include "tela.h"
#include "screen.h"  // Incluir a biblioteca screen
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

void mostrar_titulo() {
    screenClear();
    screenSetColor(YELLOW, BLACK);  // Configura cor para o título
    
    printf("         ██████╗  ═══   ██████╗  █████╗  ██████╗\n");
    printf("        ██╔════╝       ██╔═══╗  ██╔══██╗██╔══██╗\n");
    printf("        ██║            ██║   ║  ███████║██████╔╝\n");
    printf("        ██║            ██║   ║  ██╔══██║██╔══██╗\n");
    printf("        ╚██████╗       ╚██████╔╝██║  ██║██║  ██║\n");
    printf("         ╚═════╝        ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝\n");
    
    screenSetNormal();  // Volta às cores normais
}

void mostrar_menu_inicio(Jogador *jogador) {
    screenInit(1);  
    mostrar_titulo();
    
    screenSetColor(CYAN, BLACK);
    screenGotoxy(SCRSTARTX + 10, SCRSTARTY + 10);
    printf("PRESSIONE Enter PARA COMECAR");
    fflush(stdout);

    // Desativa modo raw ANTES da leitura de teclado
    disable_raw_mode(); 

    while (getchar() != '\n');  // Espera Enter

    screenClear();
    screenGotoxy(SCRSTARTX + 5, SCRSTARTY + 5);
    printf("NOME DO JOGADOR: ");
    fflush(stdout);

    if (fgets(jogador->nome, 21, stdin) == NULL) {
        strcpy(jogador->nome, "Jogador");  // Nome padrão
    }

    jogador->nome[strcspn(jogador->nome, "\n")] = '\0';
    jogador->nome[20] = '\0';

    screenClear();

    // Só reativa modo raw depois que terminou toda entrada
    enable_raw_mode();  
}
