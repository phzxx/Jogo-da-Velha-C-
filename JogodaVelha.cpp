#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>  // Adicionado para configurar o local

// Defini??o de constantes para os caracteres do jogo
#define JOGADOR_X 'X'
#define JOGADOR_O 'O'
#define EMPATE 'E'

// Estrutura para armazenar informa??es do jogador
struct Jogador {
    char nome[50];
    int placar;
};

// Prot?tipo da fun??o principal
int main();


// Prot?tipo da fun??o para exibir o ranking
void verRanking(struct Jogador jogadores[], int numJogadores);

// Fun??o para inicializar o tabuleiro do jogo com caracteres em branco.
void inicializarTabuleiro(char tabuleiro[3][3]) {
    for (int l = 0; l < 3; l++) {
        for (int c = 0; c < 3; c++) {
            tabuleiro[l][c] = ' ';
        }
    }
}

// Fun??o para exibir o tabuleiro
void exibirTabuleiro(char tabuleiro[3][3]) {
    printf("  0   1   2\n");
    for (int l = 0; l < 3; l++) {
        printf("%d ", l);
        for (int c = 0; c < 3; c++) {
            printf("%c ", tabuleiro[l][c]);
            if (c < 2) {
                printf("| ");
            }
        }
        printf("\n");
        if (l < 2) {
            printf(" ----------\n");
        }
    }
}

// Fun??o para verificar se algu?m ganhou
char verificarGanhador(char tabuleiro[3][3]) {
    // Verifica linhas
    for (int linha = 0; linha < 3; linha++) {
        if (tabuleiro[linha][0] == tabuleiro[linha][1] && tabuleiro[linha][1] == tabuleiro[linha][2] &&
            tabuleiro[linha][0] != ' ')
            return tabuleiro[linha][0];
    }

    // Verifica colunas
    for (int coluna = 0; coluna < 3; coluna++) {
        if (tabuleiro[0][coluna] == tabuleiro[1][coluna] && tabuleiro[1][coluna] == tabuleiro[2][coluna] &&
            tabuleiro[0][coluna] != ' ')
            return tabuleiro[0][coluna];
    }

    // Verifica diagonais
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[0][0] != ' ')
        return tabuleiro[0][0];

    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[0][2] != ' ')
        return tabuleiro[0][2];

    return EMPATE;
}

// Fun??o para realizar a jogada do jogador
void jogadaJogador(char tabuleiro[3][3], char jogador_atual) {
    int linha, coluna;
    int posicaoValida;
    int jogadaValida;

    do {
        posicaoValida = 1;
        jogadaValida = 1;

        do {
            printf("Informe a linha (0 a 2): ");
            if (scanf("%d", &linha) != 1) {
                printf("Jogada inv?lida. Escolha outra.\n");
                jogadaValida = 0;
                while (getchar() != '\n')
                    ;
            } else {
                jogadaValida = 1;
            }
        } while (jogadaValida == 0);

        jogadaValida = 1;

        do {
            printf("Informe a coluna (0 a 2): ");
            if (scanf("%d", &coluna) != 1) {
                printf("Jogada inv?lida. Escolha outra.\n");
                jogadaValida = 0;
                while (getchar() != '\n')
                    ;
            } else {
                jogadaValida = 1;
            }
        } while (jogadaValida == 0);

        // Verifica se a posi??o ? v?lida
        if (tabuleiro[linha][coluna] != ' ')
            printf("Posi??o j? ocupada. Escolha outra.\n");
        if (linha >= 3 || coluna >= 3) {
            printf("Posi??o inv?lida. Escolha outra.\n");
            posicaoValida = 0;
        }

    } while (tabuleiro[linha][coluna] != ' ' || posicaoValida == 0);

    tabuleiro[linha][coluna] = jogador_atual;
}

// Fun??o para realizar a jogada da m?quina
void jogadaMaquina(char tabuleiro[3][3]) {
    int linha, coluna;

    do {
        linha = rand() % 3;
        coluna = rand() % 3;
    } while (tabuleiro[linha][coluna] != ' ');

    printf("A m?quina escolheu a linha %d e a coluna %d.\n", linha, coluna);

    tabuleiro[linha][coluna] = JOGADOR_O;
}

// Fun??o para exibir os cr?ditos
void creditos(void) {
    printf("Esse jogo foi feito por Lucas Coutinho, Pedro Henrique Morais, Henrique Delmas, Kaue Fonseca e Joao Lucas Luna.\n");
    main();
}

// Fun??o para iniciar o jogo
void iniciarJogo(int modoJogo, struct Jogador jogadores[], int numJogadores) {
    char resposta;

    int cont_jogadas;
    int tam_tabuleiro = 3 * 3;
    char jogador_atual, ganhador;

    do {
        cont_jogadas = 0;
        jogador_atual = JOGADOR_X;
        ganhador = EMPATE;

        char tabuleiro[3][3];

        srand(time(NULL));

        // Inicializa o tabuleiro
        inicializarTabuleiro(tabuleiro);

        while (1) {
            printf("\n");

            // Exibe o tabuleiro
            exibirTabuleiro(tabuleiro);

            // Realiza a jogada do jogador ou da m?quina
            if (modoJogo == 1 || (modoJogo == 2 && jogador_atual == JOGADOR_X))
                jogadaJogador(tabuleiro, jogador_atual);
            else
                jogadaMaquina(tabuleiro);

            // Exibe o tabuleiro ap?s a jogada
            exibirTabuleiro(tabuleiro);
            cont_jogadas++;

            // Verifica se h? um ganhador ou empate
            ganhador = verificarGanhador(tabuleiro);
            if (ganhador != EMPATE || cont_jogadas == tam_tabuleiro)
                break;

            // Alterna entre os jogadores
            jogador_atual = (jogador_atual == JOGADOR_X) ? JOGADOR_O : JOGADOR_X;
        }

        // Exibe o resultado da partida
        if (ganhador != EMPATE)
            printf("\nO jogador %c ganhou!\n", ganhador);
        else
            printf("\nEmpatou!\n");

        // Atualiza o placar
        for (int i = 0; i < numJogadores; i++) {
            if (jogadores[i].placar > 0)
                printf("%s: %d vit?rias\n", jogadores[i].nome, jogadores[i].placar);
        }

        // Pergunta se deseja jogar novamente
        printf("Deseja jogar novamente? (s/n): ");
        scanf(" %c", &resposta);
    } while (resposta == 's' || resposta == 'S');

    // Retorna ao menu principal
    main();
}

// Fun??o para exibir o ranking
void verRanking(struct Jogador jogadores[], int numJogadores) {
    printf("Ranking:\n");
    for (int i = 0; i < numJogadores; i++) {
        printf("%s: %d vit?rias\n", jogadores[i].nome, jogadores[i].placar);
    }
}

// Fun??o principal
int main() {
    int modoJogo;

    int opcaoValida;
    int stringDigitada;

    // N?mero m?ximo de jogadores no ranking
    const int MAX_JOGADORES = 10;

    // Array para armazenar informa??es dos jogadores
    struct Jogador jogadores[MAX_JOGADORES];

    // Inicializa os jogadores
    for (int i = 0; i < MAX_JOGADORES; i++) {
        jogadores[i].placar = 0;
    }

    // Configura o local para Portugu?s do Brasil
    setlocale(LC_ALL, "Portuguese_Brazil");

    // Exibe o menu principal
    printf("Escolha o modo de jogo:\n");
    printf("(1)  Multiplayer\n");
    printf("(2)  Jogar contra o computador\n");
    printf("(3)  Ver Ranking\n");
    printf("(4)  Cr?ditos\n");
    printf("(5)  Sair\n");

    do {
        opcaoValida = 1;
        do {
            // Solicita a op??o ao usu?rio
            printf("Op??o: ");
            if (scanf("%d", &modoJogo) != 1) {
                printf("Op??o inv?lida. Escolha outra.\n");
                stringDigitada = 0;
                while (getchar() != '\n')
                    ;
            } else {
                stringDigitada = 1;
            }
        } while (stringDigitada == 0);

        // Verifica se a op??o ? v?lida
        if (modoJogo >= 6 || modoJogo <= 0) {
            printf("Op??o inv?lida. Escolha outra.\n");
            opcaoValida = 0;
        }

        // Executa a op??o escolhida
        switch (modoJogo) {
        case 1:
            iniciarJogo(modoJogo, jogadores, MAX_JOGADORES);
            break;

        case 2:
            iniciarJogo(modoJogo, jogadores, MAX_JOGADORES);
            break;

        case 3:
            verRanking(jogadores, MAX_JOGADORES);
            break;

        case 4:
            creditos();
            break;

        case 5:
            // Sai do programa
            exit(0);
            break;
        }

    } while (opcaoValida == 0);

    return 0;
}

