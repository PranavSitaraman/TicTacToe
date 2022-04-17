#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
long long relativetime = 0;
struct Move
{
    int row, column;
};
char player = 'x', opponent = 'o';
bool empty(char board[3][3])
{
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) if (board[i][j] == ' ') return true;
    return false;
}
int evaluate(char board[3][3])
{
    for (int row = 0; row < 3; row++)
    {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2])
        {
            if (board[row][0] == player) return +10;
            else if (board[row][0] == opponent) return -10;
        }
    }
    for (int column = 0; column < 3; column++)
    {
        if (board[0][column] == board[1][column] && board[1][column] == board[2][column])
        {
            if (board[0][column] == player) return +10;
            else if (board[0][column] == opponent) return -10;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == player) return +10;
        else if (board[0][0] == opponent) return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == player) return +10;
        else if (board[0][2] == opponent) return -10;
    }
    return 0;
}
int minimax(char board[3][3], int depth, bool maximum, int alpha, int beta)
{
    relativetime++;
    int score = evaluate(board);
    if (score == 10) return score;
    if (score == -10) return score;
    if (empty(board) == false) return 0;
    if (maximum)
    {
        int best = INT_MIN;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = player;
                    best = max(best, minimax(board, depth + 1, !maximum, alpha, beta));
                    board[i][j] = ' ';
                    alpha = max(alpha, best);
                    if (beta <= alpha)
                    {
                        break;
                    }
                }
            }
            if (beta <= alpha)
            {
                break;
            }
        }
        return best;
    }
    else
    {
        int best = INT_MAX;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = opponent;
                    best = min(best, minimax(board, depth + 1, !maximum, alpha, beta));
                    board[i][j] = ' ';
                    beta = min(beta, best);
                    if (beta <= alpha)
                    {
                        break;
                    }
                }
            }
            if (beta <= alpha)
            {
                break;
            }
        }
        return best;
    }
}
int minimax(char board[3][3], int depth, bool maximum)
{
    relativetime++;
    int score = evaluate(board);
    if (score == 10) return score;
    if (score == -10) return score;
    if (empty(board) == false) return 0;
    if (maximum)
    {
        int best = INT_MIN;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = player;
                    best = max(best, minimax(board, depth + 1, !maximum));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
    else
    {
        int best = INT_MAX;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = opponent;
                    best = min(best, minimax(board, depth + 1, !maximum));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}
Move humanMove(char board[3][3])
{
    Move bestMove = { -1, -1 };
    bestMove.row = -1;
    bestMove.column = -1;
    bool correct = false;
    while (correct == false)
    {
        int row = rand() % 3;
        int column = rand() % 3;
        if (board[row][column] == ' ')
        {
            correct = true;
            bestMove.row = row;
            bestMove.column = column;
        }
    }
    return bestMove;
}
Move computerMove(char board[3][3], int alphabeta)
{
    int bestVal = INT_MIN;
    Move bestMove = { -1, -1 };
    bestMove.row = -1;
    bestMove.column = -1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = player;
                int moveVal;
                if (alphabeta == 0)
                {
                    moveVal = minimax(board, 0, false);
                }
                else
                {
                    moveVal = minimax(board, 0, false, INT_MIN, INT_MAX);
                }
                board[i][j] = ' ';
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.column = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}
void printboard(char b[3][3])
{
    printf("%c|%c|%c\n-----\n%c|%c|%c\n-----\n%c|%c|%c\n", b[0][0], b[0][1], b[0][2], b[1][0], b[1][1], b[1][2], b[2][0], b[2][1], b[2][2]);
}
void playComp()
{
    int difficult;
    printf("Enter 0 to play against regular minimax and 1 to play against alpha-beta pruning: ");
    scanf("%d", &difficult);
    getchar();
    printf("Enter 0 to go first and 1 for the computer to go first: ");
    int first;
    scanf("%d", &first);
    getchar();
    char board[3][3] =
    {
        { ' ', ' ', ' ' },
        { ' ', ' ', ' ' },
        { ' ', ' ', ' ' }
    };
    if (first == 1)
    {
        printboard(board);
        printf("Computer's turn to play:\n");
        Move bestMove = computerMove(board, difficult);
        board[bestMove.row][bestMove.column] = 'x';
        printboard(board);
        if (evaluate(board) == 10)
        {
            printf("Computer wins!");
            return;
        }
        while (empty(board))
        {
            printf("Player's turn to play:\n");
            printf("Enter row and column: ");
            int row, column;
            scanf("%d %d", &row, &column);
            getchar();
            board[row][column] = 'o';
            printboard(board);
            if (evaluate(board) == -10)
            {
                printf("Player wins!");
                return;
            }
            printf("Computer's turn to play:\n");
            Move bestMove = computerMove(board, difficult);
            board[bestMove.row][bestMove.column] = 'x';
            printboard(board);
            if (evaluate(board) == 10)
            {
                printf("Computer wins!");
                return;
            }
        }
        printf("Tie!");
    }
    else
    {
        player = 'o', opponent = 'x';
        printboard(board);
        printf("Player's turn to play:\n");
        printf("Enter row and column: ");
        int row, column;
        scanf("%d %d", &row, &column);
        getchar();
        board[row][column] = 'x';
        printboard(board);
        if (evaluate(board) == -10)
        {
            printf("Player wins!");
            return;
        }
        while (empty(board))
        {
            printf("Computer's turn to play:\n");
            Move bestMove = computerMove(board, difficult);
            board[bestMove.row][bestMove.column] = 'o';
            printboard(board);
            if (evaluate(board) == 10)
            {
                printf("Computer wins!");
                return;
            }
            printf("Player's turn to play:\n");
            printf("Enter row and column: ");
            int row, column;
            scanf("%d %d", &row, &column);
            getchar();
            board[row][column] = 'x';
            printboard(board);
            if (evaluate(board) == -10)
            {
                printf("Player wins!");
                return;
            }
        }
        printf("Tie!");
    }
}
void testing()
{
    int iterations;
    printf("Enter a number of iterations: ");
    scanf("%d", &iterations);
    getchar();
    char board[3][3] = { 0 };
    int wins, ties, losses;
    wins = 0, ties = 0, losses = 0;
    for (int i = 0; i < iterations; i++)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = ' ';
            }
        }
        Move bestMove = computerMove(board, 0);
        board[bestMove.row][bestMove.column] = 'x';
        while (empty(board))
        {
            bestMove = humanMove(board);
            board[bestMove.row][bestMove.column] = 'o';
            if (evaluate(board) == -10)
            {
                losses++;
                break;
            }
            bestMove = computerMove(board, 0);
            board[bestMove.row][bestMove.column] = 'x';
            if (evaluate(board) == 10)
            {
                wins++;
                break;
            }
        }
        if (evaluate(board) == 0)
        {
            ties++;
        }
    }
    printf("Regular minimax, going first - wins: %d, ties: %d, losses: %d - relative time of %lld\n", wins, ties, losses, relativetime);
    relativetime = 0;
    wins = 0, ties = 0, losses = 0;
    for (int i = 0; i < iterations; i++)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = ' ';
            }
        }
        Move bestMove = computerMove(board, 1);
        board[bestMove.row][bestMove.column] = 'x';
        while (empty(board))
        {
            bestMove = humanMove(board);
            board[bestMove.row][bestMove.column] = 'o';
            if (evaluate(board) == -10)
            {
                losses++;
                break;
            }
            bestMove = computerMove(board, 1);
            board[bestMove.row][bestMove.column] = 'x';
            if (evaluate(board) == 10)
            {
                wins++;
                break;
            }
        }
        if (evaluate(board) == 0)
        {
            ties++;
        }
    }
    printf("Alpha-beta pruning, going first - wins: %d, ties: %d, losses: %d - relative time of %lld\n", wins, ties, losses, relativetime);
    relativetime = 0;
    player = 'o';
    opponent = 'x';
    wins = 0, ties = 0, losses = 0;
    for (int i = 0; i < iterations; i++)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = ' ';
            }
        }
        Move bestMove = humanMove(board);
        board[bestMove.row][bestMove.column] = 'x';
        while (empty(board))
        {
            bestMove = computerMove(board, 0);
            board[bestMove.row][bestMove.column] = 'o';
            if (evaluate(board) == 10)
            {
                wins++;
                break;
            }
            bestMove = humanMove(board);
            board[bestMove.row][bestMove.column] = 'x';
            if (evaluate(board) == -10)
            {
                losses++;
                break;
            }
        }
        if (evaluate(board) == 0)
        {
            ties++;
        }
    }
    printf("Regular minimax, going second - wins: %d, ties: %d, losses: %d - relative time of %lld\n", wins, ties, losses, relativetime);
    relativetime = 0;
    wins = 0, ties = 0, losses = 0;
    for (int i = 0; i < iterations; i++)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = ' ';
            }
        }
        Move bestMove = humanMove(board);
        board[bestMove.row][bestMove.column] = 'x';
        while (empty(board))
        {
            bestMove = computerMove(board, 1);
            board[bestMove.row][bestMove.column] = 'o';
            if (evaluate(board) == 10)
            {
                wins++;
                break;
            }
            bestMove = humanMove(board);
            board[bestMove.row][bestMove.column] = 'x';
            if (evaluate(board) == -10)
            {
                losses++;
                break;
            }
        }
        if (evaluate(board) == 0)
        {
            ties++;
        }
    }
    printf("Alpha-beta pruning, going second - wins: %d, ties: %d, losses: %d - relative time of %lld\n", wins, ties, losses, relativetime);
    relativetime = 0;
}
void tictactoe()
{
    srand(time(0));
    char choice;
    printf("Enter p to play against the computer or t to run an accuracy test: ");
    scanf("%c", &choice);
    getchar();
    if (choice == 'p')
    {
        playComp();
    }
    else
    {
        testing();
    }
}