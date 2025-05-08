# 🚗 C-CAR

### CESAR School — Programação Imperativa e Funcional - 2025.1

---

## 👥 Integrantes do Projeto

- Gabriel Souza (@06gabrielsouza)
- Leandro Moraes(@jleandromorais)
- Levi Moura (@colega3)
- Enzo Antuña (@colega4)
- Kayky Dias (@colega5)

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
   git clone https://github.com/seu-usuario/c-clib
   cd c-car
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

**C-CAR** é um jogo em modo texto onde o jogador controla um carro que precisa **desviar de pedras** que caem do topo da tela. Com o passar do tempo, o jogo fica **mais rápido** e mais obstáculos aparecem. O objetivo é **sobreviver o máximo possível**, acumulando pontos.

Agora, o jogo também possui **frutinhas especiais**:  
🍓 **Se o carro pegar uma frutinha, a pontuação é dobrada por 5 segundos**!

### 🎯 Regras:

* Você perde se colidir com uma pedra.
* A cada segundo sobrevivido, sua pontuação aumenta.
* A dificuldade do jogo (velocidade e quantidade de pedras) aumenta conforme o tempo passa.
* Ao pegar uma frutinha, seus pontos serão **dobrados por 5 segundos**.

### ⌨️ Controles:

* `A`: Move o carro para a esquerda
* `D`: Move o carro para a direita
* `Q`: Sai do jogo

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

## 📌 Requisitos Atendidos

* ✔️ Linguagem C
* ✔️ Biblioteca CLI-lib
* ✔️ Uso de structs e ponteiros
* ✔️ Alocação dinâmica de memória
* ✔️ Modularização com `.c` e `.h`
* ✔️ Interação com o usuário via teclado
* ✔️ Pontuação e aumento progressivo de dificuldade
* ✔️ Execução em terminal (modo texto)

---

## 📝 Licença

Este projeto pode ser distribuído sob a licença MIT. (opcional)

---
