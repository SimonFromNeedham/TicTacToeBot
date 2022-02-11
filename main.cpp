/* Overview: This program uses a simple minimax search algorithm to find a general solution to tic-tac-toe. The program can
   easily handle board states of 3x3 or smaller, anything larger would require dynamic programming (potential improvement) */

#include <iostream>
using namespace std;

// Declare helper methods so they're usable in main()
// Every helper method uses a pointer to represent the 2-D board (saves memory)
char gameOver(int num_rows, int num_cols, char *arr);
void displayBoard(int num_rows, int num_cols, char *arr);
void humanPlays(int num_rows, int num_cols, char *arr);
double computerPlays(char x_or_o, int num_rows, int num_cols, char *arr);

/* Important syntax note about 2-D array pointers:
   The adresses of array elements are still in order, first by row then by collumn
   Therefore, the proper syntax for accessing arr[1][2] would be *(arr + 3*1 + 2) --> *(arr+5)
   This syntax is used frequenctly and will be referenced later */

// The maximum board size allowed by the program
// We need to define these in advance so the the program can construct the board at compile-time
const int MAX_ROWS = 9;
const int MAX_COLS = 9;

int main()
{
    // "dimensions" describes the number of rows/cols in board
    // "turn" describes who goes first (1 for human, 2 for computer)
    // Note that for future calculations, the computer is always 'X'
    int dimensions, turn;
    
    // Only accept single-digit dimensions, anything else requires too much computing power!
    // (To be honest, anything above 3x3 requires too much power, but let's pretend to be more general)
    cout << "How many rows and columns? Please input a signle-digit number larger than 1: ";
    cin >> dimensions;
    
    cout << "Do you want to go First (1) or Second (2)? ";
    cin >> turn;
    
    // Idiot Proofing
    if (dimensions < 2 || dimensions > 9 || (turn != 1 && turn != 2))
    {
        cout << "Err. Bad input. Terminating Program." << endl;
        return 1;
    }
    
    // Constants board dimensions
    const int num_rows = dimensions;
    const int num_cols = dimensions;
    
    // We can't set board size to num_rows/num_cols, as those are underfined variables at compile-time
    // So instead, we set it to constants which represent the maximum possible size of a board
    char board[MAX_ROWS][MAX_COLS];
    
    // Fill the board with blank values
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            board[i][j] = '.';
        }
    }
    
    // Prompt the player to begin the game
    cout << endl << "Here is the board: " << endl;
    displayBoard(num_rows, num_cols, &board[0][0]);
    cout << endl << "It's time to begin. The computer will play X's, and you will play O's: " << endl;
    
    // gameOver() returns 0 if it's not over --> false
    while (!gameOver(num_rows, num_cols, &board[0][0]))
    {
        if (turn == 1)
        {
            cout << "It's your turn... " << endl;
            humanPlays(num_rows, num_cols, &board[0][0]);
            
            // Switch turns
            turn++;
        }
        
        else
        {
            cout << "It's the computer's turn... " << endl;
            computerPlays('X', num_rows, num_cols, &board[0][0]);
            
            // Switch turns
            turn--;
        }
        
        cout << "Here's the updated board: " << endl;
        displayBoard(num_rows, num_cols, &board[0][0]);
        cout << endl;
    }
    
    // 'X' = computer win, 'O' = human win, 3 = tie
    switch(gameOver(num_rows, num_cols, &board[0][0]))
    {
        case 'O':
            cout << "Human Wins :)" << endl;
            break;
            
        case 'X':
            cout << "Computer wins :(" << endl;
            break;
            
        case 3:
            cout << "It's a tie!" << endl;
            break;
            
        default:
            cout << "Oh No! Something went wrong :(" << endl;
            break;
    }
    
    return 0;
}

// Return Values:
// Game Isn't Over: 0
// Computer (X's) wins: 'X'
// Human (O's) wins: 'O'
// Board Filled (Tie): 3
char gameOver(int num_rows, int num_cols, char *arr)
{
    // Check for a vertical win
    for (int i = 0; i < num_rows; i++)
    {
        int j = 1;
        
        while (j < num_cols)
        {
            // Lines 12-15 have a syntax explanation
            char cur = *(arr + MAX_ROWS*i + j);
            char last = *(arr + MAX_ROWS*i + j-1);
            
            /* Only increment j if...
               There's a streak going (cur != last)
               That streak is of X's or O's (cur != '.') */
            if (cur != last || cur == '.')
            {
                break;
            }
            
            j++;
        }
        
        if (j == num_cols)
        {
            return *(arr + MAX_ROWS*i + j-1);
        }
    }
    
    // Check for a horizontal win
    for (int j = 0; j < num_rows; j++)
    {
        int i = 1;
        
        while (i < num_rows)
        {
            // Lines 12-15 have a syntax explanation
            char cur = *(arr + MAX_ROWS*(i) + j);
            char last = *(arr + MAX_ROWS*(i-1) + j);
            
            /* Only increment i if...
               There's a streak going (cur != last)
               That streak is of X's or O's (cur != '.') */
            if (cur != last || cur == '.')
            {
                break;
            }
            
            i++;
        }
        
        if (i == num_cols)
        {
            return *(arr + MAX_ROWS*(i-1) + j);
        }
    }
    
    // Check for diagnols:
    int i = 1;
    int j = 1;
        
    while (i < num_rows)
    {
        // You get the gist by now
        char cur = *(arr + MAX_ROWS*(i) + j);
        char last = *(arr + MAX_ROWS*(i-1) + j-1);
            
        if (cur != last || cur == '.')
        {
            break;
        }
            
        i++;
        j++;
    }
        
    if (i == num_rows)
    {
        return *(arr + MAX_ROWS*(i-1) + j-1);
    }
        
    // Don't forget about right to left diagnols!
    i = 1;
    j = num_cols-2;
        
    while (i < num_rows)
    {
        // You get the gist by now
        char cur = *(arr + MAX_ROWS*(i) + j);
        char last = *(arr + MAX_ROWS*(i-1) + j+1);
            
        if (cur != last || cur == '.')
        {
            break;
        }
            
        // j-- for right to left
        i++;
        j--;
    }
        
    if (i == num_rows)
    {
        return *(arr + MAX_ROWS*(i-1) + j+1);
    }
    
    // Check for unfilled board
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            if (*(arr + MAX_ROWS*(i) + j) == '.')
            {
                return 0;
            }
        }
    }
        
    // Filled board --> tie!
    return 3;
}

// Print out the game board
void displayBoard(int num_rows, int num_cols, char *arr)
{
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            cout << *(arr + MAX_ROWS*i + j) << ' ';
        }
        
        cout << endl;
    }
}

// Takes input to make a move
void humanPlays(int num_rows, int num_cols, char *arr)
{
    int i = -1;
    int j = -1;
    
    cout << "In what row do you want to move? ";
    cin >> i;
    
    cout << "In what collumn do you want to move? ";
    cin >> j;
    
    // Humans think of the first row/col as 1, not 0
    // The column checks are depricaded code from when the "row" and "col" could be different
    while (i < 1 || i > num_rows || j < 1 || j > num_cols || *(arr + MAX_ROWS*(i-1) + j-1) != '.')
    {
        cout << "Err. Bad input. Terminating Program." << endl;
        exit(1);
    }
    
    *(arr + MAX_ROWS*(i-1) + j-1) = 'O';
}

// Recursively search for the best move using min/max trees
double computerPlays(char x_or_o, int num_rows, int num_cols, char *arr)
{
    // 'X' = computer win, 'O' = human win, 3 = tie
    int result = gameOver(num_rows, num_cols, arr);
    
    // Assume both players are playing optimally...
    if (result == x_or_o)
    {
        return 1;
    }
    
    // Indicates a tie
    else if (result == 3)
    {
        return 0;
    }
    
    // Implies loss (no tie, no win, but the game has concluded)
    else if (result != 0)
    {
        return -1;
    }
    
    // Implies that the game is still going!
    // Keep track of the best move's location
    int max_row = 0;
    int max_col = 0;
    
    // Max val = value of best move
    // Use the lowest possible int so it gets reset
    double max_val = -2147483648;
    
    // For every possible move...
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_rows; j++)
        {
            // Lines 12-15 have a syntax explanation
            if (*(arr + MAX_ROWS*(i) + j) == '.')
            {
                // Copy the array to check for new board states
                char copy[9][9];
                
                for (int k = 0; k < num_rows; k++)
                {
                    for (int l = 0; l < num_rows; l++)
                    {
                        copy[k][l] = *(arr + MAX_ROWS*(k) + l);
                    }
                }
                
                // Play the move...
                copy[i][j] = x_or_o;
                
                // Use the negative value to find the most damaging move to our opponent
                double val = -computerPlays(x_or_o == 'O' ? 'X' : 'O', num_rows, num_cols, *copy);
                
                // If the new move is better...
                if (val > max_val)
                {
                    max_row = i;
                    max_col = j;
                    max_val = val;
                }
            }
        }
    }
    
    // Play the best move and return it
    *(arr + MAX_ROWS*(max_row) + max_col) = 'X';
    return max_val;
}
