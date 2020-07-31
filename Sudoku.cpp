#include <iostream>

using namespace std;

void printBoard(const unsigned board[9][9]) {
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            cout << board[i][j] << " | ";
        }
        cout << endl;
        cout << "------------------------------------" << endl;
    }
    cout << endl;
}

bool isValid(unsigned n, unsigned r, unsigned c, const unsigned board[9][9]) {
    bool badrow = false;
    bool badcol = false;
    bool badcell = false;
    unsigned cell; // keypad cell designator for selected location (1-9)

    // determine if the row is safe
    for (size_t i = 0; i < 9; i++) {
        if (board[r][i] == n) {
            badrow = true;
        }
    }

    // determine if the column is safe
    for (size_t i = 0; i < 9; i++) {
        if (board[i][c] == n) {
            badcol = true;
        }
    }

    // determine which cell the number is in
    if (c < 3) {
        if (r < 3) {
            cell = 1;
        }
        else if (r < 6) {
            cell = 4;
        }
        else {
            cell = 7;
        }
    }
    else if (c < 6) {
        if (r < 3) {
            cell = 2;
        }
        else if (r < 6) {
            cell = 5;
        }
        else {
            cell = 8;
        }
    }
    else if (c < 9) {
        if (r < 3) {
            cell = 3;
        }
        else if (r < 6) {
            cell = 6;
        }
        else {
            cell = 9;
        }
    }

    // determine if the cell is safe by checking the values in the cell [r][c] is in
    if (cell == 1) {
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                if (board[i][j] == n) {
                    badcell = true;
                }
            }
        }
    }
    else if (cell == 2) {
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 3; j < 6; j++) {
                if (board[i][j] == n) {
                    badcell = true;
                }
            }
        }
    }
    else if (cell == 3) {
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 6; j < 9; j++) {
                if (board[i][j] == n) {
                    badcell = true;
                }
            }
        }
    }
    else if (cell == 4) {
        for (size_t i = 3; i < 6; i++) {
            for (size_t j = 0; j < 3; j++) {
                if (board[i][j] == n) {
                    badcell = true;
                }
            }
        }
    }
    else if (cell == 5) {
        for (size_t i = 3; i < 6; i++) {
            for (size_t j = 3; j < 6; j++) {
                if (board[i][j] == n) {
                    badcell = true;
                }
            }
        }
    }
    else if (cell == 6) {
        for (size_t i = 3; i < 6; i++) {
            for (size_t j = 6; j < 9; j++) {
                if (board[i][j] == n) {
                    badcell = true;
                }
            }
        }
    }
    else if (cell == 7) {
        for (size_t i = 6; i < 9; i++) {
            for (size_t j = 0; j < 3; j++) {
                if (board[i][j] == n) {
                    badcell = true;
                }
            }
        }
    }
    else if (cell == 8) {
        for (size_t i = 6; i < 9; i++) {
            for (size_t j = 3; j < 6; j++) {
                if (board[i][j] == n) {
                    badcell = true;
                }
            }
        }
    }
    else {
        for (size_t i = 6; i < 9; i++) {
            for (size_t j = 6; j < 9; j++) {
                if (board[i][j] == n) {
                    badcell = true;
                }
            }
        }
    }

    if (badrow || badcol || badcell) {
        return false;
    }
    return true;
}

bool isFull(unsigned board[9][9]) {
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            if (board[i][j] == 0) {  //  0 represents an unassigned location
                return false;
            }
        }
    }
    return true;
}

bool Solve(unsigned board[9][9]) {
    // if the board is full, we are done
    if (isFull(board)) {
        return true;
    }

    unsigned row, col;
    bool found = false;
    
    // find the next unassigned location
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }

    // for every digit, see if it is valid and leads to a solution
    for (unsigned i = 1; i <= 9; i++) {
        if (isValid(i, row, col, board)) {
            board[row][col] = i;  // assign number to empty spot if valid
            if (Solve(board) == true) {  // if this leads to a solution, return true
                return true;
            } else {
                board[row][col] = 0;  //  else, reset the location to 0
            }
        }
    }
    return false;  //  return false if solution not found, this causes the current location to be reset to 0 and a different number to be selected (backtracking)
}

int main() {
    // example board
    unsigned board[9][9] = {8, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 3, 6, 0, 0, 0, 0, 0,
                                0, 7, 0, 0, 9, 0, 2, 0, 0,
                                0, 5, 0, 0, 0, 7, 0, 0, 0,
                                0, 0, 0, 0, 4, 5, 7, 0, 0,
                                0, 0, 0, 1, 0, 0, 0, 3, 0,
                                0, 0, 1, 0, 0, 0, 0, 6, 8,
                                0, 0, 8, 5, 0, 0, 0, 1, 0,
                                0, 9, 0, 0, 0, 0, 4, 0, 0};
    // empty board
    //     unsigned board[9][9] = {
    //     0, 0, 0, 0, 0, 0, 0, 0, 0,
    //     0, 0, 0, 0, 0, 0, 0, 0, 0,
    //     0, 0, 0, 0, 0, 0, 0, 0, 0,
    //     0, 0, 0, 0, 0, 0, 0, 0, 0,
    //     0, 0, 0, 0, 0, 0, 0, 0, 0,
    //     0, 0, 0, 0, 0, 0, 0, 0, 0,
    //     0, 0, 0, 0, 0, 0, 0, 0, 0,
    //     0, 0, 0, 0, 0, 0, 0, 0, 0,
    //     0, 0, 0, 0, 0, 0, 0, 0, 0,
    // };

    Solve(board);
    printBoard(board);
}