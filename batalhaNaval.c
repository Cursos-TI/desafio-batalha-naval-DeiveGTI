#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

// Definições de tamanho para cada nível
#define TAM_NOVATO 5
#define TAM_AVENTUREIRO 10
#define TAM_MESTRE 15
#define HABILIDADE_TAM 5

// Estrutura para representar o jogo
typedef struct {
    int **tabuleiro;
    int tamanho;
    int nivel;
    bool habilidades_ativas;
} Jogo;

// Protótipos de funções
void inicializarJogo(Jogo *jogo, int nivel);
void liberarJogo(Jogo *jogo);
void exibirTabuleiro(Jogo jogo);
void exibirMenuPrincipal();
void exibirMenuNovato();
void exibirMenuAventureiro();
void exibirMenuMestre();
void posicionarNavio(Jogo *jogo, int x, int y, int tamanho, int direcao);
bool verificarPosicao(Jogo jogo, int x, int y, int tamanho, int direcao);
void criarHabilidadeCone(int habilidade[HABILIDADE_TAM][HABILIDADE_TAM]);
void criarHabilidadeCruz(int habilidade[HABILIDADE_TAM][HABILIDADE_TAM]);
void criarHabilidadeOctaedro(int habilidade[HABILIDADE_TAM][HABILIDADE_TAM]);
void aplicarHabilidade(Jogo *jogo, int habilidade[HABILIDADE_TAM][HABILIDADE_TAM], int x, int y);
void exibirHabilidade(int habilidade[HABILIDADE_TAM][HABILIDADE_TAM]);

int main() {
    srand(time(NULL));
    Jogo jogo;
    int opcao = 0;
    int sub_opcao = 0;
    
    do {
        exibirMenuPrincipal();
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: // Nível Novato
                inicializarJogo(&jogo, 1);
                do {
                    exibirMenuNovato();
                    scanf("%d", &sub_opcao);
                    
                    switch(sub_opcao) {
                        case 1: // Posicionar navio horizontal
                            posicionarNavio(&jogo, 1, 1, 3, 0);
                            printf("Navio horizontal posicionado!\n");
                            break;
                        case 2: // Posicionar navio vertical
                            posicionarNavio(&jogo, 3, 0, 2, 1);
                            printf("Navio vertical posicionado!\n");
                            break;
                        case 3: // Exibir tabuleiro
                            exibirTabuleiro(jogo);
                            break;
                        case 0: // Voltar
                            break;
                        default:
                            printf("Opção inválida!\n");
                    }
                } while(sub_opcao != 0);
                liberarJogo(&jogo);
                break;
                
            case 2: // Nível Aventureiro
                inicializarJogo(&jogo, 2);
                do {
                    exibirMenuAventureiro();
                    scanf("%d", &sub_opcao);
                    
                    switch(sub_opcao) {
                        case 1: // Posicionar navio horizontal
                            posicionarNavio(&jogo, 2, 2, 4, 0);
                            printf("Navio horizontal posicionado!\n");
                            break;
                        case 2: // Posicionar navio vertical
                            posicionarNavio(&jogo, 5, 1, 3, 1);
                            printf("Navio vertical posicionado!\n");
                            break;
                        case 3: // Posicionar navio diagonal 1
                            posicionarNavio(&jogo, 1, 6, 3, 2);
                            printf("Navio diagonal (baixo/direita) posicionado!\n");
                            break;
                        case 4: // Posicionar navio diagonal 2
                            posicionarNavio(&jogo, 8, 2, 2, 3);
                            printf("Navio diagonal (cima/direita) posicionado!\n");
                            break;
                        case 5: // Exibir tabuleiro
                            exibirTabuleiro(jogo);
                            break;
                        case 0: // Voltar
                            break;
                        default:
                            printf("Opção inválida!\n");
                    }
                } while(sub_opcao != 0);
                liberarJogo(&jogo);
                break;
                
            case 3: // Nível Mestre
                inicializarJogo(&jogo, 3);
                jogo.habilidades_ativas = true;
                
                int cone[HABILIDADE_TAM][HABILIDADE_TAM];
                int cruz[HABILIDADE_TAM][HABILIDADE_TAM];
                int octaedro[HABILIDADE_TAM][HABILIDADE_TAM];
                
                criarHabilidadeCone(cone);
                criarHabilidadeCruz(cruz);
                criarHabilidadeOctaedro(octaedro);
                
                do {
                    exibirMenuMestre();
                    scanf("%d", &sub_opcao);
                    
                    switch(sub_opcao) {
                        case 1: // Aplicar habilidade Cone
                            aplicarHabilidade(&jogo, cone, 3, 3);
                            printf("Habilidade Cone aplicada!\n");
                            break;
                        case 2: // Aplicar habilidade Cruz
                            aplicarHabilidade(&jogo, cruz, 7, 7);
                            printf("Habilidade Cruz aplicada!\n");
                            break;
                        case 3: // Aplicar habilidade Octaedro
                            aplicarHabilidade(&jogo, octaedro, 10, 10);
                            printf("Habilidade Octaedro aplicada!\n");
                            break;
                        case 4: // Exibir padrões de habilidades
                            printf("\nPadrão Cone:\n");
                            exibirHabilidade(cone);
                            printf("\nPadrão Cruz:\n");
                            exibirHabilidade(cruz);
                            printf("\nPadrão Octaedro:\n");
                            exibirHabilidade(octaedro);
                            break;
                        case 5: // Exibir tabuleiro
                            exibirTabuleiro(jogo);
                            break;
                        case 0: // Voltar
                            break;
                        default:
                            printf("Opção inválida!\n");
                    }
                } while(sub_opcao != 0);
                liberarJogo(&jogo);
                break;
                
            case 0: // Sair
                printf("Saindo do jogo...\n");
                break;
                
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);
    
    return 0;
}

void inicializarJogo(Jogo *jogo, int nivel) {
    jogo->nivel = nivel;
    jogo->habilidades_ativas = false;
    
    // Definir tamanho do tabuleiro conforme o nível
    switch(nivel) {
        case 1: jogo->tamanho = TAM_NOVATO; break;
        case 2: jogo->tamanho = TAM_AVENTUREIRO; break;
        case 3: jogo->tamanho = TAM_MESTRE; break;
    }
    
    // Alocar memória para o tabuleiro
    jogo->tabuleiro = (int **)malloc(jogo->tamanho * sizeof(int *));
    for (int i = 0; i < jogo->tamanho; i++) {
        jogo->tabuleiro[i] = (int *)malloc(jogo->tamanho * sizeof(int));
        for (int j = 0; j < jogo->tamanho; j++) {
            jogo->tabuleiro[i][j] = 0;
        }
    }
}

void liberarJogo(Jogo *jogo) {
    for (int i = 0; i < jogo->tamanho; i++) {
        free(jogo->tabuleiro[i]);
    }
    free(jogo->tabuleiro);
    jogo->tabuleiro = NULL;
}

void exibirTabuleiro(Jogo jogo) {
    printf("\nTabuleiro %dx%d:\n", jogo.tamanho, jogo.tamanho);
    for (int i = 0; i < jogo.tamanho; i++) {
        for (int j = 0; j < jogo.tamanho; j++) {
            printf("%d ", jogo.tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void posicionarNavio(Jogo *jogo, int x, int y, int tamanho, int direcao) {
    if (!verificarPosicao(*jogo, x, y, tamanho, direcao)) {
        printf("Posição inválida para o navio!\n");
        return;
    }
    
    switch(direcao) {
        case 0: // Horizontal
            for (int i = 0; i < tamanho; i++) {
                jogo->tabuleiro[x][y + i] = 1;
            }
            break;
        case 1: // Vertical
            for (int i = 0; i < tamanho; i++) {
                jogo->tabuleiro[x + i][y] = 1;
            }
            break;
        case 2: // Diagonal (baixo/direita)
            for (int i = 0; i < tamanho; i++) {
                jogo->tabuleiro[x + i][y + i] = 1;
            }
            break;
        case 3: // Diagonal (cima/direita)
            for (int i = 0; i < tamanho; i++) {
                jogo->tabuleiro[x - i][y + i] = 1;
            }
            break;
    }
}

bool verificarPosicao(Jogo jogo, int x, int y, int tamanho, int direcao) {
    switch(direcao) {
        case 0: // Horizontal
            if (y + tamanho > jogo.tamanho) return false;
            for (int i = 0; i < tamanho; i++) {
                if (jogo.tabuleiro[x][y + i] != 0) return false;
            }
            break;
        case 1: // Vertical
            if (x + tamanho > jogo.tamanho) return false;
            for (int i = 0; i < tamanho; i++) {
                if (jogo.tabuleiro[x + i][y] != 0) return false;
            }
            break;
        case 2: // Diagonal (baixo/direita)
            if (x + tamanho > jogo.tamanho || y + tamanho > jogo.tamanho) return false;
            for (int i = 0; i < tamanho; i++) {
                if (jogo.tabuleiro[x + i][y + i] != 0) return false;
            }
            break;
        case 3: // Diagonal (cima/direita)
            if (x - tamanho < 0 || y + tamanho > jogo.tamanho) return false;
            for (int i = 0; i < tamanho; i++) {
                if (jogo.tabuleiro[x - i][y + i] != 0) return false;
            }
            break;
    }
    return true;
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

void aplicarHabilidade(Jogo *jogo, int habilidade[HABILIDADE_TAM][HABILIDADE_TAM], int x, int y) {
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            int posX = x + i - HABILIDADE_TAM/2;
            int posY = y + j - HABILIDADE_TAM/2;
            
            if (posX >= 0 && posX < jogo->tamanho && posY >= 0 && posY < jogo->tamanho) {
                if (habilidade[i][j] == 1) {
                    jogo->tabuleiro[posX][posY] = 1;
                }
            }
        }
    }
}

void exibirHabilidade(int habilidade[HABILIDADE_TAM][HABILIDADE_TAM]) {
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            printf("%d ", habilidade[i][j]);
        }
        printf("\n");
    }
}

void exibirMenuPrincipal() {
    printf("\n=== BATALHA NAVAL UNIFICADA ===\n");
    printf("1. Nível Novato (5x5)\n");
    printf("2. Nível Aventureiro (10x10)\n");
    printf("3. Nível Mestre (15x15) com Habilidades Especiais\n");
    printf("0. Sair\n");
    printf("Escolha o nível: ");
}

void exibirMenuNovato() {
    printf("\n=== NÍVEL NOVATO ===\n");
    printf("1. Posicionar navio horizontal (tamanho 3)\n");
    printf("2. Posicionar navio vertical (tamanho 2)\n");
    printf("3. Exibir tabuleiro\n");
    printf("0. Voltar\n");
    printf("Opção: ");
}

void exibirMenuAventureiro() {
    printf("\n=== NÍVEL AVENTUREIRO ===\n");
    printf("1. Posicionar navio horizontal (tamanho 4)\n");
    printf("2. Posicionar navio vertical (tamanho 3)\n");
    printf("3. Posicionar navio diagonal (baixo/direita, tamanho 3)\n");
    printf("4. Posicionar navio diagonal (cima/direita, tamanho 2)\n");
    printf("5. Exibir tabuleiro\n");
    printf("0. Voltar\n");
    printf("Opção: ");
}

void exibirMenuMestre() {
    printf("\n=== NÍVEL MESTRE ===\n");
    printf("1. Aplicar habilidade Cone\n");
    printf("2. Aplicar habilidade Cruz\n");
    printf("3. Aplicar habilidade Octaedro\n");
    printf("4. Exibir padrões de habilidades\n");
    printf("5. Exibir tabuleiro\n");
    printf("0. Voltar\n");
    printf("Opção: ");
}