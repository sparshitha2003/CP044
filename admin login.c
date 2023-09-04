#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 9

// Define a basic user struct
typedef struct {
    char username[20];
    char password[20];
    bool isAdmin;
} User;

// Define the Sudoku board
int sudokuBoard[SIZE][SIZE];

// Function to check if a user is an admin
bool isAdmin(User* users, int userCount, const char* username) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && users[i].isAdmin) {
            return true;
        }
    }
    return false;
}

// Function to authenticate a user
bool authenticate(User* users, int userCount, const char* username, const char* password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return true;
        }
    }
    return false;
}

// Function to print the Sudoku board
void printSudoku(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

// Function to solve Sudoku
bool solveSudoku(int board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= SIZE; num++) {
                    bool valid = true;
                    // Check if the number is already in the row, column, or 3x3 subgrid
                    for (int i = 0; i < SIZE; i++) {
                        if (board[row][i] == num || board[i][col] == num ||
                            board[row - row % 3 + i / 3][col - col % 3 + i % 3] == num) {
                            valid = false;
                            break;
                        }
                    }
                    if (valid) {
                        board[row][col] = num;
                        if (solveSudoku(board)) {
                            return true;
                        }
                        board[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// Function to input a Sudoku puzzle
void inputSudoku() {
    printf("Enter the Sudoku puzzle (use 0 for empty cells):\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf("%d", &sudokuBoard[i][j]);
        }
    }
}

int main() {
    // Define some users (for demonstration purposes)
    User users[] = {
        {"user1", "password1", false},
        {"admin", "adminpassword", true}
    };
    int userCount = sizeof(users) / sizeof(users[0]);

    // Admin login
    char username[20];
    char password[20];

    printf("Enter admin username: ");
    scanf("%s", username);
    printf("Enter admin password: ");
    scanf("%s", password);

    if (authenticate(users, userCount, username, password) && isAdmin(users, userCount, username)) {
        printf("Admin login successful!\n");
        inputSudoku(); // Admin inputs the Sudoku puzzle

        // Print the Sudoku puzzle
        printf("Sudoku Puzzle:\n");
        printSudoku(sudokuBoard);

        // Solve the Sudoku puzzle
        solveSudoku(sudokuBoard);

        // Print the solved Sudoku
        printf("\nSolved Sudoku:\n");
        printSudoku(sudokuBoard);
    } else {
        printf("Admin login failed. Invalid username or password or not an admin.\n");
    }

    return 0;
}
