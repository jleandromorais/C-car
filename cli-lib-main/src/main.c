#include "../include/cenario.h"
#include "../include/tela.h"
#include "../include/ControleCar.h"
#include <termios.h>
#include <unistd.h> 
#include <fcntl.h> 

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

    EstadoJogo estado = inicializar_jogo(); 
    
      fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    
    
    executar_jogo_principal(&estado);
    finalizar_jogo(&estado);
    
    disable_raw_mode();
    return 0;
}