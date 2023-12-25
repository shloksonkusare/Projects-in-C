#include <stdio.h>

#define PLAYER_X 'X'
#define PLAYER_O 'O'
#define EMPTY ' '

int evaluate_board(char board[3][3]) {
    // Check for a winner
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != EMPTY) {
            return (board[i][0] == PLAYER_X) ? -10 : 10;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != EMPTY) {
            return (board[0][i] == PLAYER_X) ? -10 : 10;
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != EMPTY) {
        return (board[0][0] == PLAYER_X) ? -10 : 10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != EMPTY) {
        return (board[0][2] == PLAYER_X) ? -10 : 10;
    }

    // No winner, return 0
    return 0;
}

int is_board_full(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                return 0;
            }
        }
    }
    return 1;
}

int minimax(char board[3][3], int depth, int is_maximizer, int alpha, int beta) {
    int score = evaluate_board(board);

    // If AI wins, return positive
    if (score == 10) {
        return score - depth;
    }

    // If player wins, return negative
    if (score == -10) {
        return score + depth;
    }

    // If the board is full, draw
    if (is_board_full(board)) {
        return 0;
    }

    if (is_maximizer) {
        int best_score = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_O;
                    int score = minimax(board, depth + 1, 0, alpha, beta);
                    board[i][j] = EMPTY;
                    if (score > best_score) {
                        best_score = score;
                    }
                    alpha = (alpha > best_score) ? alpha : best_score;
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return best_score;
    } else {
        int best_score = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_X;
                    int score = minimax(board, depth + 1, 1, alpha, beta);
                    board[i][j] = EMPTY;
                    if (score < best_score) {
                        best_score = score;
                    }
                    beta = (beta < best_score) ? beta : best_score;
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return best_score;
    }
}

void display_board(char board[3][3]) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) {
                printf("|");
            }
        }
        printf("\n");
        if (i < 2) {
            printf("---|---|---\n");
        }
    }
    printf("\n");
}

int is_valid_move(char board[3][3], int row, int col) {
    if (row < 0 || row > 2 || col < 0 || col > 2) {
        printf("Invalid move. Please enter row (0-2) and column (0-2) within the board range.\n");
        return 0;
    }

    if (board[row][col] != EMPTY) {
        printf("Invalid move. The cell is already occupied.\n");
        return 0;
    }

    return 1;
}

int make_move(char board[3][3], int row, int col, char player) {
    board[row][col] = player;
    return 1;
}

int main() {
    char board[3][3] = {
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY}
    };

    int row, col;
    char winner = EMPTY;

    printf("Tic Tac Toe - Human (X) vs AI (O)\n");
    display_board(board);

    while (1) {
        // Human player's move
        do {
            printf("Enter row (0-2) and column (0-2) for your move: ");
            scanf("%d %d", &row, &col);
        } while (!is_valid_move(board, row, col));

        make_move(board, row, col, PLAYER_X);
        display_board(board);

        if (evaluate_board(board) != 0 || is_board_full(board)) {
            break;
        }

        // AI player's move 
        printf("AI's turn...\n");
        int best_score = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_O;
                    int score = minimax(board, 0, 0, -1000, 1000);
                    board[i][j] = EMPTY;
                    if (score > best_score) {
                        best_score = score;
                        row = i;
                        col = j;
                    }
                }
            }
        }

        make_move(board, row, col, PLAYER_O);
        display_board(board);

        if (evaluate_board(board) != 0 || is_board_full(board)) {
            break;
        }
    }

    winner = evaluate_board(board);
    if (winner == PLAYER_X) {
        printf("Congratulations! You win!\n");
    } else if (winner == PLAYER_O) {
        printf("AI wins! Better luck next time.\n");
    } else {
        printf("It's a draw! Good game!\n");
    }

    return 0;
}
