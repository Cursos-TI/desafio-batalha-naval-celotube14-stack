#include <stdio.h>

#define TAMANHO 10   // Tamanho fixo do tabuleiro
#define NAVIO 3      // Tamanho fixo dos navios
#define AGUA 0       // Representa água
#define NAVIO_VAL 3  // Representa navio no tabuleiro
#define HABILIDADE 5 // Representa área de efeito

// ---------- Funções utilitárias ----------

// Inicializa tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Exibe tabuleiro com índices
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
            if (tabuleiro[i][j] == AGUA)
                printf(" ~ "); // água
            else if (tabuleiro[i][j] == NAVIO_VAL)
                printf(" # "); // navio
            else if (tabuleiro[i][j] == HABILIDADE)
                printf(" * "); // área de habilidade
        }
        printf("\n");
    }
}

// Verifica se pode posicionar navio
int podePosicionar(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char orientacao) {
    if (orientacao == 'H') {
        if (coluna + NAVIO > TAMANHO) return 0;
        for (int j = 0; j < NAVIO; j++)
            if (tabuleiro[linha][coluna + j] != AGUA) return 0;
    } 
    else if (orientacao == 'V') {
        if (linha + NAVIO > TAMANHO) return 0;
        for (int i = 0; i < NAVIO; i++)
            if (tabuleiro[linha + i][coluna] != AGUA) return 0;
    }
    else if (orientacao == 'D') { // diagonal principal "\"
        if (linha + NAVIO > TAMANHO || coluna + NAVIO > TAMANHO) return 0;
        for (int k = 0; k < NAVIO; k++)
            if (tabuleiro[linha + k][coluna + k] != AGUA) return 0;
    }
    else if (orientacao == 'd') { // diagonal secundária "/"
        if (linha + NAVIO > TAMANHO || coluna - NAVIO + 1 < 0) return 0;
        for (int k = 0; k < NAVIO; k++)
            if (tabuleiro[linha + k][coluna - k] != AGUA) return 0;
    }
    return 1;
}

// Posiciona navio
void posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char orientacao) {
    if (orientacao == 'H')
        for (int j = 0; j < NAVIO; j++) tabuleiro[linha][coluna + j] = NAVIO_VAL;

    else if (orientacao == 'V')
        for (int i = 0; i < NAVIO; i++) tabuleiro[linha + i][coluna] = NAVIO_VAL;

    else if (orientacao == 'D')
        for (int k = 0; k < NAVIO; k++) tabuleiro[linha + k][coluna + k] = NAVIO_VAL;

    else if (orientacao == 'd')
        for (int k = 0; k < NAVIO; k++) tabuleiro[linha + k][coluna - k] = NAVIO_VAL;
}

// ---------- Construção de habilidades ----------

// Constrói matriz cone (5x5)
void construirCone(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (j >= 2 - i && j <= 2 + i) habilidade[i][j] = 1;
            else habilidade[i][j] = 0;
        }
    }
}

// Constrói matriz cruz (5x5)
void construirCruz(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 2 || j == 2) habilidade[i][j] = 1;
            else habilidade[i][j] = 0;
        }
    }
}

// Constrói matriz octaedro (5x5)
void construirOctaedro(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (abs(i - 2) + abs(j - 2) <= 2) habilidade[i][j] = 1;
            else habilidade[i][j] = 0;
        }
    }
}

// ---------- Aplicação de habilidades no tabuleiro ----------

// Sobrepõe matriz de habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int habilidade[5][5], int origemLinha, int origemColuna) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (habilidade[i][j] == 1) {
                int linha = origemLinha + i - 2;
                int coluna = origemColuna + j - 2;
                if (linha >= 0 && linha < TAMANHO && coluna >= 0 && coluna < TAMANHO) {
                    if (tabuleiro[linha][coluna] == AGUA) {
                        tabuleiro[linha][coluna] = HABILIDADE;
                    }
                }
            }
        }
    }
}

// ---------- Programa principal ----------
int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    int cone[5][5], cruz[5][5], octaedro[5][5];

    // Inicializar tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Posicionar navios
    if (podePosicionar(tabuleiro, 2, 3, 'H')) posicionarNavio(tabuleiro, 2, 3, 'H');
    if (podePosicionar(tabuleiro, 5, 5, 'V')) posicionarNavio(tabuleiro, 5, 5, 'V');
    if (podePosicionar(tabuleiro, 0, 0, 'D')) posicionarNavio(tabuleiro, 0, 0, 'D');
    if (podePosicionar(tabuleiro, 0, 9, 'd')) posicionarNavio(tabuleiro, 0, 9, 'd');

    // Construir habilidades
    construirCone(cone);
    construirCruz(cruz);
    construirOctaedro(octaedro);

    // Aplicar habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, 4, 4);       // cone com origem em (4,4)
    aplicarHabilidade(tabuleiro, cruz, 7, 2);       // cruz com origem em (7,2)
    aplicarHabilidade(tabuleiro, octaedro, 6, 7);   // octaedro com origem em (6,7)

    // Mostrar tabuleiro final
    imprimirTabuleiro(tabuleiro);

    return 0;
}

