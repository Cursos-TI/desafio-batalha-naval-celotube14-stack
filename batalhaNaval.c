#include <stdio.h>

#define TAMANHO 10   // Tamanho fixo do tabuleiro
#define NAVIO 3      // Tamanho fixo dos navios
#define AGUA 0       // Representa água
#define NAVIO_VAL 3  // Representa navio no tabuleiro

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\nTabuleiro:\n\n");

    // Cabeçalho das colunas
    printf("   ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d ", i); // índice da linha
        for (int j = 0; j < TAMANHO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se é possível posicionar um navio
int podePosicionar(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char orientacao) {
    if (orientacao == 'H') { // Horizontal
        if (coluna + NAVIO > TAMANHO) return 0;
        for (int j = 0; j < NAVIO; j++) {
            if (tabuleiro[linha][coluna + j] != AGUA) return 0;
        }
    } 
    else if (orientacao == 'V') { // Vertical
        if (linha + NAVIO > TAMANHO) return 0;
        for (int i = 0; i < NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] != AGUA) return 0;
        }
    }
    else if (orientacao == 'D') { // Diagonal principal (\)
        if (linha + NAVIO > TAMANHO || coluna + NAVIO > TAMANHO) return 0;
        for (int k = 0; k < NAVIO; k++) {
            if (tabuleiro[linha + k][coluna + k] != AGUA) return 0;
        }
    }
    else if (orientacao == 'd') { // Diagonal secundária (/)
        if (linha + NAVIO > TAMANHO || coluna - NAVIO + 1 < 0) return 0;
        for (int k = 0; k < NAVIO; k++) {
            if (tabuleiro[linha + k][coluna - k] != AGUA) return 0;
        }
    }
    return 1;
}

// Função para posicionar o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char orientacao) {
    if (orientacao == 'H') {
        for (int j = 0; j < NAVIO; j++) {
            tabuleiro[linha][coluna + j] = NAVIO_VAL;
        }
    } 
    else if (orientacao == 'V') {
        for (int i = 0; i < NAVIO; i++) {
            tabuleiro[linha + i][coluna] = NAVIO_VAL;
        }
    } 
    else if (orientacao == 'D') { // Diagonal principal (\)
        for (int k = 0; k < NAVIO; k++) {
            tabuleiro[linha + k][coluna + k] = NAVIO_VAL;
        }
    }
    else if (orientacao == 'd') { // Diagonal secundária (/)
        for (int k = 0; k < NAVIO; k++) {
            tabuleiro[linha + k][coluna - k] = NAVIO_VAL;
        }
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];

    // Inicializar tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Coordenadas dos navios (fixas para simplificação)
    int linha1 = 2, coluna1 = 3; // Navio horizontal
    int linha2 = 5, coluna2 = 5; // Navio vertical
    int linha3 = 0, coluna3 = 0; // Navio diagonal principal "\"
    int linha4 = 0, coluna4 = 9; // Navio diagonal secundária "/"

    // Posicionar navio horizontal
    if (podePosicionar(tabuleiro, linha1, coluna1, 'H')) {
        posicionarNavio(tabuleiro, linha1, coluna1, 'H');
    } else {
        printf("Erro: não foi possível posicionar o navio horizontal!\n");
    }

    // Posicionar navio vertical
    if (podePosicionar(tabuleiro, linha2, coluna2, 'V')) {
        posicionarNavio(tabuleiro, linha2, coluna2, 'V');
    } else {
        printf("Erro: não foi possível posicionar o navio vertical!\n");
    }

    // Posicionar navio diagonal principal
    if (podePosicionar(tabuleiro, linha3, coluna3, 'D')) {
        posicionarNavio(tabuleiro, linha3, coluna3, 'D');
    } else {
        printf("Erro: não foi possível posicionar o navio diagonal principal!\n");
    }

    // Posicionar navio diagonal secundária
    if (podePosicionar(tabuleiro, linha4, coluna4, 'd')) {
        posicionarNavio(tabuleiro, linha4, coluna4, 'd');
    } else {
        printf("Erro: não foi possível posicionar o navio diagonal secundária!\n");
    }

    // Exibir tabuleiro
    imprimirTabuleiro(tabuleiro);

    return 0;
}
