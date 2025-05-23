# 🚗 C-CAR

### CESAR School — Programação Imperativa e Funcional - 2025.1

---

## 👥 Integrantes do Projeto

- Gabriel Souza ([@06gabrielsouza](https://github.com/06gabrielsouza))
- Leandro Moraes([@jleandromorais](https://github.com/jleandromorais))
- Levi Moura ([@LeviMoraesMoura](https://github.com/LeviMoraesMoura))
- Enzo Antuña ([@Enzo-Antuna](https://github.com/Enzo-Antuna))
- Kayky Dias ([@kaykyDias04](https://github.com/kaykyDias04))

---

## 🏫 Instituição

CESAR School

---

## 🕹️ Nome do Jogo

**C-CAR**

---

## ⚙️ Como Compilar e Executar

### Pré-requisitos:

- Sistema operacional **Linux** ou **macOS** (ou uso de máquina virtual)
- Compilador `gcc`
- Biblioteca [CLI-lib](https://github.com/tgfb/cli-lib)

### Passo a passo:

1. Clone este repositório:

   ```bash
   git clone https://github.com/jleandromorais/clin-lib-main
   cd clin-lib-main
   ```

2. Baixe a CLI-lib:

   ```bash
   git submodule add https://github.com/tgfb/cli-lib.git
   ```

3. Compile o projeto:

   ```bash
   make
   ```

4. Execute o jogo:

   ```bash
   ./bin/jogo-carro
   ```

> ⚠️ Certifique-se de que você está com o terminal em modo compatível com `ncurses` e que o terminal suporta caracteres ASCII.

---

## 🎮 Sobre o Jogo

**C-CAR** é um jogo em modo texto onde o jogador controla um carro que precisa **desviar de troncos** que caem do topo da tela. Com o passar do tempo, o jogo fica **mais rápido** e mais obstáculos aparecem. O objetivo é **sobreviver o máximo possível**, acumulando pontos.

Agora, o jogo também possui **frutinhas especiais**:  
🍓 **Se o carro pegar uma frutinha, a pontuação é dobrada por 10 segundos**!


### 🎯 Regras:

* Você perde se colidir com um tronco.
* A cada segundo sobrevivido, sua pontuação aumenta.
* A dificuldade do jogo (velocidade e quantidade de troncos) aumenta conforme o tempo passa.
* Ao pegar uma frutinha, seus pontos serão **dobrados por 10 segundos**.

### ⌨️ Controles:

* `A`: Move o carro para a esquerda
* `D`: Move o carro para a direita
* `ESC`: Sai do jogo

---

## 📁 Estrutura do Projeto

```
/projeto
├── src/           → Código-fonte (.c)
├── include/       → Cabeçalhos (.h)
├── build/         → Saídas de compilação
├── cli-lib/       → Biblioteca CLI-lib
├── README.md      → Este arquivo
├── Makefile       → Arquivo opcional de build
└── LICENSE        → Licença (opcional)
```
---

## 📝 Licença

Este projeto pode ser distribuído sob a licença MIT. (opcional)

---
