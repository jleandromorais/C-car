#include "../include/tela.h"
#include "../include/screen.h"  // Incluir a biblioteca screen
#include "../include/ranking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

void mostrar_titulo() {
    screenSetColor(YELLOW, BLACK);
    printf("         ██████╗  ═══   ██████╗  █████╗  ██████╗\n");
    printf("        ██╔════╝       ██╔═══╗  ██╔══██╗██╔══██╗\n");
    printf("        ██║            ██║   ║  ███████║██████╔╝\n");
    printf("        ██║            ██║   ║  ██╔══██║██╔══██╗\n");
    printf("        ╚██████╗       ╚██████╔╝██║  ██║██║  ██║\n");
    printf("         ╚═════╝        ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝\n");
    screenSetNormal();
}

void mostrar_menu_inicio(Jogador *jogador) {
    // Configuração inicial
    disable_raw_mode();
    screenInit(1); // Limpa tela e desenha bordas
    
    // Posição ajustada para a esquerda (subtraímos mais 10 colunas)
    const int offset_esquerda = 10;
    const int centro_x = (MAXX / 2) - offset_esquerda;
    const int centro_y = MAXY / 2;
    
    // Título ASCII (mais para esquerda)
    screenGotoxy(centro_x - 15, centro_y - 5);
    screenSetColor(YELLOW, BLACK);
    printf("         ██████╗  ═══   ██████╗  █████╗  ██████╗");
    
    screenGotoxy(centro_x - 15, centro_y - 4);
    printf("        ██╔════╝       ██╔═══╗  ██╔══██╗██╔══██╗");
    
    screenGotoxy(centro_x - 15, centro_y - 3);
    printf("        ██║            ██║   ║  ███████║██████╔╝");
    
    screenGotoxy(centro_x - 15, centro_y - 2);
    printf("        ██║            ██║   ║  ██╔══██║██╔══██╗");
    
    screenGotoxy(centro_x - 15, centro_y - 1);
    printf("        ╚██████╗       ╚██████╔╝██║  ██║██║  ██║");
    
    screenGotoxy(centro_x - 15, centro_y);
    printf("         ╚═════╝        ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝");
    screenSetNormal();

    // Entrada do nome (mais para esquerda)
    screenGotoxy(centro_x - 10, centro_y + 2);
    screenSetColor(CYAN, BLACK);
    printf("DIGITE SEU NOME: ");
    screenSetNormal();
    
    // Posiciona cursor para entrada
    screenShowCursor();
    screenGotoxy(centro_x - 10 + 17, centro_y + 2);
    screenUpdate();
    
    // Lê o nome do jogador
    char buffer[21];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        strncpy(jogador->nome, buffer, 20);
        jogador->nome[20] = '\0';
    } else {
        strcpy(jogador->nome, "Jogador");
    }
    screenHideCursor();

    // Menu de opções (mais para esquerda)
    int opcao = 0;
    do {
        screenGotoxy(centro_x - 15, centro_y + 4);
        screenSetColor(GREEN, BLACK);
        printf("PRESSIONE [1] PARA COMECAR...");
        
        screenGotoxy(centro_x - 15, centro_y + 5);
        printf("PRESSIONE [2] PARA VER RANKING...");
        
        screenGotoxy(centro_x - 15, centro_y + 6);
        screenSetColor(YELLOW, BLACK);
        printf("OPÇÃO: ");
        screenSetNormal();
        
        screenShowCursor();
        screenGotoxy(centro_x - 15 + 7, centro_y + 6);
        screenUpdate();

        char escolha[3];
        if (fgets(escolha, sizeof(escolha), stdin) != NULL) {
            opcao = atoi(escolha);
        }

        switch (opcao) {
            case 1:
                screenGotoxy(centro_x - 10, centro_y + 8);
                screenSetColor(GREEN, BLACK);
                printf("Iniciando o jogo...");
                screenSetNormal();
                screenUpdate();
                sleep(1);
                break;
            case 2:
                screenGotoxy(centro_x - 10, centro_y + 8);
                screenSetColor(CYAN, BLACK);
                printf("Exibindo ranking...");
                screenSetNormal();
                screenUpdate();
                sleep(1);
                exibir_ranking();
                screenInit(1);
                break;
            default:
                screenGotoxy(centro_x - 15, centro_y + 8);
                screenSetColor(RED, BLACK);
                printf("Opção inválida! Tente novamente.");
                screenSetNormal();
                screenUpdate();
                sleep(1);
                screenGotoxy(centro_x - 15, centro_y + 8);
                printf("                                 ");
                screenUpdate();
        }
    } while (opcao != 1 && opcao != 2);

    enable_raw_mode();
    screenClear();
}