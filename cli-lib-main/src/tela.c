#include "tela.h"
#include "screen.h"  // Incluir a biblioteca screen
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    
    // Correção principal aqui:
    fgets(jogador->nome, 21, stdin); // Limita a 20 caracteres + '\0'
    jogador->nome[strcspn(jogador->nome, "\n")] = '\0'; // Remove a quebra de linha
    jogador->nome[20] = '\0'; // Garante terminação mesmo se o nome for muito longo
    
    enable_raw_mode();
    screenClear();
}