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
     int opcao = 0;
    do {
        printf("\n\033[32mPRESSIONE [1] PARA COMECAR...\033[0m");
        printf("\n\033[32mPRESSIONE [2] PARA VER RANKING...\033[0m\n");
        printf("\n\033[33mOPÇÃO: \033[0m");
        fflush(stdout);

        char escolha[3];
        if (fgets(escolha, sizeof(escolha), stdin) != NULL) {
            opcao = atoi(escolha);
        }

        switch (opcao) {
            case 1:
                printf("\n\033[32mIniciando o jogo...\033[0m\n");
                break;
            case 2:
                printf("\n\033[36mExibindo ranking...\033[0m\n");
                // Aqui você pode chamar a função que mostra o ranking:
                // exibirRanking();
                   exibir_ranking();
                break;
            default:
                printf("\n\033[31mOpção inválida! Tente novamente.\033[0m\n");
        }

    } while (opcao != 1 && opcao != 2);

    // 6. Prepara para o jogo
    enable_raw_mode();  // Reativa modo raw para o jogo
    system("clear");    // Limpa a tela
}