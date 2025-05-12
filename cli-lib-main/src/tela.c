#include "tela.h"
#include "screen.h"  // Incluir a biblioteca screen
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
    // 1. Configuração inicial
    disable_raw_mode();  // Permite entrada normal do teclado
    system("clear");     // Limpa a tela

    // 2. Mostra o título ASCII
    mostrar_titulo();

    // 3. Mostra instrução e já posiciona para digitar
    printf("\n\n\033[36mDIGITE SEU NOME: \033[0m");  // Mensagem em ciano
    fflush(stdout);  // Garante que a mensagem apareça antes da leitura

    // 4. Lê o nome do jogador
    char buffer[21];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Remove o '\n' final e armazena no jogador
        buffer[strcspn(buffer, "\n")] = '\0';
        strncpy(jogador->nome, buffer, 20);
        jogador->nome[20] = '\0';  // Garante terminação nula
    } else {
        strcpy(jogador->nome, "Jogador");  // Nome padrão se falhar
    }

    // 5. Mensagem para continuar (opcional)
    printf("\n\033[32mPRESSIONE ENTER PARA COMECAR...\033[0m");
    while (getchar() != '\n');  // Espera Enter

    // 6. Prepara para o jogo
    enable_raw_mode();  // Reativa modo raw para o jogo
    system("clear");    // Limpa a tela
}