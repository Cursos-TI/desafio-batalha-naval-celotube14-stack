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
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se é possível posicionar um navio
int podePosicionar(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char orientacao) {
    if (orientacao == 'H') { // Horizontal
        if (coluna + NAVIO > TAMANHO) return 0; // Fora do limite
        for (int j = 0; j < NAVIO; j++) {
            if (tabuleiro[linha][coluna + j] != AGUA) return 0; // Já ocupado
        }
    } else if (orientacao == 'V') { // Vertical
        if (linha + NAVIO > TAMANHO) return 0; // Fora do limite
        for (int i = 0; i < NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] != AGUA) return 0; // Já ocupado
        }
    }
    return 1; // Pode posicionar
}

// Função para posicionar o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char orientacao) {
    if (orientacao == 'H') {
        for (int j = 0; j < NAVIO; j++) {
            tabuleiro[linha][coluna + j] = NAVIO_VAL;
        }
    } else if (orientacao == 'V') {
        for (int i = 0; i < NAVIO; i++) {
            tabuleiro[linha + i][coluna] = NAVIO_VAL;
        }
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];

    // Inicializar tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Coordenadas dos navios (definidas no código)
    int linha1 = 2, coluna1 = 3; // Navio horizontal
    int linha2 = 5, coluna2 = 5; // Navio vertical

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

    // Exibir tabuleiro
    imprimirTabuleiro(tabuleiro);

    return 0;
}
