#include "MatrixMarker.h"

MatrixMarker::MatrixMarker(int input[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i)
        for (int j = 0; j < COLS; ++j) {
            matrix[i][j] = input[i][j];
            marks[i][j] = false;
        }
}

bool MatrixMarker::canMark(int row, int col) {
    int unmarkedInRow = 0;
    for (int j = 0; j < COLS; ++j)
        if (!marks[row][j] && j != col)
            ++unmarkedInRow;
    if (unmarkedInRow == 0) return false;

    int unmarkedInCol = 0;
    for (int i = 0; i < ROWS; ++i)
        if (!marks[i][col] && i != row)
            ++unmarkedInCol;
    return unmarkedInCol != 0;
}

void MatrixMarker::findDuplicatesInRows() {
    for (int i = 0; i < ROWS; ++i) {
        bool visited[COLS] = {};
        for (int j = 0; j < COLS; ++j) {
            if (visited[j]) continue;
            int count = 0, indices[COLS];

            for (int k = 0; k < COLS; ++k)
                if (matrix[i][j] == matrix[i][k]) {
                    indices[count++] = k;
                    visited[k] = true;
                }

            if (count > 1)
                for (int x = 1; x < count; ++x)
                    if (canMark(i, indices[x]))
                        marks[i][indices[x]] = true;
        }
    }
}

void MatrixMarker::findDuplicatesInCols() {
    for (int j = 0; j < COLS; ++j) {
        bool visited[ROWS] = {};
        for (int i = 0; i < ROWS; ++i) {
            if (visited[i]) continue;
            int count = 0, indices[ROWS];

            for (int k = 0; k < ROWS; ++k)
                if (matrix[i][j] == matrix[k][j]) {
                    indices[count++] = k;
                    visited[k] = true;
                }

            if (count > 1)
                for (int x = 1; x < count; ++x)
                    if (canMark(indices[x], j))
                        marks[indices[x]][j] = true;
        }
    }
}

void MatrixMarker::process() {
    findDuplicatesInRows();
    findDuplicatesInCols();
}

void MatrixMarker::print() const {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j)
            std::cout << (marks[i][j] ? RESET : COLOR) << matrix[i][j] << ' ';
        std::cout << RESET << '\n';
    }
}
