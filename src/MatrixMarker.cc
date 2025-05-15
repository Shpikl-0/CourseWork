#include "MatrixMarker.h"
#include <iomanip>
using namespace std;

MatrixMarker::MatrixMarker(int input[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i)
        for (int j = 0; j < COLS; ++j) {
            matrix[i][j] = input[i][j];
            marked[i][j] = false;
        }
}

bool MatrixMarker::isMarkAllowed(int row, int col) {
    int unmarkedInRow = 0;
    for (int j = 0; j < COLS; ++j)
        if (!marked[row][j] && j != col)
            ++unmarkedInRow;
    if (unmarkedInRow == 0) return false;

    int unmarkedInCol = 0;
    for (int i = 0; i < ROWS; ++i)
        if (!marked[i][col] && i != row)
            ++unmarkedInCol;
    return unmarkedInCol != 0;
}

void MatrixMarker::markRowDuplictes() {
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
                    if (isMarkAllowed(i, indices[x]))
                        marked[i][indices[x]] = true;
        }
    }
}

void MatrixMarker::markColumnDuplicates() {
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
                    if (isMarkAllowed(indices[x], j))
                        marked[indices[x]][j] = true;
        }
    }
}

void MatrixMarker::run() {
    markRowDuplictes();
    markColumnDuplicates();
}


string centerText(int number, int width) {
    string str = to_string(number);
    int padding = width - static_cast<int>(str.length());
    int padLeft = padding / 2;
    int padRight = padding - padLeft;
    return string(padLeft, ' ') + str + string(padRight, ' ');
}

void printHorizontalLine(int cols, int cellWidth) {
    for (int i = 0; i < cols; ++i) {
        cout << "+";
        for (int j = 0; j < cellWidth; ++j)
            cout << "-";
    }
    cout << "+\n";
}

void MatrixMarker::print() const {
    const int cellWidth = 8;
    const int cellHeight = 3;

    for (int i = 0; i < ROWS; ++i) {
        printHorizontalLine(COLS, cellWidth);

        for (int h = 0; h < cellHeight; ++h) {
            for (int j = 0; j < COLS; ++j) {
                cout << "|";
                bool isHighlighted = !marked[i][j];
                string content;

                if (h == cellHeight / 2) {
                    content = centerText(matrix[i][j], cellWidth);
                } else {
                    content = string(cellWidth, ' ');
                }

                if (isHighlighted)
                    cout << COLOR << content << RESET;
                else
                    cout << content;
            }
            cout << "|\n";
        }
    }

    printHorizontalLine(COLS, cellWidth);
}