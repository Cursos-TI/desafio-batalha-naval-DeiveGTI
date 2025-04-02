#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 15
#define HABILIDADE_TAM 5

void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

void criarHabilidadeCone(int habilidade[HABILIDADE_TAM][HABILIDADE_TAM]) {
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            if (i == 0 && j == 2) habilidade[i][j] = 1;
            else if (i == 1 && j >= 1 && j <= 3) habilidade[i][j] = 1;
            else if (i == 2) habilidade[i][j] = 1;
            else habilidade[i][j] = 0;
        }
    }
}

void criarHabilidadeCruz(int habilidade[HABILIDADE_TAM][HABILIDADE_TAM]) {
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            if (i == 1 || j == 2) habilidade[i][j] = 1;
            else habilidade[i][j] = 0;
        }
    }
}

void criarHabilidadeOctaedro(int habilidade[HABILIDADE_TAM][HABILIDADE_TAM]) {
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            if ((i == 0 || i == 2 || i == 4) && j == 2) habilidade[i][j] = 1;
            else if (i == 1 && j >= 1 && j <= 3) habilidade[i][j] = 1;
            else if (i == 3 && j >= 1 && j <= 3) habilidade[i][j] = 1;
            else habilidade[i][j] = 0;
        }
    }
}

void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int habilidade[HABILIDADE_TAM][HABILIDADE_TAM], int x, int y) {
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            int posX = x + i - HABILIDADE_TAM/2;
            int posY = y + j - HABILIDADE_TAM/2;
            
            if (posX >= 0 && posX < TAMANHO && posY >= 0 && posY < TAMANHO) {
                if (habilidade[i][j] == 1) {
                    tabuleiro[posX][posY] = 1;
                }
            }
        }
    }
}

void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\nTabuleiro com Habilidades Especiais:\n");
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void exibirHabilidade(int habilidade[HABILIDADE_TAM][HABILIDADE_TAM]) {
    printf("\nPadrão da Habilidade:\n");
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            printf("%d ", habilidade[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));
    int tabuleiro[TAMANHO][TAMANHO];
    int cone[HABILIDADE_TAM][HABILIDADE_TAM];
    int cruz[HABILIDADE_TAM][HABILIDADE_TAM];
    int octaedro[HABILIDADE_TAM][HABILIDADE_TAM];
    
    inicializarTabuleiro(tabuleiro);
    
    // Criar padrões de habilidades
    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);
    
    printf("=== BATALHA NAVAL - NIVEL MESTRE ===\n");
    
    // Aplicar habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, 3, 3);
    aplicarHabilidade(tabuleiro, cruz, 7, 7);
    aplicarHabilidade(tabuleiro, octaedro, 10, 10);
    
    // Exibir padrões de habilidades
    printf("\nHabilidade Cone:");
    exibirHabilidade(cone);
    
    printf("\nHabilidade Cruz:");
    exibirHabilidade(cruz);
    
    printf("\nHabilidade Octaedro:");
    exibirHabilidade(octaedro);
    
    // Exibir tabuleiro com áreas afetadas
    exibirTabuleiro(tabuleiro);
    
    return 0;
}